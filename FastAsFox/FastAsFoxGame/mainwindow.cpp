#include "mainwindow.h"

#include <QString>
#include <QPainter>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    timer.start();
    DisplayScore();
    this->repaint();
}

MainWindow::~MainWindow()
{
}

void MainWindow::DisplayScore(){
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent* event){
    Q_UNUSED(this);
    QPainter *painter = new QPainter(this);


    float time=0;
    time+=timer.elapsed()/1000;
    this->score.setNum(time,'g',2);


    painter->drawText(10,10,QString::fromStdString(std::to_string(time)));
    delete painter;
}

