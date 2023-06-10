#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QGridLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
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


protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

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

signals:
    void levelSelected(int levelIndex);
    void finished();


};

#endif // MENUWIDGET_H
