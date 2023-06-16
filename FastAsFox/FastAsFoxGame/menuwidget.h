#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QGridLayout>
#include <QMediaPlayer>
#include "animatedsprite.h"
#include "qgraphicseffect.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsView>
#include <QPushButton>
#include <QAudioOutput>
#include <QSqlTableModel>
#include <QTableView>




class MenuWidget: public QWidget {
    Q_OBJECT

public:
    explicit MenuWidget(QWidget * parent, int aNumberOfLevelsUnlocked, int isRestart); //isRestart=1 => Le programme vient de redémarrer
    void setBackgroundImage(const QString & imagePath);
    void setupImagesLayout();

    void animateSelection();
    void moveCursorToSelectedFrame();
    void setNumberOfLevelsUnlocked(int nb);
    int getSelectedLevelIndex();
    void skipMenu();
    bool isMenuSkipped() const;
    void saga();
    QMediaPlayer * m_sagaPlayer;
    QTimer * m_timer;
    void resetBackground();
    void initMenu();
    void createPlayButton();
    void playButtonClicked();
    void logoSwitchAnimation();
    void restartGame();
    void launchPlayButtonClickedProcess();
    void settingsButtonClicked();
    void applyColor();
    void showLeaderboard();
    void showPlayerOptions();
    void addUser();
    void deleteUser();

protected:
    void paintEvent(QPaintEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void resizeEvent(QResizeEvent * event) override;

private:

    QSqlTableModel *model;
    QTableView *aView;
    QItemSelectionModel *select;
    QVBoxLayout *layout;
    QPushButton *deletePlayerButton ;
    QPushButton *addPlayerButton;
    QMediaPlayer * m_selectPlayer;
    QMediaPlayer * m_selectedPlayer;
    QPixmap m_backgroundImage;
    QGridLayout * m_layout;
    QLabel * infoLabel;
    QCursor m_customCursor;
    int m_startGrayscaleImage;
    int selectedLevelIndex;
    bool menuSkipped;
    QLabel * cursorLabel;
    QMovie * cursorMovie;
    QPushButton * m_activeButton;
    QPushButton * playButton;
    QPushButton * settingsButton;
    QPushButton * selectedButton;
    QLabel * cursorLabel2;
    QMovie * cursorMovie2;
    QTimer * m_playButtonTimer;
    QTimer * m_settingsButtonTimer;
    bool playButtonClickedOnce;
    bool settingsButtonClickedOnce;
    QWidget * settingsWindow;
    Fox * fox;
    QList < QColor > colors;
    QPushButton * originalButton;
    QPushButton * validateButton;
    QColor selectedColor;
    bool originalClicked;
    QMediaPlayer * player;
    QAudioOutput * selectOutput;
    QAudioOutput * audioOutput;
    QWidget * frame;
    QVBoxLayout * vbox;

    QLabel * imageLabel;
    QPropertyAnimation * anim;
    QGraphicsDropShadowEffect * glow;
    QPropertyAnimation * glowAnim;
    QGraphicsOpacityEffect * opacity;
    QPropertyAnimation * fadeAnim;
    QWidget * selectedFrame;
    QLabel * logoLabel;


    QGraphicsView * view;
    QSpacerItem * leftSpacer;
    QSpacerItem * rightSpacer;
    QGraphicsColorizeEffect * colorize;
    QVBoxLayout * buttonsLayout;
    QLabel * label;
    QFont loadCustomFont();
    void setupTitleScene(QFont customFont);
    void setupImageHolder();
    void handleImageReady(int index, QPixmap pixmap);
    void setupGifAndLayout();
    QGraphicsScene* scene;
    QGraphicsTextItem* titleItem;
    QGraphicsDropShadowEffect* effect;
    QGraphicsView* titleView;

    QWidget* imageHolder;
    QGridLayout* gridLayout;

    QList<QLabel*> m_imageLabels;
    QList<QLabel*> m_infoLabels;
    int m_currentActiveFrame;

    QLabel* gifLabel;
    QMovie* movie;

    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;
    QHBoxLayout* gifLayout;
    QPushButton *cupButton;

    const int maxPerRow = 5;
    int numberOfLevelsUnlocked = 2;

private slots:
    void originalButtonClicked();
    void validateButtonClicked();

signals:
    void levelSelected(int levelIndex);
    void finished();

};

#endif
