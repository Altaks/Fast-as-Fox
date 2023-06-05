#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(QObject *parent = nullptr);
    ~Game();

public slots:
    void handleTPSUpdate();
    void handleFPSUpdate();

private:
    QTimer tps; // Timer for position updates (20 Hz)
    QTimer fps; // Timer for repainting updates (100 Hz)

    // Other member variables and methods for game logic
};

#endif // GAME_H
