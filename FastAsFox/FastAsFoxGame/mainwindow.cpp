﻿#include "mainwindow.h"
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

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

    int fontId = QFontDatabase::addApplicationFont(":/font/sprites/font/font.TTF");
    QString fontFamily;
    if (fontId != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

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

    if (event->key() == Qt::Key_P)
    {
        isRestarting = true;
        writeToFile(true);

        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
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

/*void MainWindow::displayFruit(FruitType fruitType, int versionId, int x, int y)
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
}*/


void MainWindow::resizeEvent(QResizeEvent *event) {
//    QMainWindow::resizeEvent(event);
//    if (!m_menuWidget->isMenuSkipped()) {
//        level->updateLCDPosition();
//    }
}




void MainWindow::handleMenuFinished()
{
    TileSet * set = new TileSet(GROUND_TILES, TILE_SIZE, 1);
    MapSection * section = new MapSection(LEVEL_ONE);

    std::vector<TileSet*>* tilesets = new std::vector<TileSet*>();
    tilesets->push_back(set);

    Map * map = new Map(section, tilesets);
    map->load();
    level = new Level(LEVEL_ONE_START_POS,map,this);

    QPixmap background(":/texture/sprites/texture/bg.jpg");
    level->getScene()->setBackgroundBrush(background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    level->start();
    connect(level->getPlayer(),SIGNAL(playerMoved()),level,SLOT(finish()));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isRestarting)
    {
        writeToFile(false);
    }

    QWidget::closeEvent(event);
}
