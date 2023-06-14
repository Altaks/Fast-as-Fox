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

const std::pair<int, int> &Player::getSpritePosition() const
{
    return spritePosition;
}

int Player::getHp() const
{
    return hp;
}

Player::Player(Map * map, std::pair<int, int> spawnCoords, QObject *parent) : GameObject{parent}
{
    this->inAir = false;
    this->onGround = true;
    this->playerJump = false;
    this->velocity = QVector2D(0, 0);
    this->animation = new Fox(map->getScene());
    this->animation->setZValue(1);
    this->map = map;
    this->spawnCoords = spawnCoords;
    this->hp = 3;
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

    if(this->isOnAir() && this->isJumping){
        std::chrono::time_point<std::chrono::system_clock> currentTimeStamp = std::chrono::system_clock::now();
        std::chrono::duration<double> time = currentTimeStamp - this->lastJumpTimeStamp;

        double t = time.count();

        if(this->animation->getIsRunning())
            vx = RUNNING_SPEED * cos(ALPHA);
        else
            vx = WALKING_SPEED * cos(ALPHA);

        vy = - GRAVITY*2 * t + V0 * sin(ALPHA);
    }

    else if(this->isOnGround()){
            if(this->animation->getIsRunning()){
                vx = RUNNING_SPEED;
            }
            else {
                // walking by default
                vx = WALKING_SPEED;
            }
    } //else qWarning("None condition of movement have been implied in position update");
    else
    {
        std::chrono::time_point<std::chrono::system_clock> currentTimeStamp = std::chrono::system_clock::now();
        std::chrono::duration<double> time = currentTimeStamp - this->lastJumpTimeStamp;

        double t = time.count();

        if(this->animation->getIsRunning())
            vx = RUNNING_SPEED * cos(ALPHA);
        else
            vx = WALKING_SPEED * cos(ALPHA);

        vy = - GRAVITY*2 * t + WALKING_SPEED * sin(ALPHA);
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

        if(!collisionSide.first.has_value())
        {
            if (collisionCompute.first.has_value())
            {
                if (collisionCompute.first.value()==TOP)
                {
                    collidedTopTileRect = tileRect;
                    collisionSide.first.emplace(TOP);
                }
                else if (collisionCompute.first.value()==BOTTOM)
                {
                    collidedBottomTileRect = tileRect;
                    collisionSide.first.emplace(BOTTOM);
                }
            }
        }

        if(!collisionSide.second.has_value())
        {
            if (collisionCompute.second.has_value())
            {
                if (collisionCompute.second.value()==LEFT)
                {
                    collidedRightTileRect = tileRect;
                    collisionSide.second.emplace(LEFT);
                }
                else if (collisionCompute.second.value()==RIGHT)
                {
                    collidedLeftTileRect = tileRect;
                    collisionSide.second.emplace(RIGHT);
                }
            }
        }

        if(collisionSide.first.has_value())
            if(collisionSide.first.value()==BOTTOM)
                if(collisionCompute.first.has_value())
                    if (collisionCompute.first.value()==TOP){
                        collidedTopTileRect = tileRect;
                        collisionSide.first.emplace(TOP);
                    }

        if(collisionSide.second.has_value())
            if(collisionSide.second.value()==LEFT)
                if(collisionCompute.second.has_value())
                    if (collisionCompute.second.value()==LEFT)
                    {
                        collidedRightTileRect = tileRect;
                        collisionSide.second.emplace(LEFT);
                    }
    }

    if(collisionSide.first.has_value())
    {

        if (collisionSide.first.value()==TOP)
        {

            if(!playerJump && !isJumping)
            {
                onGround=true;
                inAir=false;
            }

            if(!playerJump && isJumping)
            {
                onGround=true;
                inAir=false;
                isJumping=false;
            }

            if(againstWall && playerJump && !isJumping)
            {
                onGround=true;
                if(playerJump)
                {
                    vy=1;
                    onGround=false;
                }
            }
            else if(playerJump && !isJumping)
            {
                onGround=false;
                inAir=true;
                isJumping=true;
            }
        }

    }
    else
    {
        if(this->inAir==false)
            this->setInAir(true);
        this->onGround=false;
    }

    if(collisionSide.second.has_value())
    {
        if(collisionSide.second.value()==LEFT)
        {
            againstWall=true;
            if(!collisionSide.first.has_value())
                if(inAir==false)
                {
                    setInAir(true);
                    onGround=false;
                }
        }
    }
    else
        againstWall=false;

    if(onGround)
        yPlayer = this->map->getScene()->height()/32 - collidedTopTileRect.y()/32 + collidedTopTileRect.height()/32;

    if(againstWall)
        vx=0;

    if(playerJump)
        playerJump=false;



    // Applies the whole velocity logic
    xPlayer += vx;
    yPlayer += vy;

    //std::cout << "Player recalculated position is " << xPlayer << ", " << yPlayer << std::endl;
    // Reconvert the coordinates to game based coordinates
    xPlayer *= 32;
    yPlayer *= 32;
    yPlayer = this->map->getScene()->height() - yPlayer;



    if((xPlayer + this->animation->pixmap().width() >= this->map->getScene()->width()) || (yPlayer + this->animation->pixmap().height() >= this->map->getScene()->height())){
           double gameX = this->spawnCoords.first * 32;
           double gameY = this->spawnCoords.second * 32;

           gameY = this->map->getScene()->height() - gameY;


           getAnimation()->setPos(gameX, gameY);

           emit playerMoved();
           return;
    }
    if(this->animation->getIsRunning())
    {
        this->animation->setPos(xPlayer, yPlayer - FOX_RUN_SPRITE_HEIGHT + TILE_SIZE -1);
        this->spritePosition = {xPlayer,yPlayer - FOX_RUN_SPRITE_HEIGHT + TILE_SIZE -1};
    }
    else
    {
        this->animation->setPos(xPlayer, yPlayer - FOX_WALK_SPRITE_HEIGHT + TILE_SIZE -1);
        this->spritePosition = {xPlayer,yPlayer - FOX_WALK_SPRITE_HEIGHT + TILE_SIZE -1};
    }
    emit playerMoved();
}

void Player::updateHealthbar()
{
    this->hp--;
    std::cout << hp << std::endl;
    if(hp==0)
    {
        emit playerDeath();

    }
}

    void Player::playerAccelerated()
    {
        if(!animation->getIsRunning()){
            qInfo() << "Player accelerated\n";
            this->getAnimation()->setIsRunning(true);
        }
    }

    void Player::playerJumped(){
        if(!playerJump){
            if(!inAir)
            {
                qInfo() << "Player jumped \n";
                this->setInAir(true);
                playerJump = true;
                isJumping = true;
                onGround = false;
            }
        }
    }

    void Player::playerSlowedDown(){
        if(animation->getIsRunning()){
            qInfo() << "Player slowed down\n";
            this->getAnimation()->setIsRunning(false);
        }
    }
