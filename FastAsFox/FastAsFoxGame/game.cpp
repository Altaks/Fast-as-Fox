#include "game.h"

Game::Game(QObject *parent)
    : QObject(parent),
      tps(new QTimer(this)),
      fps(new QTimer(this))
{
    connect(tps, &QTimer::timeout, this, &Game::slotPositionUpdates);
    tps->start(1000 / 50);  // 20 Hz

    connect(fps, &QTimer::timeout, this, &Game::slotRepaintingUpdates);
    fps->start(1000 / 10); // 100 Hz
}
