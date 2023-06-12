#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QGridLayout>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsView>
#include <QPushButton>


class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent, int aNumberOfLevelsUnlocked);
    void setBackgroundImage(const QString &imagePath);
    void setupImagesLayout();

    void animateSelection();
    void moveCursorToSelectedFrame();
    void setNumberOfLevelsUnlocked(int nb);
    int getSelectedLevelIndex();
    void skipMenu();
    bool isMenuSkipped() const;
    void saga();
    QMediaPlayer *m_sagaPlayer;
    QTimer *m_timer;
    void resetBackground();
    void initMenu();
    void createPlayButton();
    void playButtonClicked();
    void logoSwitchAnimation();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QMediaPlayer *m_selectPlayer;
    QMediaPlayer *m_selectedPlayer;
    QPixmap m_backgroundImage;
    QList<QLabel*> m_imageLabels;
    QGridLayout *m_layout;
    int m_currentActiveFrame;
    QLabel *infoLabel;
    QList<QLabel*> m_infoLabels;
    QWidget *imageHolder;
    QLabel *gifLabel;
    QGraphicsView *titleView;
    QCursor m_customCursor;
    int m_startGrayscaleImage;
    int numberOfLevelsUnlocked;
    int selectedLevelIndex;
    bool menuSkipped;
    QLabel *cursorLabel;
    QMovie *cursorMovie;


signals:
    void levelSelected(int levelIndex);
    void finished();


};































































































































































































































// mdr bien joué





class LogoLabel : public QLabel {
    Q_OBJECT
    Q_PROPERTY(float fadeFraction READ fadeFraction WRITE setFadeFraction)
public:
    LogoLabel(QWidget* parent = nullptr) : QLabel(parent), m_fadeFraction(0) {
        m_oldLogo.load(":/menu/sprites/menu/oldLogo.png");
        m_newLogo.load(":/menu/sprites/menu/logo.png");
    }
    float fadeFraction() const {
        return m_fadeFraction;
    }
    void setFadeFraction(float fraction) {
        m_fadeFraction = fraction;
        update();  // This will cause a repaint
    }
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.drawPixmap(0, 0, m_oldLogo);
        QLinearGradient gradient(0, height(), 0, 0);
        gradient.setColorAt(0, QColor(255, 255, 255, 0));
        gradient.setColorAt(m_fadeFraction, QColor(255, 255, 255, 255));
        painter.setBrush(gradient);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.drawPixmap(0, 0, m_newLogo);
    }
private:
    QPixmap m_oldLogo;
    QPixmap m_newLogo;
    float m_fadeFraction;
};

#endif // MENUWIDGET_H
