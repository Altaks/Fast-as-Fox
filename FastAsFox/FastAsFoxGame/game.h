#ifndef GAME_H
#define GAME_H


#include <QObject>
#include <QTimer>

class Game : public QObject
{
    Q_OBJECT

public:
    Game(QObject *parent = nullptr);

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
