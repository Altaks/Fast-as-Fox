#include "mainwindow.h"
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include "powerup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    int fontId = QFontDatabase::addApplicationFont(":/font/sprites/font/font.TTF");
    QString fontFamily;
    if (fontId != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }


    level = nullptr;
    int nbMode = 4; // Default value

    QFile file(QCoreApplication::applicationDirPath() + "restart.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        bool ok;
        int val = in.readLine().toInt(&ok);
        if (ok)
        {
            nbMode = val;
        }
        else
        {
            qDebug() << "Failed to convert file content to int";
        }
        file.close();
    }
    else
    {
        qDebug() << "Failed to open the file";
    }

    m_menuWidget = new MenuWidget(this, 4, nbMode);
    setCentralWidget(m_menuWidget);
    //connect(m_menuWidget, &MenuWidget::levelSelected, this, &MainWindow::handleLevelSelection);
    connect(m_menuWidget, &MenuWidget::finished, this, &MainWindow::handleMenuFinished);
    connect(m_menuWidget, &MenuWidget::levelSelected, this, &MainWindow::setLevelN);


    // Skipping the menu
    //m_menuWidget->skipMenu();

    this->installEventFilter(this);
}
/**
 * @brief Writes a value to a file.
 *
 * The function writes a boolean value to a file named "restart.txt" in the application's directory.
 * If the file is successfully opened, the value is written as a string ("1" for true, "0" for false).
 * If the file cannot be opened, an error message is printed to the debug output.
 *
 * @param value The boolean value to be written to the file.
 */
void MainWindow::writeToFile(bool value) {
    QFile file(QCoreApplication::applicationDirPath() + "restart.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << (value ? "1" : "0");
        file.close();
    }
    else
    {
        qDebug() << "Failed to open file for writing.";
    }
}


void MainWindow::keyPressEvent(QKeyEvent * event){
    switch (event->key()) {
    case Qt::Key::Key_Z:
    case Qt::Key::Key_Up:
        this->level->getPlayer()->playerJumped();
        break;
    case Qt::Key::Key_D:
    case Qt::Key::Key_Right:
        this->level->getPlayer()->playerAccelerated();
        break;
    case Qt::Key::Key_E:
            if(this->level->getPlayer()->getStockedPowerUp() != nullptr){
                this->level->getPlayer()->getStockedPowerUp()->applyEffect(this->level, this->level->getPlayer());
            }
    case Qt::Key::Key_Q:
    case Qt::Key::Key_Left:
        this->level->getPlayer()->playerSlowedDown();
        break;
    default:
        break;
    }

}

void MainWindow::setLevelN(int newLevelN)
{
    levelN = newLevelN;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
        QMainWindow::resizeEvent(event);
        if (level!=nullptr) {
            level->updateLCDPosition();
        }
}

/**
 * @brief Handles the finished event of the menu.
 *
 * The function is called when the menu has finished, indicating that the game should start.
 * It initializes the TileSet and MapSection objects, creates a vector of TileSet pointers,
 * and loads the map. It also creates a Level object with the specified level number and starting position,
 * sets the background image of the level's scene, and starts the level.
 */
void MainWindow::handleMenuFinished()
{
    TileSet * set = new TileSet(GROUND_TILES, true, TILE_SIZE, 1);
    TileSet * propsSet = new TileSet(PROPS_TILES, false, TILE_SIZE, 257);

    section = new MapSection(LEVELS.at(levelN));

    tilesets = new std::vector<TileSet*>();
    tilesets->push_back(set);
    tilesets->push_back(propsSet);


    map = new Map(section, tilesets);
    map->load();
    level = new Level(levelN,LEVEL_START_POS.at(levelN),map,this);

    //QPixmap background(":/texture/sprites/texture/bg.jpg");
    //level->getScene()->setBackgroundBrush(background.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));


    level->start();
    connect(level->getPlayer(),SIGNAL(playerMoved()),level,SLOT(finish()));
    QObject::connect(map, &Map::golevelMenu, this, &MainWindow::handleLevelMenu);

}

/**
 * @brief Handles the close event for the main window.
 *
 * The function is called when the main window is about to be closed.
 * If the application is not restarting, it writes to a file. It then passes
 * the close event to the parent class to perform the default close behavior.
 *
 * @param event A pointer to the QCloseEvent object that contains details about the event.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isRestarting)
    {
        writeToFile(false);
    }

    QWidget::closeEvent(event);
}

/**
 * @brief Handles the level menu action.
 *
 * The function is called when the level menu action is triggered.
 * It sets the flag isRestarting to true, writes to a file, quits the application,
 * and restarts the application with the same arguments.
 */
void MainWindow::handleLevelMenu()
{
    isRestarting = true;
    writeToFile(true);

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

