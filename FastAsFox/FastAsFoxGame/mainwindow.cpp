#include "mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include "fox.h"
#include "mapsection.h"
#include "constants.h"
#include "map.h"
#include <QApplication>
#include <QKeyEvent>
#include <QScreen>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QScreen>
#include <QStyle>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // load the font from resources
    int fontId = QFontDatabase::addApplicationFont(":/font/sprites/font/font.TTF");
    QString fontFamily;
    if (fontId != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    TileSet * set = new TileSet(GROUND_TILES, TILE_SIZE, 1);
    MapSection * section = new MapSection(LEVEL_ONE);
    std::vector<TileSet*>* tilesets = new std::vector<TileSet*>();
    tilesets->push_back(set);

    Map * map = new Map(section, tilesets);
    map->load();

    // Create a scene and view to display text
    mScene = map->getScene();
    view = map->getView();

    // Load and scale the background image
    QPixmap bg(":/texture/sprites/texture/sky.jpg");

    // Assuming mapWidth and mapHeight are the size of your map
    // Adjust these to match your map size
    int mapWidth = map->getWidth(); // Replace with actual width of your map
    int mapHeight = map->getHeight(); // Replace with actual height of your map

    bg = bg.scaled(mapWidth, mapHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Add the background to the scene
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(bg);
    background->setZValue(-1); // ensure it's drawn behind all other items
    mScene->addItem(background);

    // Set the scene's size to the size of the background
    mScene->setSceneRect(0, 0, bg.width(), bg.height());

    // Set the QGraphicsView's viewport to the size of the scene
    view->setViewport(new QWidget);
    view->viewport()->setFixedSize(bg.size());

    // Set the central widget of the window to be the view
    setCentralWidget(view);

    // Set the scroll bar policies for the QGraphicsView
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //:/texture/sprites/texture/sky.jpg

    // save font family for use in printText
    mFontFamily = fontFamily;
    mFruits = QPixmap(":/fruits/sprites/fruits/fruits.png");


    // Initialize the LCD number
    lcd = new QLCDNumber(this);
    lcd->setDigitCount(7);  // 2 digits for integer part, 1 dot, 2 digits for fraction part
    lcd->setMode(QLCDNumber::Dec);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setFrameStyle(QFrame::NoFrame); // Remove the rectangular outline
    lcd->display(count);


    int margin = 10;
    // Set LCD size and location
    lcd->setFixedSize(200, 50); // Adjust the size as per your requirements
    lcd->move(this->width() - lcd->width() - margin, margin);


    // Initialize the timer
    timer = new QTimer(this);

    // Connect timer's timeout() signal to the slot that will update the LCD
    connect(timer, &QTimer::timeout, this, &MainWindow::updateLCD);


    // Start the timer to fire every 10 ms (this will result in hundredths of a second)
    timer->start(10);

    // Create the Fox
    foxSprite = new Fox(mScene, view);


    //==================CAMERA================================


    // Threshold point beyond which camera will move, adjust as needed
    double threshold = view->width() * 0.25;

    // Check if fox's position in the view has crossed the threshold
    QPointF foxInView = view->mapFromScene(foxSprite->pos());

    if (foxInView.x() < threshold) {
        // Center camera on fox but with an offset to the left
        view->centerOn(QPointF(foxSprite->pos().x() - threshold, foxSprite->pos().y()));
    }

    //===========================================================

    this->setFocus();
    qApp->installEventFilter(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    windowHeight = screenGeometry.height();
    windowWidth = screenGeometry.width();

    QPixmap ribbonPixmap(":/userInterface/sprites/userInterface/ribbon.png");
   ribbonX = (this->width() - ribbonPixmap.width()) / 2 - 100;


    ribbonY = 0;


    // Calculate the new size for the window
    QSize newSize(bg.width() - 1000, bg.height());

    // Set MainWindow's size to the newSize
    this->setGeometry(QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        newSize,
        QGuiApplication::primaryScreen()->availableGeometry()
    ));


}


void MainWindow::addText() {
    printText("Bonjour a tous !", 100, 200, 20, QColor(Qt::red));
    printText("La vie est belle.", 150, 250, 20, QColor(Qt::green));
    printText("Les chiens jouent dans le parc.", 200, 300, 20, QColor(Qt::blue));
    printText("La lutte des classes est le moteur de l'histoire", 300, 400, 20, QColor(231, 200, 27));

}

void MainWindow::printText(const QString &text, int x, int y, int z, const QColor &color) {
    QFont font(mFontFamily);
    font.setPointSize(z);
    QGraphicsTextItem *textItem = new QGraphicsTextItem(text);
    textItem->setFont(font);
    textItem->setPos(x, y);
    textItem->setDefaultTextColor(color);
    mScene->addItem(textItem);
}

void MainWindow::displayFruit(FruitType fruitType, int versionId, int x, int y)
{
    // Define constants for the locations and widths of the fruit types in your sprite sheet
    const int APPLE_START_X = 0;
    const int APPLE_WIDTH = 16;

    const int GRAPE_START_X = 48;
    const int GRAPE_WIDTH = 16;

    const int CHERRY_START_X = 225;
    const int CHERRY_WIDTH = 15;

    const int LEMON_START_X = 272;
    const int LEMON_WIDTH = 16;

    const int PEACH_START_X = 190;
    const int PEACH_WIDTH = 19;

    // Determine the fruitId based on the fruitType
    int fruitId;
    switch (fruitType) {
    case FruitType::Apple:
        fruitId = APPLE_START_X / APPLE_WIDTH;
        break;
    case FruitType::Grape:
        fruitId = GRAPE_START_X / GRAPE_WIDTH;
        break;
    case FruitType::Cherry:
        fruitId = CHERRY_START_X / CHERRY_WIDTH;
        break;
    case FruitType::Lemon:
        fruitId = LEMON_START_X / LEMON_WIDTH;
        break;
    case FruitType::Peach:
        fruitId = PEACH_START_X / PEACH_WIDTH;
        break;
    }

    if (fruitId < 0 || fruitId >= 38 || versionId < 0 || versionId >= 6)
        return;

    int fruitX = fruitId * 16;       // 16 pixels width per fruit
    int fruitY = versionId * 16;     // 16 pixels height per fruit version
    int fruitWidth = 16;
    int fruitHeight = 16;

    QPixmap fruit = mFruits.copy(fruitX, fruitY, fruitWidth, fruitHeight);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(fruit);
    item->setPos(x, y);
    mScene->addItem(item);
}

void MainWindow::updateLCD()
{
    // Increment counter by 0.01 (which corresponds to hundredths of a second)
    count += 0.01;

    // Round the number to two decimal places
    double roundedCount = std::round(count * 100.0) / 100.0;

    // Format the number as a string with leading zeroes
    QString str = QString("%1").arg(roundedCount, 5, 'f', 2, '0');

    // Display the formatted string
    lcd->display(str);
}




void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    int lcdWidth = 200;
    int lcdHeight = 50;
    int margin = 10;
    lcd->setGeometry(QRect(QPoint(this->width() - lcdWidth - margin, margin), QSize(lcdWidth, lcdHeight)));
}




void MainWindow::onFoxStoppedMoving() {
    timer->stop();
    lcd->hide();
}

void MainWindow::onRibbonAnimationFinished() {
    // Position the LCD just outside the top edge of the window
    lcd->move((this->width() - lcd->width()) / 2, -lcd->height());

    // Display the LCD
    lcd->show();

    // Create a QPropertyAnimation to animate the geometry of the LCD
    QPropertyAnimation *animation = new QPropertyAnimation(lcd, "geometry");

    // Set the duration of the animation
    animation->setDuration(1000); // 1 second

    // Set the start and end values for the geometry
    QRect startRect((this->width() - lcd->width()) / 2, -lcd->height(), lcd->width(), lcd->height());

    // Calculate the center position of the ribbon
    int ribbonCenterX = this->width() / 2;
    int ribbonCenterY = ribbonPixmap.height();

    // Calculate new endRect considering the ribbon width
    int newX = ribbonCenterX - (lcd->width() / 2); // center lcd with respect to the ribbon
    int newY = ribbonCenterY + ribbonPixmap.height() + 10; // place it 10 pixels below the ribbon
    QRect endRect(newX, newY, lcd->width(), lcd->height());


    animation->setStartValue(startRect);
    animation->setEndValue(endRect);

    // Start the animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}






#include <QGraphicsItemAnimation>
#include <QTimeLine>

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_P: {
        timer->stop();
            // Store the fox's current position
            QPointF lastPosition = foxSprite->pos();

            foxSprite->stopMoving();

            // Set the fox's position back to its last position
            foxSprite->setPos(lastPosition);

            QPixmap ribbonPixmap(":/userInterface/sprites/userInterface/ribbon.png");
            QGraphicsPixmapItem *ribbonItem = new QGraphicsPixmapItem(ribbonPixmap);

            // Center the ribbon at the top of the window
           ribbonX = (this->width() - ribbonPixmap.width()) / 2 - 100;


            ribbonY = 0;
            ribbonItem->setScale(1.0); // Initial scale

            ribbonItem->setPos(ribbonX, ribbonY);
            mScene->addItem(ribbonItem);

            // Create a QGraphicsItemAnimation to animate the ribbonItem's scale
            QGraphicsItemAnimation *itemAnimation = new QGraphicsItemAnimation;
            itemAnimation->setItem(ribbonItem);

            // Create a QTimeLine for the animation
            QTimeLine *timeLine = new QTimeLine(1000); // Set the duration for the animation (in milliseconds)
            timeLine->setFrameRange(0, 100); // Set the frame range for the animation

            // Connect the timeLine's frameChanged signal to update the scale of the ribbonItem
            connect(timeLine, &QTimeLine::frameChanged, this, [=](int frame) {
                qreal scale = 1.0 + static_cast<qreal>(frame) / 100.0; // Calculate the scale value based on the frame
                ribbonItem->setScale(scale);
            });

            // Connect the timeLine's finished signal to the onRibbonAnimationFinished slot
            connect(timeLine, &QTimeLine::finished, this, &MainWindow::onRibbonAnimationFinished);

            // Start the animation
            timeLine->start();

            break;
        }
        default:
            QMainWindow::keyPressEvent(event);
    }
}
