#include "menuwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMovie>
#include <QApplication>
#include <QTimer>
#include <iostream>
#include <QPushButton>
#include <QAudioOutput>
#include "animatedsprite.h"
#include <QFile>
#include <functional>


MenuWidget::MenuWidget(QWidget *parent, int aNumberOfLevelsUnlocked, int isRestart) : QWidget(parent), m_layout(new QGridLayout), m_currentActiveFrame(0),playButtonClickedOnce(false), settingsButtonClickedOnce(false)
{
    numberOfLevelsUnlocked = aNumberOfLevelsUnlocked;


    // Setup audio
    m_selectPlayer = new QMediaPlayer(this);
    m_selectPlayer->setSource(QUrl("qrc:/menu/sprites/menu/menuSelection.mp3"));
    QAudioOutput *selectOutput = new QAudioOutput(this);
    m_selectPlayer->setAudioOutput(selectOutput);
    m_selectedPlayer = new QMediaPlayer(this);
    m_selectedPlayer->setSource(QUrl("qrc:/menu/sprites/menu/menuSelected.mp3"));
    QAudioOutput *selectedOutput = new QAudioOutput(this);
    m_selectedPlayer->setAudioOutput(selectedOutput);


    m_sagaPlayer = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput;
    m_sagaPlayer->setAudioOutput(audioOutput);
    m_sagaPlayer->setSource(QUrl("qrc:/menu/sprites/menu/saga.mp3"));

    this->setFocusPolicy(Qt::StrongFocus);

    // Load the cursor image.
    QPixmap cursorPixmap(":/menu/sprites/menu/pointeurMouse.png");
    m_customCursor = QCursor(cursorPixmap, -1, -1);

    menuSkipped = false;

    //isRestart=1 => Le programme vient de redémarrer
    if (isRestart==1)
    {
        initMenu();
    }
    else{
        saga();
    }

}


void MenuWidget::setBackgroundImage(const QString &imagePath)
{
    m_backgroundImage.load(imagePath);
    update(); // Request a repaint to show the new background image
}

void MenuWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_backgroundImage.scaled(size()));
}

void MenuWidget::setupImagesLayout()
{
    int numImages = 10;
    int maxPerRow = 5;
    int verticalSpacing = 150;

    // Load the custom font.
    int fontId = QFontDatabase::addApplicationFont(":/menu/sprites/menu/font.TTF");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(family, 50);

    // Set up a QGraphicsScene and QGraphicsTextItem for the title with outline.
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsTextItem *titleItem = new QGraphicsTextItem("Choose your level!");
    titleItem->setFont(customFont);
    titleItem->setDefaultTextColor(Qt::black);

    // Create a QGraphicsDropShadowEffect for the outline.
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(0); // No blur for a clean outline.
    effect->setColor(Qt::white); // White outline.
    effect->setOffset(0); // No offset for an even outline.
    titleItem->setGraphicsEffect(effect);

    scene->addItem(titleItem);

    titleView = new QGraphicsView(scene, this);
    titleView->setAlignment(Qt::AlignCenter);
    titleView->setStyleSheet("background-color: transparent;");
    titleView->setFrameShape(QFrame::NoFrame);


    // This widget holds the images.
    QWidget *imageHolder = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(imageHolder);
    gridLayout->setVerticalSpacing(verticalSpacing);

    for (int i = 0; i < numImages; ++i) {
        // This widget holds an image and its information.
        QWidget *frame = new QWidget;
        QVBoxLayout *vbox = new QVBoxLayout(frame);

        QLabel *imageLabel = new QLabel;

        // Load base image.
        QPixmap baseImage(":/menu/sprites/menu/"+QString::number(i+1) + ".jpg");

        if (i >= numberOfLevelsUnlocked) {
            // Convert all images after the first two to grayscale
            QImage image = baseImage.toImage();
            image = image.convertToFormat(QImage::Format_Grayscale8);
            baseImage = QPixmap::fromImage(image);
        }

        baseImage = baseImage.scaled(QSize(200, 150), Qt::IgnoreAspectRatio);

        // Load overlay image.
        QPixmap overlayImage(":/menu/sprites/menu/framelevel.png");
        overlayImage = overlayImage.scaled(QSize(200, 150), Qt::IgnoreAspectRatio);

        // Paint the overlay image on top of the base image.
        QPainter painter(&baseImage);
        painter.drawPixmap(0, 0, overlayImage);
        painter.end();

        // Use the combined image.
        imageLabel->setPixmap(baseImage);

        int fontId = QFontDatabase::addApplicationFont(":/menu/sprites/menu/retro.ttf");
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QString styleSheet = QString("background-color: black; color: white; font-family: '%1'; font-size: 20px; border-radius: 15px; padding: 10px;").arg(family);

        infoLabel = new QLabel(QString("Level: %1\nNumber of coins collected: %2\nRecord time: %3 seconds")
                                   .arg(i + 1).arg(rand() % 100).arg(rand() % 60));
        infoLabel->setStyleSheet(styleSheet);
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->hide();

        vbox->addWidget(imageLabel);
        vbox->addWidget(infoLabel);

        int row = i / maxPerRow;
        int col = i % maxPerRow;
        gridLayout->addWidget(frame, row, col);

        m_imageLabels.append(imageLabel);
        m_infoLabels.append(infoLabel);

        // Create a drop shadow effect
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setColor(Qt::white);
        effect->setBlurRadius(70);
        effect->setOffset(0);
        imageLabel->setGraphicsEffect(effect);
        effect->setEnabled(false); // Initially disabled
    }

    // Enable effect for the active frame and show its info
    dynamic_cast<QGraphicsDropShadowEffect*>(m_imageLabels[m_currentActiveFrame]->graphicsEffect())->setEnabled(true);
    m_infoLabels[m_currentActiveFrame]->show();

    // Add a gif below the images.
    QMovie *movie = new QMovie(":/menu/sprites/menu/foxwaiting.gif");
    gifLabel = new QLabel;
    gifLabel->setMovie(movie);
    movie->start();

    // Add the titleView, imageHolder, and gif to the layout.
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(titleView);
    QHBoxLayout *hLayout = new QHBoxLayout();

    // Push the imageHolder to the center.
    hLayout->addStretch();
    hLayout->addWidget(imageHolder);
    hLayout->addStretch();

    vLayout->addLayout(hLayout);

    // Create a layout for the gif and push the gif to the center.
    QHBoxLayout *gifLayout = new QHBoxLayout;
    gifLayout->addStretch();
    gifLayout->addWidget(gifLabel);
    gifLayout->addStretch();

    vLayout->addLayout(gifLayout); // Add the layout for the gif below the imageHolder.
    vLayout->addStretch();

    this->setLayout(vLayout);
}


void MenuWidget::keyPressEvent(QKeyEvent *event)
{
    // Temporary variable to store the new active frame
    int newActiveFrame = m_currentActiveFrame;

    // Change the current active frame based on the key input
    if (event->key() == Qt::Key_Z)
        newActiveFrame = std::max(0, m_currentActiveFrame - 5); // 5 is the number of frames per row
    else if (event->key() == Qt::Key_S)
        newActiveFrame = std::min(numberOfLevelsUnlocked - 1, m_currentActiveFrame + 5);
    else if (event->key() == Qt::Key_Q)
        newActiveFrame = std::max(0, m_currentActiveFrame - 1);
    else if (event->key() == Qt::Key_D)
        newActiveFrame = std::min(numberOfLevelsUnlocked - 1, m_currentActiveFrame + 1);
    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (newActiveFrame < numberOfLevelsUnlocked) {
            m_infoLabels[m_currentActiveFrame]->hide();
            m_selectedPlayer->play();
            animateSelection();
            selectedLevelIndex = newActiveFrame;
            // Emit signal
            emit levelSelected(selectedLevelIndex);

            // Restore the cursor to its normal design
            QCursor normalCursor(Qt::ArrowCursor);
            QApplication::setOverrideCursor(normalCursor);
            return;
        }
    }

    // Ensure the new active frame doesn't exceed the number of levels unlocked
    newActiveFrame = std::min(newActiveFrame, numberOfLevelsUnlocked - 1);

    // If the new active frame is not the same as the current active frame, proceed with the update
    if (newActiveFrame != m_currentActiveFrame) {
        // Disable effect for the previously active frame and hide its info
        dynamic_cast<QGraphicsDropShadowEffect*>(m_imageLabels[m_currentActiveFrame]->graphicsEffect())->setEnabled(false);
        m_infoLabels[m_currentActiveFrame]->hide();

        // Update the current active frame
        m_currentActiveFrame = newActiveFrame;

        // If we reach here, then we are navigating through the images.
        m_selectPlayer->stop();
        m_selectPlayer->play();

        // Enable effect for the new active frame and show its info
        dynamic_cast<QGraphicsDropShadowEffect*>(m_imageLabels[m_currentActiveFrame]->graphicsEffect())->setEnabled(true);
        m_infoLabels[m_currentActiveFrame]->show();

        // Move the mouse pointer to the selected frame
        moveCursorToSelectedFrame();
    }

    event->accept();
}


void MenuWidget::animateSelection() {
    QPropertyAnimation *anim;
    // Calculate the position below the titleView
    int yOffset = titleView->height() + 200;  // 200 pixels below the titleView
    QPoint desiredPosition = mapTo(this, QPoint(width()/2, yOffset));

    for(int i = 0; i < m_imageLabels.size(); ++i) {
        QWidget *frame = m_imageLabels[i]->parentWidget();
        if (i != m_currentActiveFrame) {
            // Shrink and fade out frames that are not selected
            anim = new QPropertyAnimation(frame, "geometry");
            anim->setDuration(1000);
            anim->setEndValue(QRect(frame->pos(), QSize(0, 0)));
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        } else {
            // Move the selected frame to the desired position
            anim = new QPropertyAnimation(frame, "pos");
            anim->setDuration(1000);
            anim->setEndValue(desiredPosition - frame->rect().center());
            anim->start(QAbstractAnimation::DeleteWhenStopped);

            // Highlight the selected frame with a glow effect
            QGraphicsDropShadowEffect *glow = new QGraphicsDropShadowEffect();
            glow->setBlurRadius(20);
            glow->setColor(Qt::yellow);
            glow->setOffset(0);
            frame->setGraphicsEffect(glow);

            // Animate the glow effect
            QPropertyAnimation *glowAnim = new QPropertyAnimation(glow, "blurRadius");
            glowAnim->setStartValue(20);
            glowAnim->setEndValue(40);
            glowAnim->setDuration(500);
            glowAnim->setLoopCount(-1);  // Loop forever
            glowAnim->setEasingCurve(QEasingCurve::InOutSine);  // Smooth pulsating effect
            glowAnim->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }

    QTimer::singleShot(3500, [this]() {
        QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(opacity);

        QPropertyAnimation *fadeAnim = new QPropertyAnimation(opacity, "opacity");
        fadeAnim->setEasingCurve(QEasingCurve::OutBack);
        fadeAnim->setDuration(2000);
        fadeAnim->setStartValue(1.0);
        fadeAnim->setEndValue(0.0);

        // Connect the 'finished' signal of the animation to the 'finished' signal of the MenuWidget
        connect(fadeAnim, &QPropertyAnimation::finished, this, &MenuWidget::finished);

        fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
    });
}




void MenuWidget::moveCursorToSelectedFrame() {

    QWidget *selectedFrame = m_imageLabels[m_currentActiveFrame]->parentWidget();

    // Calculate the global position of the center left of the selected frame
    QPoint pos = selectedFrame->mapToGlobal(QPoint(0, selectedFrame->height() / 2));

    // Load the cursor image
    QPixmap cursorPixmap(":/menu/sprites/menu/pointeurMouse.png");

    // Create the cursor with the QPixmap, setting the hot spot to the center of the image
    QCursor cursor(cursorPixmap, cursorPixmap.width() / 2, cursorPixmap.height() / 2);

    // Set the cursor
    QApplication::setOverrideCursor(cursor);

    // Move the mouse pointer to the calculated position
    QCursor::setPos(pos);
}
void MenuWidget::setNumberOfLevelsUnlocked(int nb)
{
    numberOfLevelsUnlocked=nb;
}

int MenuWidget::getSelectedLevelIndex()
{
    return selectedLevelIndex;
}

void MenuWidget::skipMenu()
{
    menuSkipped = true;
    emit finished();
}

bool MenuWidget::isMenuSkipped() const
{
    return menuSkipped;
}

void MenuWidget::saga()
{
    // Play the saga.mp3 and set the saga.jpg as background
    m_sagaPlayer->play();
    setBackgroundImage(":/menu/sprites/menu/saga.jpg");

    // If saga.mp3 has finished playing, set the backgroundImage to menubg.png
    connect(m_sagaPlayer, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            // Create a QLabel and a QMovie for the gif
            QLabel *label = new QLabel(this);
            QMovie *movie = new QMovie(":/menu/sprites/menu/bgstart.gif");

            // Set the QLabel to the size of the window
            label->setGeometry(0, 0, this->width(), this->height());
            label->setMovie(movie);
            label->setScaledContents(true);

            // Set the movie to the QLabel
            label->setMovie(movie);
            label->show();

            // Create a QLabel for the logo and a QPixmap to load the logo
            QLabel *logoLabel = new QLabel(this);
            logoLabel->setObjectName("logoLabel");
            QPixmap logoPixmap(":/menu/sprites/menu/logo.png");

            // Scale the logo by 2
            logoPixmap = logoPixmap.scaled(logoPixmap.width() * 1, logoPixmap.height() * 1);

            logoLabel->setPixmap(logoPixmap);
            logoLabel->setScaledContents(true);
            // Set the logo size as you need
            logoLabel->setFixedSize(logoPixmap.size());
            // Position the logo at the center of the window
            logoLabel->move((this->width() - logoLabel->width()) / 2, (this->height() - logoLabel->height()) / 2);
            logoLabel->show();


            // Load the font from the file into the application
            int fontId = QFontDatabase::addApplicationFont(":/menu/sprites/menu/retro.ttf");
            QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

                QFont retroFont(family);

                // Create the QPushButton
                QPushButton *playButton = new QPushButton("PLAY !", this);

                // Set the font
                playButton->setFont(retroFont);

                // Set the button width
                playButton->setFixedWidth(200);

                // Apply the 3D effect by modifying the stylesheet
                playButton->setStyleSheet(
                    "QPushButton {"
                    "background-color: #444;"
                    "color: #fff;"
                    "padding: 10px;"
                    "font-size: 20px;"
                    "border: 1px solid #555;" // border color
                    "border-radius: 5px;" // rounded corners
                    "}"
                    "QPushButton:pressed {"
                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                    "stop: 0 #888, stop: 1 #555);" // gradient effect when button is pressed
                    "}"
                    );

                playButton->move((this->width() - playButton->width()) / 2, (logoLabel->y() + logoLabel->height() - 80)); // 20 pixels below logoLabel play with - and +
                playButton->show();

                settingsButton = new QPushButton("Settings", this);
                settingsButton->setFont(retroFont);
                settingsButton->setFixedWidth(200);
                settingsButton->setStyleSheet(
                    "QPushButton {"
                    "background-color: #444;"
                    "color: #fff;"
                    "padding: 10px;"
                    "font-size: 20px;"
                    "border: 1px solid #555;"
                    "border-radius: 5px;"
                    "}"
                    "QPushButton:pressed {"
                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                    "stop: 0 #888, stop: 1 #555);"
                    "}"
                    );
                settingsButton->move((this->width() - settingsButton->width()) / 2, playButton->y() + playButton->height() + 20); // 20 pixels below playButton
                settingsButton->show();

                cursorLabel2 = new QLabel(this);
                cursorLabel2->setObjectName("cursorLabel2");
                QMovie *cursorMovie2 = new QMovie(":/menu/sprites/menu/startcursor.gif");
                cursorMovie2->jumpToFrame(0);
                QSize originalSize2 = cursorMovie2->frameRect().size();
                cursorLabel2->setFixedSize(originalSize2 / 4);
                cursorLabel2->setMovie(cursorMovie2);
                cursorLabel2->setScaledContents(true);
                cursorLabel2->move(settingsButton->x() - cursorLabel2->width() - 10, settingsButton->y() + (settingsButton->height() - cursorLabel2->height()) / 2);
                cursorMovie2->start();
                cursorLabel2->hide();


                cursorLabel = new QLabel(this);
                cursorLabel->setObjectName("cursorLabel");
                cursorMovie = new QMovie(":/menu/sprites/menu/startcursor.gif");

                // Load the movie to get its size
                cursorMovie->jumpToFrame(0);
                QSize originalSize = cursorMovie->frameRect().size();

                // Set the QLabel to one-fourth the size of the original image, keeping aspect ratio
                cursorLabel->setFixedSize(originalSize / 4);
                cursorLabel->setMovie(cursorMovie);
                cursorLabel->setScaledContents(true);

                // Position the QLabel to the left of the button with a slight space
                cursorLabel->move(playButton->x() - cursorLabel->width() - 10, playButton->y() + (playButton->height() - cursorLabel->height()) / 2); // adjusted the y-coordinate to center vertically

                // Show the QLabel and start the gif
                cursorLabel->show();
                cursorMovie->start();

                // Connect the clicked() signal of the playButton to the playButtonClicked() slot
                connect(playButton, &QPushButton::clicked, this, [=]() {
                    QLabel *cursorLabel = this->findChild<QLabel*>("cursorLabel");
                    QLabel *cursorLabel2 = this->findChild<QLabel*>("cursorLabel2");

                    if (playButtonClickedOnce) {
                        movie->stop();
                        label->hide();
                        logoLabel->hide();

                        QLabel *cursorLabel = this->findChild<QLabel*>("cursorLabel");
                        QLabel *cursorLabel2 = this->findChild<QLabel*>("cursorLabel2");
                        if (cursorLabel) {
                            cursorLabel->hide();
                        }
                        if (cursorLabel2) {
                            cursorLabel2->hide();
                        }

                        playButton->hide();
                        settingsButton->hide();

                        this->initMenu();
                        playButtonClickedOnce = false;
                    }
                    else {
                        if (cursorLabel2) {
                            cursorLabel2->hide();
                        }
                        if (cursorLabel) {
                            cursorLabel->show();
                        }
                        playButtonClickedOnce = true;
                        settingsButtonClickedOnce = false;
                    }
                });

                // Connect the clicked() signal of the settingsButton to the settingsButtonClicked() slot
                connect(settingsButton, &QPushButton::clicked, this, [=]() {
                    QLabel *cursorLabel = this->findChild<QLabel*>("cursorLabel");
                    QLabel *cursorLabel2 = this->findChild<QLabel*>("cursorLabel2");

                    if (settingsButtonClickedOnce) {
                        this->settingsButtonClicked();
                        settingsButtonClickedOnce = false;
                    } else {
                        if (cursorLabel) {
                            cursorLabel->hide();
                        }
                        if (cursorLabel2) {
                            cursorLabel2->show();
                        }
                        settingsButtonClickedOnce = true;
                        playButtonClickedOnce = false;
                    }
                });












            // Start the gif
            movie->start();

            // Play the menu.mp3
            m_sagaPlayer->setSource(QUrl("qrc:/menu/sprites/menu/menu.mp3"));
            m_sagaPlayer->play();

            // Baisser le volume de 50%
            player = new QMediaPlayer;
            QAudioOutput *audioOutput = new QAudioOutput;
            player->setAudioOutput(audioOutput);
            audioOutput->setVolume(0.5); // Set the volume to half



            // Create a QEventLoop
            QEventLoop loop;

            // When the movie finishes, quit the loop
            connect(movie, &QMovie::finished, &loop, &QEventLoop::quit);

            // Start the loop
            loop.exec();

            // When the gif has finished, hide the QLabel and delete it
            label->hide();
            delete label;
            delete movie;

            // Hide and delete the logoLabel
            logoLabel->hide();
            delete logoLabel;

            setBackgroundImage(":/menu/sprites/menu/menubg.png");
            initMenu();
        }
    });
}


void MenuWidget::settingsButtonClicked()
{

    m_sagaPlayer->setSource(QUrl("qrc:/menu/sprites/menu/paint.mp3"));
    m_sagaPlayer->play();
    originalClicked = false;
    // Create the settings window widget
    settingsWindow = new QWidget;
    settingsWindow->setWindowTitle("Settings");

    // Set a fixed size for the settings window
    settingsWindow->setFixedSize(800, 600);

    // Set the background image using a QPalette
    QPalette palette;
    QPixmap backgroundImage(":/menu/sprites/menu/peinture.jpg"); // Load the background image
    palette.setBrush(QPalette::Window, backgroundImage.scaled(settingsWindow->size())); // Scale the image to fit the window size
    settingsWindow->setPalette(palette);

    // Create a layout and add the QLabel to it
    QGridLayout *layout = new QGridLayout;

    // Adjust horizontal spacing and margins
    layout->setHorizontalSpacing(5);  // Sets the space between items in the layout to 10 pixels
    layout->setContentsMargins(5, 5, 5, 5); // Sets the margins around the layout to 10 pixels

    // Create a new QGraphicsView and QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(settingsWindow);
    QGraphicsView *view = new QGraphicsView(scene, settingsWindow);
    view->setStyleSheet("background: transparent; border: none;");


    // Create the fox
    // Create the fox with a scale of 4
    fox = new Fox(scene);
    fox->setScale(4); // assuming your Fox class has this method

    // Move fox to the desired position
    // Add a smaller spacer to the left of the view
    QSpacerItem* leftSpacer = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addItem(leftSpacer, 3, 0, 2, 1);

    // Add a larger spacer to the right of the view
    QSpacerItem* rightSpacer = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(rightSpacer, 3, 2, 2, 1);

    // Move the view to the second column
    layout->addWidget(view, 4, 1, 2, 2);

    // Create an array of colors for each element
    colors = { QColor("darkred"), QColor("gold"), QColor("darkgreen"), QColor("darkturquoise"), QColor("darkblue"), QColor("darkmagenta"), QColor("deeppink") };

    // Create a single column grid for "minifox1.png"
    for(int i=0; i<colors.size(); i++) {
        ClickableLabel* foxLabel = new ClickableLabel(settingsWindow);
        QPixmap foxPixmap(":/menu/sprites/menu/minifox1.png");

        QSize newSize = foxPixmap.size() / 2;
        QPixmap scaledPixmap = foxPixmap.scaled(newSize, Qt::KeepAspectRatio);

        QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect;
        colorize->setColor(colors.at(i));
        foxLabel->setGraphicsEffect(colorize);

        foxLabel->setPixmap(scaledPixmap);
        layout->addWidget(foxLabel, i + 1, 2, Qt::AlignRight);

        // Connect the signal emitted when the label is clicked to the slot in the Fox class
        connect(foxLabel, &ClickableLabel::clicked, fox, [this, color = colors.at(i)](){
            this->fox->setColor(color);
            this->selectedColor = color;
            originalClicked = false;
        });

    }

    // Create the "Original" button
    originalButton = new QPushButton("Original", settingsWindow);
    originalButton->setFixedSize(100, 50);  // Set a fixed size for the button
    originalButton->setStyleSheet("background-color: #556B2F; color: white; font: bold; border-radius: 10px;"); // Add CSS

    // Create the "Validate" button
    validateButton = new QPushButton("Validate", settingsWindow);
    validateButton->setFixedSize(100, 50);  // Set a fixed size for the button
    validateButton->setStyleSheet("background-color: #008B8B; color: white; font: bold; border-radius: 10px;"); // Add CSS

    // Create a QVBoxLayout for buttons
    QVBoxLayout *buttonsLayout = new QVBoxLayout;

    // Add buttons to the layout
    buttonsLayout->addWidget(originalButton, 0, Qt::AlignCenter);
    buttonsLayout->addWidget(validateButton, 0, Qt::AlignCenter);

    // Add a stretch at the bottom of the buttons layout to make sure the buttons are at the top
    buttonsLayout->addStretch(1);

    // Add buttons layout to the grid layout
    layout->addLayout(buttonsLayout, 3, 0, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);


    connect(originalButton, &QPushButton::clicked, this, &MenuWidget::originalButtonClicked);
    connect(validateButton, &QPushButton::clicked, this, &MenuWidget::validateButtonClicked);



    // Set the layout for the settings window
    settingsWindow->setLayout(layout);

    // Show the settings window
    settingsWindow->show();

    // Set the attribute to delete the settingsWindow when it is closed
    settingsWindow->setAttribute(Qt::WA_DeleteOnClose);
    // Connect destroyed() signal of settingsWindow to stop the m_sagaPlayer
    connect(settingsWindow, &QObject::destroyed, this, [this]() {
        m_sagaPlayer->stop();
    });
}



void MenuWidget::originalButtonClicked() {
    fox->resetColor();  // Reset the color of the fox
    originalClicked = true;

    // Prepare file path
    QFile file(QCoreApplication::applicationDirPath() + "/color.txt");

    // Try to open the file with read/write permissions, this will create the file if it doesn't exist
    if(file.open(QIODevice::ReadWrite)) {
        qDebug() << "File opened for reading and writing.";

        // Read all lines into a QStringList
        QStringList lines = QString(file.readAll()).split("\n");

        // Make sure there are at least two lines
        while(lines.size() < 2) {
            lines << "";
        }

        // Update the second line with the chosen color
        lines[1] = "orange";
        qDebug() << "Second line updated to: " << lines[1];

        // Clear the file content to prepare for overwriting
        file.resize(0);

        // Write all lines back to the file
        QTextStream out(&file);
        out << lines.join("\n");
        file.close();
        qDebug() << "Updated lines written to file.";
    } else {
        qDebug() << "Failed to open file for reading and writing: " << file.errorString();
    }
}




void MenuWidget::validateButtonClicked() {
    fox->setColor(selectedColor);  // Set the color of the fox

    // Prepare file path
    QFile file(QCoreApplication::applicationDirPath() + "/color.txt");

    // Open the file with read/write permissions, this will create the file if it doesn't exist
    if(file.open(QIODevice::ReadWrite)) {
        qDebug() << "File opened for reading and writing.";

        // Read all lines into a QStringList
        QStringList lines = QString(file.readAll()).split("\n");

        // Make sure there are at least two lines
        while(lines.size() < 2) {
            lines << "";
        }

        // Update the second line with the chosen color if "original" wasn't clicked, or if the current color isn't orange
        if(!originalClicked || lines[1].trimmed().toLower() != "orange") {
            lines[1] = selectedColor.name();

            // Clear the file content to prepare for overwriting
            file.resize(0);

            // Write all lines back to the file
            QTextStream out(&file);
            out << lines.join("\n");
            file.close();
        }

        // Reset the flag
        originalClicked = false;
    } else {
        qDebug() << "Failed to open file for reading and writing: " << file.errorString();
    }

    settingsWindow->close();  // Close the settings window
}




void MenuWidget::initMenu()
{
    setupImagesLayout();
    this->setLayout(m_layout);

    setBackgroundImage(":/menu/sprites/menu/menubg.png");
}

void MenuWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // If the central QLabel exists, resize it
    QLabel *label = this->findChild<QLabel*>();
    QLabel *logoLabel = this->findChild<QLabel*>("logoLabel");
    if(label && label->movie())
    {
        QSize newSize = event->size();
        label->resize(newSize);

        // Reposition logoLabel according to the new size
        if (logoLabel) {
            logoLabel->move((newSize.width() - logoLabel->width()) / 2, (newSize.height() - logoLabel->height()) / 2);
        }

        // Reposition titleView according to the new size
        titleView->move((newSize.width() - titleView->width()) / 2, titleView->y());

        // Reposition gifLabel according to the new size
        gifLabel->move((newSize.width() - gifLabel->width()) / 2, gifLabel->y());
    }

//    // If the play button exists, move it
//    QPushButton *playButton = this->findChild<QPushButton*>();
//    QLabel *cursorLabel = this->findChild<QLabel*>("cursorLabel");
//    if (playButton) {
//        playButton->move((event->size().width() - playButton->width()) / 2, (logoLabel->y() + logoLabel->height() + 20));
//        // If cursorLabel exists, move it to the left of the playButton and adjust the size
//        if (cursorLabel) {
//            cursorLabel->move(playButton->x() - cursorLabel->width() - 10, playButton->y() + (playButton->height() - cursorLabel->height()) / 2);
//            cursorLabel->setFixedSize(playButton->size() / 2);
//        }
//    }

//    // If the settings button exists, move it
//    QPushButton *settingsButton = this->findChild<QPushButton*>("settingsButton");
//    QLabel *cursorLabel2 = this->findChild<QLabel*>("cursorLabel2");
//    if (settingsButton) {
//        settingsButton->move((event->size().width() - settingsButton->width()) / 2, (playButton->y() + playButton->height() + 20));
//        // If cursorLabel2 exists, move it to the left of the settingsButton and adjust the size
//        if (cursorLabel2) {
//            cursorLabel2->move(settingsButton->x() - cursorLabel2->width() - 10, settingsButton->y() + (settingsButton->height() - cursorLabel2->height()) / 2);
//            cursorLabel2->setFixedSize(settingsButton->size() / 2);
//        }
//    }
}




void MenuWidget::launchPlayButtonClickedProcess()
{
    initMenu();

    // Find all needed widgets
    QPushButton *playButton = this->findChild<QPushButton*>();
    QLabel *label = this->findChild<QLabel*>();

    // Hide and delete the playButton
    if(playButton) {
        playButton->hide();
        delete playButton;
    }
    if(settingsButton) {
        settingsButton->hide();
        delete settingsButton;
    }

    // Hide and delete the label
    if(label && label->movie()) {
        label->hide();
        delete label->movie();
        delete label;
    }

    // Find logoLabel and hide/delete it
    QLabel *logoLabel = this->findChild<QLabel*>("logoLabel");
    if(logoLabel) {
        logoLabel->hide();
        delete logoLabel;
    }

    // Find cursorLabel and hide/delete it
    QLabel *cursorLabel = this->findChild<QLabel*>("cursorLabel");
    if(cursorLabel) {
        cursorLabel->hide();
        if (cursorLabel->movie())
            cursorLabel->movie()->deleteLater();
        cursorLabel->deleteLater();
    }

    // Find cursorLabel2 and hide/delete it
    QLabel *cursorLabel2 = this->findChild<QLabel*>("cursorLabel2");
    if(cursorLabel2) {
        cursorLabel2->hide();
        if (cursorLabel2->movie())
            cursorLabel2->movie()->deleteLater();
        cursorLabel2->deleteLater();
    }

    // Create a media player to play the sound
    QMediaPlayer *player = new QMediaPlayer;

    // Set the media source and play the sound
    player->setSource(QUrl("qrc:/menu/sprites/menu/playsound.mp3"));
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->play();

    // Cleanup the media player after the sound finished
    connect(player, &QMediaPlayer::playbackStateChanged, [=](QMediaPlayer::PlaybackState newState) {
        if (newState == QMediaPlayer::StoppedState) {
            player->deleteLater();
        }
    });
}

void MenuWidget::playButtonClicked()
{
    launchPlayButtonClickedProcess();
}

