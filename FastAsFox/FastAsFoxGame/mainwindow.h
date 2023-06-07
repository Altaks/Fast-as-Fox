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
#include "fox.h"
#include <QLCDNumber>
#include "map.h"

enum class FruitType {
    Apple,
    Grape,
    Cherry,
    Lemon,
    Peach,
    // Add other fruit types here as needed
};


class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr);
    void displayFruit(FruitType fruitType, int versionId, int x, int y);

private slots:
    void addText();
    void printText(const QString &text, int x, int y, int z, const QColor &color);
    void updateLCD();
    void resetGame();
    void onFoxReachedEnd();
    void keyPressEvent(QKeyEvent *event);
    void onFoxStoppedMoving();
    void onRibbonAnimationFinished();

private:
    QString mFontFamily;
    QGraphicsScene *mScene;
    QPixmap mFruits;
    QTimer *timer;
    QLCDNumber *lcd;
    double count;
    Fox* foxSprite;
    Map *map;
    int windowHeight;  // Renamed from 'height'
    int windowWidth;   // Renamed from 'width'
    QPixmap ribbonPixmap;
    int ribbonX;
    int ribbonY;
    double deadZoneWidth;
    QGraphicsView *view;


protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // MAINWINDOW_H
