#include "mainwindow.h"
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    int fontId = QFontDatabase::addApplicationFont(":/font/sprites/font/font.TTF");
    QString fontFamily;
    if (fontId != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }


    level = nullptr;
    int nbMode = 4; // Default value

    QFile file(QCoreApplication::applicationDirPath() + "restart.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        bool ok;
        int val = in.readLine().toInt(&ok);
        if (ok)
        {
            nbMode = val;
        }
        else
        {
            qDebug() << "Failed to convert file content to int";
        }
        file.close();
    }
    else
    {
        qDebug() << "Failed to open the file";
    }

    m_menuWidget = new MenuWidget(this, 4, nbMode);
    setCentralWidget(m_menuWidget);
    //connect(m_menuWidget, &MenuWidget::levelSelected, this, &MainWindow::handleLevelSelection);
    connect(m_menuWidget, &MenuWidget::finished, this, &MainWindow::handleMenuFinished);


    // Skipping the menu
    //m_menuWidget->skipMenu();

    this->installEventFilter(this);
}

void MainWindow::writeToFile(bool value) {
    QFile file(QCoreApplication::applicationDirPath() + "restart.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << (value ? "1" : "0");
        file.close();
    }
    else
    {
        qDebug() << "Failed to open file for writing.";
    }
}


void MainWindow::keyPressEvent(QKeyEvent * event){
    switch (event->key()) {
    case Qt::Key::Key_Z:
    case Qt::Key::Key_Up:
        this->level->getPlayer()->playerJumped();
        break;
    case Qt::Key::Key_D:
    case Qt::Key::Key_Right:
        this->level->getPlayer()->playerAccelerated();
        break;
    case Qt::Key::Key_Q:
    case Qt::Key::Key_Left:
        this->level->getPlayer()->playerSlowedDown();
        break;
    default:
        break;
    }

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



void MainWindow::resizeEvent(QResizeEvent *event) {
        QMainWindow::resizeEvent(event);
        if (level!=nullptr) {
            level->updateLCDPosition();
        }
}




void MainWindow::handleMenuFinished()
{
    set = new TileSet(GROUND_TILES, TILE_SIZE, 1);
    section = new MapSection(LEVEL_ONE);

    tilesets = new std::vector<TileSet*>();
    tilesets->push_back(set);

    map = new Map(section, tilesets);
    map->load();
    GameObject * gameobjectvitefait;
    gameobjectvitefait = new GameObject();
    level = new Level(LEVEL_ONE_START_POS,gameobjectvitefait,map,this);

    QPixmap background(":/texture/sprites/texture/bg.jpg");
    level->getScene()->setBackgroundBrush(background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    level->start();
    //connect(level->getPlayer(),SIGNAL(playerMoved()),level,SLOT(finish()));
    //QObject::connect(map, &Map::golevelMenu, this, &MainWindow::handleLevelMenu);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isRestarting)
    {
        writeToFile(false);
    }

    QWidget::closeEvent(event);
}

void MainWindow::handleLevelMenu()
{
    isRestarting = true;
    writeToFile(true);

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_lastClickedPos = event->pos();

        QPixmap screenshot = this->grab();

        bool ok;
        QString rawText = QInputDialog::getText(this, tr("Input Dialog"), tr("Enter text:"), QLineEdit::Normal, "", &ok);
        if (ok && !rawText.isEmpty()) {
            const int maxCharPerLine = 30;  // Adjust this value according to your needs
            QString wrappedText;
            while (!rawText.isEmpty()) {
                QString line = rawText.left(maxCharPerLine);
                rawText.remove(0, line.length());
                wrappedText.append(line + "\n");
            }

            drawOnImage(screenshot, m_lastClickedPos, wrappedText);

            QString screenshotPath = getScreenshotPath();
            screenshot.save(screenshotPath);
        }
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // check if the clicked widget is a button
        QWidget *clickedWidget = this->childAt(mouseEvent->pos());
        if (clickedWidget && qobject_cast<QPushButton*>(clickedWidget)) {
            // if it's a button, ignore the click
            return false;
        }

        // perform usual tasks
        if (mouseEvent->button() == Qt::LeftButton) {
            m_lastClickedPos = mouseEvent->pos();

            QPixmap screenshot = this->grab();

            bool ok;
            QString rawText = QInputDialog::getText(this, tr("Input Dialog"), tr("Enter text:"), QLineEdit::Normal, "", &ok);
            if (ok && !rawText.isEmpty()) {
                const int maxCharPerLine = 30;  // Adjust this value according to your needs
                QString wrappedText;
                while (!rawText.isEmpty()) {
                    QString line = rawText.left(maxCharPerLine);
                    rawText.remove(0, line.length());
                    wrappedText.append(line + "\n");
                }

                drawOnImage(screenshot, m_lastClickedPos, wrappedText);

                QString screenshotPath = getScreenshotPath();
                screenshot.save(screenshotPath);
            }

            return true;
        }
    }

    // pass the event on to the parent class
    return QMainWindow::eventFilter(obj, event);
}
void MainWindow::drawOnImage(QPixmap &image, const QPoint &pos, const QString &text)
{
    QFont font;
    font.setPointSize(12);  // adjust size according to your need
    QFontMetrics fm(font);
    QRect textRect = fm.boundingRect(QRect(pos, image.size()), Qt::TextWordWrap, text);
    textRect += QMargins(10, 10, 10, 10); // add some padding around text

    QPainter painter(&image);
    painter.setBrush(Qt::white); // fill color
    painter.setPen(Qt::black); // border color
    painter.drawRect(textRect);

    painter.setFont(font);
    painter.setPen(Qt::black); // text color
    painter.drawText(textRect, Qt::AlignCenter | Qt::TextWordWrap, text); // draw text centered in the rectangle

    painter.end();
}

QString MainWindow::getScreenshotPath()
{
    QString screenshotDir = QCoreApplication::applicationDirPath() + "/todo";
    QDir dir(screenshotDir);

    // create the directory if it doesn't exist
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // format the current date/time as a string
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss");

    return screenshotDir + QString("/screenshot-%1.png").arg(timestamp);
}
