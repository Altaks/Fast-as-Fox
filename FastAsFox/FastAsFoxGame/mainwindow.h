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

/*enum class FruitType {
    Apple,
    Grape,
    Cherry,
    Lemon,
    Peach,
    // Add other fruit types here as needed
};*/

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr);
    //void displayFruit(FruitType fruitType, int versionId, int x, int y);
    void showEndOfMapMessage();
    void handleLevelSelection(int levelIndex);
    void handleMenuFinished();


private slots:
    void addText();
    void printText(const QString &text, int x, int y, int z, const QColor &color);
    void updateLCD();
    void onHomeButtonClicked();

private:
    QString mFontFamily;
    QGraphicsScene *mScene;
    QPixmap mFruits;
    QTimer *timer;
    QLCDNumber *lcd;
    double count;
    Fox* foxSprite;
    Map *map;
    int height=25;
    int  weight=30;
    MenuWidget *m_menuWidget;
    Level * level;



protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
