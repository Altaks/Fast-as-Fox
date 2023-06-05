#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // load the font from resources
    int fontId = QFontDatabase::addApplicationFont(":/font/sprites/font/font.TTF");
    QString fontFamily;
    if (fontId != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    // create a scene and view to display text
    mScene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(mScene, this);
    setCentralWidget(view);

    // create a button that adds random text when clicked
    QPushButton *button = new QPushButton("Add Text", this);
    button->setGeometry(10, 10, 80, 30);

    // save font family for use in printText
    mFontFamily = fontFamily;

    // connect button to printText function
    connect(button, &QPushButton::clicked, this, &MainWindow::addText);
}

void MainWindow::addText() {
    printText("Bonjour a tous !", 100, 200, 20, QColor(Qt::red));
    printText("La vie est belle.", 150, 250, 20, QColor(Qt::green));
    printText("Les chiens jouent dans le parc.", 200, 300, 20, QColor(Qt::blue));
    printText("La lutte des classes est le moteur de l'histoire", 300, 400, 20, QColor(Qt::black));

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

