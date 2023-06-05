#ifndef GAME_H
#define GAME_H


#include <QObject>
#include <QTimer>

class Game : public QObject
{
    Q_OBJECT

public:
    Game(QObject *parent = nullptr)
        : QObject(parent),
          tps(new QTimer(this)),
          fps(new QTimer(this))
    {
        connect(tps, &QTimer::timeout, this, &Game::slotPositionUpdates);
        tps->start(1000 / 20);  // 20 Hz

        connect(fps, &QTimer::timeout, this, &Game::slotRepaintingUpdates);
        fps->start(1000 / 100); // 100 Hz
    }

    ~Game()
    {
        delete tps;
        delete fps;
    }

public slots:
    void slotPositionUpdates()
    {
        // position update logic here
    }

    void slotRepaintingUpdates()
    {
        // repainting update logic here
    }

private:
    QTimer *tps;
    QTimer *fps;
};

#endif // GAME_H
