#include "game.h"

Game::Game(QObject *parent)
    : QObject(parent)
{
    // Set up the timers
    tps.setInterval(50); // 1000ms / 20 = 50ms
    fps.setInterval(10); // 1000ms / 100 = 10ms

    // Connect the timer signals to slots
    connect(&tps, &QTimer::timeout, this, &Game::handleTPSUpdate);
    connect(&fps, &QTimer::timeout, this, &Game::handleFPSUpdate);

    // Start the timers
    tps.start();
    fps.start();

    // Other initialization code for the game
}

Game::~Game()
{
    // Stop the timers
    tps.stop();
    fps.stop();
}

void Game::handleTPSUpdate()
{
    // Logic for position updates at 20 Hz
    // This method will be called when the tps timer triggers
    // Update the positions of game objects here
}

void Game::handleFPSUpdate()
{
    // Logic for repainting updates at 100 Hz
    // This method will be called when the fps timer triggers
    // Repaint the game view or perform other visual updates here
    // Note: If you're using a separate class for the game view, you may need to emit a signal to trigger the repaint in that class
}
