#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QLabel>


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString score=QString();
    QElapsedTimer timer;
    QLabel label;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DisplayScore();
    void paintEvent(QPaintEvent* event);
};
#endif // MAINWINDOW_H
