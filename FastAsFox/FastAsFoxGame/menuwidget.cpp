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

MenuWidget::MenuWidget(QWidget *parent, int aNumberOfLevelsUnlocked) : QWidget(parent), m_layout(new QGridLayout), m_currentActiveFrame(0)
{
    numberOfLevelsUnlocked=aNumberOfLevelsUnlocked;

    setupImagesLayout();
    this->setLayout(m_layout);
    this->setFocusPolicy(Qt::StrongFocus); // Enable the widget to receive keyboard focus

    // Setup audio
    m_selectPlayer = new QMediaPlayer(this);
    m_selectPlayer->setMedia(QUrl("qrc:/menu/sprites/menu/menuSelection.mp3"));
    m_selectedPlayer = new QMediaPlayer(this);
    m_selectedPlayer->setMedia(QUrl("qrc:/menu/sprites/menu/menuSelected.mp3"));

    setBackgroundImage(":/menu/sprites/menu/menubg.png");

    // Load the cursor image.
    QPixmap cursorPixmap(":/menu/sprites/menu/pointeurMouse.png");
    m_customCursor = QCursor(cursorPixmap, -1, -1);  // The second and third parameters define the hotspot of the cursor.

    menuSkipped = false;

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
    if (event->key() == Qt::Key_Up)
        newActiveFrame = std::max(0, m_currentActiveFrame - 5); // 5 is the number of frames per row
    else if (event->key() == Qt::Key_Down)
        newActiveFrame = std::min(numberOfLevelsUnlocked - 1, m_currentActiveFrame + 5);
    else if (event->key() == Qt::Key_Left)
        newActiveFrame = std::max(0, m_currentActiveFrame - 1);
    else if (event->key() == Qt::Key_Right)
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
