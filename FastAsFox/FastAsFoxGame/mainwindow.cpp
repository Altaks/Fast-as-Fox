#include "mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include "level.h"
#include "mapsection.h"
#include "constants.h"
#include "map.h"
#include <QCoreApplication>
#include <QProcess>

#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <QThread>


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


    // Skipping the menu
    //m_menuWidget->skipMenu();

    bool isRestarting = false;
}

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
    case Qt::Key::Key_Q:
    case Qt::Key::Key_Left:
        this->level->getPlayer()->playerSlowedDown();
        break;
    default:
        break;
    }

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



void MainWindow::resizeEvent(QResizeEvent *event) {
        QMainWindow::resizeEvent(event);
        if (level!=nullptr) {
            level->updateLCDPosition();
        }
}




void MainWindow::handleMenuFinished()
{
    set = new TileSet(GROUND_TILES, TILE_SIZE, 1);
    section = new MapSection(LEVEL_ONE);

    tilesets = new std::vector<TileSet*>();
    tilesets->push_back(set);

    map = new Map(section, tilesets);
    map->load();

    level = new Level(LEVEL_ONE_START_POS,map,this);

    //QPixmap background(":/texture/sprites/texture/bg.jpg");
    //level->getScene()->setBackgroundBrush(background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    level->start();
    //connect(level->getPlayer(),SIGNAL(playerMoved()),level,SLOT(finish()));
    //QObject::connect(map, &Map::golevelMenu, this, &MainWindow::handleLevelMenu);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isRestarting)
    {
        writeToFile(false);
    }

    QWidget::closeEvent(event);
}

void MainWindow::handleLevelMenu()
{
    isRestarting = true;
    writeToFile(true);

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

