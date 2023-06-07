#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector2D>
#include "animatedsprite.h"
#include "constants.h"
#include "tile.h"

/**
 * @brief The Player class represents a player in the game.
 *
 * The Player class manages the player's position, velocity, and animations.
 */
class Player : public QObject
{
    Q_OBJECT

private:
    bool inAir; /**< Indicates if the player is in the air. */
    bool onGround; /**< Indicates if the player is on the ground. */
    QVector2D velocity; /**< The velocity of the player. */
    Fox* animation; /**< The animation of the player. */

public:
    /**
     * @brief Constructs a Player object.
     * @param parent The parent object.
     */
    explicit Player(QObject *parent = nullptr);

    /**
     * @brief Destructs the Player object.
     */
    ~Player();

    /**
     * @brief Checks if the player is in the air.
     * @return True if the player is in the air, false otherwise.
     */
    bool isOnAir() const;

    /**
     * @brief Checks if the player is on the ground.
     * @return True if the player is on the ground, false otherwise.
     */
    bool isOnGround() const;

    /**
     * @brief Sets the velocity of the player.
     * @param x The x component of the velocity.
     * @param y The y component of the velocity.
     */
    void setVelocity(int x, int y);

    /**
     * @brief Sets the velocity of the player.
     * @param vec The velocity vector.
     */
    void setVelocity(const QVector2D &vec);

    /**
     * @brief Adds the specified velocity to the current velocity of the player.
     * @param x The x component of the velocity to add.
     * @param y The y component of the velocity to add.
     */
    void addVelocity(int x, int y);

    /**
     * @brief Adds the specified velocity to the current velocity of the player.
     * @param vec The velocity vector to add.
     */
    void addVelocity(const QVector2D &vec);

signals:
    void jump();
    void accelerate();
    void slowdown();
    void playerMoved();

public slots:
    /**
     * @brief Updates the position of the player based on the current velocity and handles tile collisions.
     * @param tiles The vector of tiles in the game.
     */
    void updatePosition(const std::vector<Tile *> tiles);

    /**
     * @brief Updates the animation of the player based on the current state.
     */
    void updateAnimation();
};

#endif // PLAYER_H
