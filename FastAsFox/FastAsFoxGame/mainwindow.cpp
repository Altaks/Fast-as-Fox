#include "mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include "level.h"
#include "mapsection.h"
#include "constants.h"
#include "map.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_menuWidget = new MenuWidget(this,4);
    setCentralWidget(m_menuWidget);
    //connect(m_menuWidget, &MenuWidget::levelSelected, this, &MainWindow::handleLevelSelection);
    connect(m_menuWidget, &MenuWidget::finished, this, &MainWindow::handleMenuFinished);

    int fontId = QFontDatabase::addApplicationFont(":/font/sprites/font/font.TTF");
    QString fontFamily;
    if (fontId != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    // Skipping the menu
    m_menuWidget->skipMenu();
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
    level->start();
    connect(level->getPlayer(),SIGNAL(playerMoved()),level,SLOT(finish()));
}
