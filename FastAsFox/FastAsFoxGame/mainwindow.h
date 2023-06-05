#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRandomGenerator>
#include <QPushButton>

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addText();
    void printText(const QString &text, int x, int y, int z, const QColor &color);

private:
    QString mFontFamily;
    QGraphicsScene *mScene;
};

#endif // MAINWINDOW_H
