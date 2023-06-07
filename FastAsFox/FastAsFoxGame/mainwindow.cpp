#include "mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include "animatedsprite.h"
#include "mapsection.h"
#include "constants.h"
#include "map.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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

    // create a scene and view to display text
    mScene = map->getScene();
    QGraphicsView *view = map->getView();
    setCentralWidget(view);


    // save font family for use in printText
    mFontFamily = fontFamily;

    mFruits = QPixmap(":/fruits/sprites/fruits/fruits.png");

//    // Test the displayFruit function
//    displayFruit(FruitType::Lemon, 0, 100, 100);

//    // create a button that adds random text when clicked
//    QPushButton *button = new QPushButton("Add Text", this);
//    button->setGeometry(10, 10, 80, 30);
//    // connect button to printText function
//    connect(button, &QPushButton::clicked, this, &MainWindow::addText);


    // Initialize the LCD number
    lcd = new QLCDNumber(this);
    lcd->setDigitCount(7);  // 2 digits for integer part, 1 dot, 2 digits for fraction part
    lcd->setMode(QLCDNumber::Dec);
    lcd->setSegmentStyle(QLCDNumber::Flat);
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
    foxSprite = new Fox(mScene);


}

void MainWindow::addText() {
    printText("Bonjour a tous !", 100, 200, 20, QColor(Qt::red));
    printText("La vie est belle.", 150, 250, 20, QColor(Qt::green));
    printText("Les chiens jouent dans le parc.", 200, 300, 20, QColor(Qt::blue));
    printText("La lutte des classes est le moteur de l'histoire", 300, 400, 20, QColor(Qt::black));

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

void MainWindow::showEndOfMapMessage() {
    QMessageBox::information(this, "Game over", "Le renard a atteint la fin de la map !");
}

