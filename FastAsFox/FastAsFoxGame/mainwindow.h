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

private:
    QString mFontFamily;
    QGraphicsScene *mScene;
    QPixmap mFruits;
};

#endif // MAINWINDOW_H
