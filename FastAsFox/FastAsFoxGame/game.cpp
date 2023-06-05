#include "game.h"

Game::Game(QObject *parent)
    : QObject(parent)
{
    tps = new QTimer(this);
    fps = new QTimer(this);

    connect(tps, &QTimer::timeout, this, &Game::slotPositionUpdates);
    tps->start(1000 / 20); // 20 Hz

    connect(fps, &QTimer::timeout, this, &Game::slotRepaintingUpdates);
    fps->start(1000 / 100); // 100 Hz
}

Game::~Game()
{
    delete tps;
    delete fps;
}

void Game::slotPositionUpdates()
{
    // Perform position updates for game objects here

    for (GameObject *gameObject : gameObjects) {
        // Update the position of the game object
        gameObject->updatePosition();
    }

    // Emit a signal or call a method to notify other parts of the program
    // that the positions have been updated
    emit positionsUpdated();
}

void Game::slotRepaintingUpdates()
{
    // Perform repainting or visual updates for the game here

    // Repaint the game view or perform other visual updates
    gameView->repaint();

    // Emit a signal or call a method to trigger the repaint in the UI
    emit repaintGameView();
}
