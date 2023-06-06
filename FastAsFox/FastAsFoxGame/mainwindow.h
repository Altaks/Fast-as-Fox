#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QLCDNumber>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString score=QString();
    QLCDNumber score2;
    QElapsedTimer timer;
    QTimer clock;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void DisplayScore(float time);
};
#endif // MAINWINDOW_H
