#ifndef GAME_H
#define GAME_H


#include <QObject>
#include <QTimer>

class Game : public QObject
{
    Q_OBJECT

public:
    Game(QObject *parent = nullptr);
    ~Game();

public slots:
    void slotPositionUpdates();

    void slotRepaintingUpdates();

private:
    QTimer *tps;
    QTimer *fps;
};

#endif // GAME_H
