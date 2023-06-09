#include "player.h"

Fox *Player::getAnimation() const
{
    return animation;
}

void Player::setInAir(bool newInAir)
{
    this->lastJumpTimeStamp = std::chrono::system_clock::now();
    inAir = newInAir;
}

void Player::setOnGround(bool newOnGround)
{
    onGround = newOnGround;
}

void Player::setLastJumpTimeStamp(std::chrono::time_point<std::chrono::system_clock> newLastJumpTimeStamp)
{
    lastJumpTimeStamp = newLastJumpTimeStamp;
}

Player::Player(Map * map, QObject *parent)
{
    this->inAir = false;
    this->onGround = true;
    this->playerJump = false;
    this->velocity = QVector2D(0, 0);
    this->animation = new Fox(map->getScene());
    this->animation->setZValue(1);
    this->map = map;
}

Player::~Player()
{
    delete animation;
}

bool Player::isOnAir() const
{
    return inAir;
}

bool Player::isOnGround() const
{
    return onGround;
}

bool Player::isStillOnGround(std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> collision) const
{
    if(!collision.first.has_value() and onGround==true)
    {
        return false;
    }
    return true;
}

void Player::setVelocity(int x, int y)
{
    this->velocity.setX(x);
    this->velocity.setY(y);
}

void Player::setVelocity(const QVector2D &vec)
{
    this->velocity = vec;
}

void Player::addVelocity(int x, int y)
{
    this->velocity += QVector2D(x, y);
}

void Player::addVelocity(const QVector2D &vec)
{
    this->velocity += vec;
}

std::vector<Tile *> filterNearbyTiles(std::vector<Tile *>* tiles, int proximity, double predictedX, double predictedY){
    std::vector<Tile *> filtered = std::vector<Tile *>();

    for(Tile * tile : *tiles){
        if(tile->getTileId() != 0){

            int xOffset = abs(((int)predictedX) - tile->getX());
            int yOffset = abs(((int)predictedY) - tile->getY());

            if(xOffset <= proximity && yOffset <= proximity) filtered.push_back(tile);
        }

    }

    return filtered;
}

void Player::updatePosition()
{
    // Query the tiles from the Map of the level
    std::vector<Tile *>* tiles = map->getActuallyLoadedTiles();

    // Get the "game real" coordinates
    double xPlayer = ((double)this->animation->x() / 32); // get the x as usual
    double yPlayer = (((double)this->map->getScene()->height() - this->animation->y()) / 32); // invert the y axis

    //std::cout << "Player is located at " << xPlayer << ", " << yPlayer << std::endl;

    // Calculates the velocity vector applied to the player
    double vx = 0.0;
    double vy = 0.0;

    std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> collisionSide;

    if(this->isOnAir() && this->playerJump){

        std::chrono::time_point<std::chrono::system_clock> currentTimeStamp = std::chrono::system_clock::now();
        std::chrono::duration<double> time = currentTimeStamp - this->lastJumpTimeStamp;
        double t = time.count();

        vx = V0 * sin(alpha);
        vy = - gravity * t + V0 * cos(alpha);

    }
    else if(this->isOnGround()){

            if(this->animation->getIsRunning()){

                vx = running_speed;

            }
            else {
                // walking by default
                vx = walking_speed;
            }

    } //else qWarning("None condition of movement have been implied in position update");
    else
    {
        std::chrono::time_point<std::chrono::system_clock> currentTimeStamp = std::chrono::system_clock::now();
        std::chrono::duration<double> time = currentTimeStamp - this->lastJumpTimeStamp;
        double t = time.count();

        if(this->animation->getIsRunning())
            vx = running_speed * sin(alpha);
        else
            vx = walking_speed * sin(alpha);

        vy = - gravity * t - walking_speed * cos(alpha);
    }


    // Check for collision, if they appear, cancel the movement in the specified direction.
    double predictedX = xPlayer + vx;
    double predictedY = yPlayer + vy;

    //std::cout << "Player is supposed to go at " << predictedX << ", " << predictedY << std::endl;

    this->setRectangle(this->animation->pixmap().rect());

    // Filter the tiles to obtain only the nearby tiles to avoid unnecessary collision checks
    std::vector<Tile *> nearbyTiles = filterNearbyTiles(tiles, 5, predictedX, predictedY);

    QRect collidedTopTileRect;
    QRect collidedBottomTileRect;
    QRect collidedRightTileRect;
    QRect collidedLeftTileRect;


    for(Tile * tile : *tiles){
        if(tile->getTileId() == 0) continue;

        QRect playerRect = QRect(predictedX * 32, this->map->getScene()->height() - (predictedY * 32), this->animation->pixmap().width(), this->animation->pixmap().height());
        QRect tileRect = QRect(tile->getTileItem()->x(), tile->getTileItem()->y(), tile->getTileItem()->pixmap().width(), tile->getTileItem()->pixmap().height());

        //std::cout << "Precalculated playerRect [x:"<< playerRect.x() << ",y:"<< playerRect.y() << ",w:"<< playerRect.width() << ",h:"<< playerRect.height() << "]" << std::endl;
        //std::cout << "Precalculated tileRect [x:"<< tileRect.x() << ",y:"<< tileRect.y() << ",w:"<< tileRect.width() << ",h:"<< tileRect.height() << "]" << std::endl;

        std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> collisionCompute = GameObject::collides(tileRect, playerRect);


        if(collisionCompute.first.has_value())
        {
            if (collisionCompute.first.value()==TOP){
                collidedTopTileRect = tileRect;
                collisionSide.first.emplace(TOP);
            }
            else if (collisionCompute.first.value()==BOTTOM){
                collidedBottomTileRect = tileRect;
                collisionSide.first.emplace(BOTTOM);
            }
        }

        else if (collisionCompute.second.has_value())
        {
            if (collisionCompute.second.value()==RIGHT)
            {
                collidedRightTileRect = tileRect;
                collisionSide.second.emplace(RIGHT);
            }
            else if (collisionCompute.second.value()==LEFT)
            {
                collidedLeftTileRect = tileRect;
                collisionSide.second.emplace(LEFT);
            }
        }


 /*       if(collisionCompute.first.has_value()){
            // switch sur le côté de la tile qui collide avec l'object
            switch (collisionCompute.first.value()) {
                case TOP:
                    this->animation->setIsRunning(false);
                    onGround = true;
                    inAir = false;
                    yPlayer = this->map->getScene()->height()/32 - tileRect.y()/32 + tileRect.height()/32;
                    collisionSideOld.emplace(TOP);
                    break;
                case BOTTOM:
                    vx = 0.00;
                    vy = 0.00;
                    collisionSideOld.emplace(BOTTOM);
                    break;
                case LEFT:
                case RIGHT:
                    vx = 0.00;
                    collisionSideOld.emplace(RIGHT);
                    break;
                default:
                    break;
            }

            /* std::cout << "Tile of ID : " << tile->getTileId() << " "
                      << "[x:" << tile->getTileItem()->x() << ",y:" << tile->getTileItem()->y() << "]"
                      << "[pixX:" << tile->getTileItem()->pixmap().rect().x() << ",pixY:" << tile->getTileItem()->pixmap().rect().y() << ",pixW:" << tile->getTileItem()->pixmap().rect().width() <<",pixH:" << tile->getTileItem()->pixmap().rect().height() << "] "
                      << "collided with player [x:" << this->animation->pixmap().rect().x() << ",y:" << this->animation->pixmap().rect().y() << ",w:" << this->animation->pixmap().rect().width() << ",h:" << this->animation->pixmap().rect().height() << "][xOffset:"<< this->animation->offset().x() <<"yOffset:"<< this->animation->offset().y() <<"][x:"<< this->animation->x() <<"y:"<< this->animation->y() <<"]" << std::endl;
            */


         // else qDebug("Didn't collide with tile");

    }

    if(!isStillOnGround(collisionSide))
    {
        onGround=false;
        setInAir(true);
    }

    if(collisionSide.first.has_value() and collisionSide.second.has_value())
    {
        if(collisionSide.first.value()==TOP and collisionSide.second.value()==RIGHT)
        {
            vx=0;
            yPlayer = this->map->getScene()->height()/32 - collidedTopTileRect.y()/32 + collidedTopTileRect.height()/32;
        }
    }
    else if(collisionSide.first.has_value() and !collisionSide.second.has_value())
    {
        if(collisionSide.first.value()==TOP)
        {
            this->animation->setIsRunning(false);
            onGround = true;
            inAir = false;
            yPlayer = this->map->getScene()->height()/32 - collidedTopTileRect.y()/32 + collidedTopTileRect.height()/32;
        }
        if(collisionSide.first.value()==BOTTOM)
        {

        }
    }
    else if(!collisionSide.first.has_value() and collisionSide.second.has_value())
    {
        if(collisionSide.second.value()==RIGHT)
        {
            setInAir(true);
            vx=0;
        }
    }

    // Applies the whole velocity logic
    xPlayer += vx;
    yPlayer += vy;

    //std::cout << "Player recalculated position is " << xPlayer << ", " << yPlayer << std::endl;

    // Reconvert the coordinates to game based coordinates
    xPlayer *= 32;
    yPlayer *= 32;
    yPlayer = this->map->getScene()->height() - yPlayer;

    if((xPlayer + this->animation->pixmap().width() >= this->map->getScene()->width()) || (yPlayer >= this->map->getScene()->height())){
        xPlayer = LEVEL_ONE_START_POS.first*32;
        yPlayer = LEVEL_ONE_START_POS.second*32;
    }

    this->animation->setPos(xPlayer, yPlayer);
    emit playerMoved();
}

void Player::updateAnimation()
{

}
