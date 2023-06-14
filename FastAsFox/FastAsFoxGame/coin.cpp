#include "coin.h"

Coin::Coin(QGraphicsScene * theScene, std::pair<int,int> position, int sectionHeight)
{
    texture = new QPixmap(COIN);
    this->coinToCollect = new GameObject();
    scene=theScene;
    QRect placement(0,0,TILE_SIZE,TILE_SIZE);
    this->coinToCollect->setRectangle(placement);

    double graphicsX = position.first * TILE_SIZE;
    double graphicxY = ( sectionHeight - position.second) * TILE_SIZE;

    setPos(graphicsX, graphicxY);

    scene->addItem(this);
    *texture=texture->scaled(32,32);
    this->setPixmap(*texture);
    this->update();
}

Coin::~Coin()
{
    delete texture;
    delete coinToCollect;
}


int Coin::getX() const
{
    return position.first;
}

int Coin::getY() const
{
    return position.second;
}

int Coin::getCoinCounter() const
{
    return coinCounter;
}

void Coin::handleCollision(Fox *fox)
{

    QRect coinItem(x(), y(), TILE_SIZE, TILE_SIZE);
    QRect foxRect(fox->x(), fox->y(), fox->pixmap().width(), fox->pixmap().height());

    // Check if the player has collided with the coin
    if (coinItem.intersects(foxRect))
    {
        // Emit the coinCollected() signal
        emit coinCollected();

        // Remove the coin from the scene
        scene->removeItem(this);
        delete this;
    }

    /**
    QRect coinItem(x(), y(), TILE_SIZE, TILE_SIZE);
    QRect foxRect(fox->x(),fox->y(),fox->pixmap().width(),fox->pixmap().height());

    // Check if the player has collided with the coin
    if(GameObject::collides(coinItem, foxRect) != std::pair<std::optional<CollisionSide>,std::optional<CollisionSide>>(std::nullopt, std::nullopt))
    {
        // Emit the coinCollected() signal
        emit coinCollected();

        // Remove the coin from the scene
        delete coinToCollect;
        scene->update();
    }
    **/
}

