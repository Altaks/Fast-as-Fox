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
#include <QTimer>
#include <QMessageBox>
#include "level.h"
#include "mapsection.h"
#include "constants.h"
#include "map.h"
#include <QCoreApplication>
#include <QProcess>
#include <QLineEdit>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QThread>
#include <QDir>
#include <QNetworkAccessManager>
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
    void drawOnImage(QPixmap &image, const QPoint &pos, const QString &text);
    QString getScreenshotPath();
    void createGitlabIssue(const QPoint &pos, const QString &text);

    void setLevelN(int newLevelN);

private slots:
    void addText();
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
    int levelN;
    Level * level;
    MenuWidget *m_menuWidget;
    bool isRestarting;
    QPoint m_lastClickedPos;


protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
