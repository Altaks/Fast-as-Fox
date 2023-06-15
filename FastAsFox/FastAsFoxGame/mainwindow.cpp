#include "mainwindow.h"
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>

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
    connect(m_menuWidget, &MenuWidget::levelSelected, this, &MainWindow::setLevelN);


    // Skipping the menu
    //m_menuWidget->skipMenu();

    this->installEventFilter(this);
}
/**
 * @brief Writes a value to a file.
 *
 * The function writes a boolean value to a file named "restart.txt" in the application's directory.
 * If the file is successfully opened, the value is written as a string ("1" for true, "0" for false).
 * If the file cannot be opened, an error message is printed to the debug output.
 *
 * @param value The boolean value to be written to the file.
 */
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

void MainWindow::setLevelN(int newLevelN)
{
    levelN = newLevelN;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
        QMainWindow::resizeEvent(event);
        if (level!=nullptr) {
            level->updateLCDPosition();
        }
}

/**
 * @brief Handles the finished event of the menu.
 *
 * The function is called when the menu has finished, indicating that the game should start.
 * It initializes the TileSet and MapSection objects, creates a vector of TileSet pointers,
 * and loads the map. It also creates a Level object with the specified level number and starting position,
 * sets the background image of the level's scene, and starts the level.
 */
void MainWindow::handleMenuFinished()
{
    set = new TileSet(GROUND_TILES, TILE_SIZE, 1);
    section = new MapSection(LEVELS.at(levelN));

    tilesets = new std::vector<TileSet*>();
    tilesets->push_back(set);

    map = new Map(section, tilesets);
    map->load();
    level = new Level(levelN,LEVEL_START_POS.at(levelN),map,this);

    QPixmap background(":/texture/sprites/texture/bg.jpg");
    level->getScene()->setBackgroundBrush(background.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));


    level->start();
    //connect(level->getPlayer(),SIGNAL(playerMoved()),level,SLOT(finish()));
    //QObject::connect(map, &Map::golevelMenu, this, &MainWindow::handleLevelMenu);

}

/**
 * @brief Handles the close event for the main window.
 *
 * The function is called when the main window is about to be closed.
 * If the application is not restarting, it writes to a file. It then passes
 * the close event to the parent class to perform the default close behavior.
 *
 * @param event A pointer to the QCloseEvent object that contains details about the event.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isRestarting)
    {
        writeToFile(false);
    }

    QWidget::closeEvent(event);
}

/**
 * @brief Handles the level menu action.
 *
 * The function is called when the level menu action is triggered.
 * It sets the flag isRestarting to true, writes to a file, quits the application,
 * and restarts the application with the same arguments.
 */
void MainWindow::handleLevelMenu()
{
    isRestarting = true;
    writeToFile(true);

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
/**
 * @brief Handles the mouse press event for the main window.
 *
 * The function is called when a mouse button is pressed on the main window.
 * If the left mouse button is pressed, it captures a screenshot of the window,
 * prompts the user for text input, wraps the text, draws it on the screenshot,
 * and saves the screenshot to a file.
 *
 * @param event A pointer to the QMouseEvent object that contains details about the event.
 */
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
/**
 * @brief Filters events for the main window.
 *
 * The function filters events for the main window and handles the MouseButtonPress event.
 * If the clicked widget is a button, the function ignores the click. Otherwise, it performs
 * the usual tasks, including capturing a screenshot, prompting the user for text input,
 * drawing the text on the screenshot, and saving the screenshot. Finally, it passes the event
 * to the parent class.
 *
 * @param obj   The object that triggered the event.
 * @param event The event to be filtered.
 *
 * @return @c true if the event was handled, @c false otherwise.
 */
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
/**
 * @brief Draws a rectangle with text on the specified image at the given position.
 *
 * The function draws a rectangle with the specified text on the provided image,
 * centered at the given position. It also creates a new issue in GitLab with the
 * current position and text.
 *
 * @param image The image to draw on, passed as a QPixmap reference.
 * @param pos   The position to draw the rectangle and text, specified as a QPoint.
 * @param text  The text to be displayed inside the rectangle.
 */
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

    // Create a new issue in GitLab with the current position and text
    createGitlabIssue(pos, text);

    painter.end();
}
/**
 * @brief Retrieves the path for saving a screenshot.
 *
 * The function generates a directory path and filename for saving a screenshot.
 * The directory path is created if it doesn't exist.
 *
 * @return The path for saving the screenshot, formatted as a QString.
 */
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
/**
 * @brief Creates a GitLab issue with the specified position and text.
 *
 * @param pos  The position of the issue.
 * @param text The text content of the issue.
 */
void MainWindow::createGitlabIssue(const QPoint &pos, const QString &text)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString token = "glpat-Yw-5FffG8xsEz7xRCQLh";
    QString issueTitle = text;  // The title is now the same as the text
    QString issueDescription = QString("Coord %1 %2 : %3").arg(pos.x()).arg(pos.y()).arg(text);
    int projectId = 4894;
    int assigneeId = 745;

    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://forge.iut-larochelle.fr/api/v4/projects/%1/issues").arg(projectId)));
    request.setRawHeader("PRIVATE-TOKEN", token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("title", issueTitle);  // Use the text as the issue title
    json.insert("description", issueDescription);
    json.insert("assignee_ids", QJsonArray::fromVariantList({assigneeId}));
    json.insert("labels", "To Do");  // Add the To Do label

    QNetworkReply* reply = manager->post(request, QJsonDocument(json).toJson());

    // Error handling
    connect(reply, &QNetworkReply::finished, [reply]() {
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();  // This will print the response body
        } else {
            qDebug() << "Issue created successfully.";
        }
        reply->deleteLater();
    });
}
