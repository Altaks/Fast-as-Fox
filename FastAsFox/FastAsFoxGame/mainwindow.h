#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QRandomGenerator>
#include <QPushButton>
#include "animatedsprite.h"
#include <QLCDNumber>
#include <QKeyEvent>
#include "level.h"
#include "map.h"
#include "menuwidget.h"
#include <QCoreApplication>
#include <QProcess>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <QThread>


class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr);
    //void displayFruit(FruitType fruitType, int versionId, int x, int y);
    void keyPressEvent(QKeyEvent *event);
    void showEndOfMapMessage();
    void handleLevelSelection(int levelIndex);
    void writeToFile(bool value);
    void handleLevelMenu();
    void handleMenuFinished();

    void resizeEvent(QResizeEvent *event) ;
    void closeEvent(QCloseEvent *event) ;

private slots:
    void addText();
    void printText(const QString &text, int x, int y, int z, const QColor &color);
    void updateLCD();

private:
    QString mFontFamily;
    QGraphicsScene *mScene;
    QPixmap mFruits;
    QTimer *timer;
    QLCDNumber *lcd;
    double count;
    Fox* foxSprite;
    Map *map;
    TileSet * set;
    MapSection * section;
    std::vector<TileSet*>* tilesets;
    int height=25;
    int  weight=30;
    Level * level;
    MenuWidget *m_menuWidget;
    bool isRestarting;


};

#endif // MAINWINDOW_H
