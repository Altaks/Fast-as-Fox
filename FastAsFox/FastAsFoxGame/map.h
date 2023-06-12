#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "gameobject.h"
#include "tileset.h"
#include "mapsection.h"
#include "tile.h"
#include <QPushButton>
#include <QMovie>


class Player; //Forward declaration of player, to avoid creating an circular inclusion, as map.h is already included in player.h



class Map : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief mapScene the scene that contains every object in the game
     */
    QGraphicsScene * mapScene = nullptr;
    /**
     * @brief mapView the camera, basically
     */
    QGraphicsView * mapView = nullptr;
    /**
     * @brief sections vector storing every section of the map
     */
    std::vector<MapSection *> sections;
    /**
     * @brief tileSets vector storing the tilesets used to render the map
     */
    std::vector<TileSet *> * tileSets;
    /**
     * @brief loadedTiles map storing the texture of every tile in the map, as well as its ID
     */
    std::map<int, QPixmap*> loadedTiles;
    /**
     * @brief actuallyLoadedTiles vector storing every Tile object in the map
     */
    std::vector<Tile *> * actuallyLoadedTiles = nullptr;
    /**
     * @brief itsPlayer the player that will venture the map
     */
    Player* itsPlayer;
    std::string lcdCount;
    QPushButton *homeButton;
public:
    /**
     * @brief Map the constructor of the map class
     * @param defaultSection
     * @param availableTileSets
     */
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();
    /**
     * @brief load loads the map in the scene
     */
    void load();
    /**
     * @brief getMap getter for the Map class
     * @return every section from the map
     */
    std::vector<MapSection *>* getMap();
    /**
     * @brief getScene getter for mapScene
     * @return mapScene
     */
    QGraphicsScene * getScene();
    /**
     * @brief getView getter for mapView
     * @return mapView
     */
    QGraphicsView * getView();
    /**
     * @brief getActuallyLoadedTiles getter for actuallyLoadedTiles
     * @return actuallyLoadedTiles
     */
    std::vector<Tile *> *getActuallyLoadedTiles() const;
    /**
     * @brief setItsPlayer setter for itsPlayer
     * @param playerthe Player to be set as our current map's player
     */

    void setItsPlayer(Player* player);
    /**
     * @brief getItsPlayer getter for itsPlayer
     * @return itsPlayer
     */
    Player* getItsPlayer();

    std::vector<MapSection *> getSections() const;

    void setLcdCount(const std::string &value);
    void displayAnimation();


public slots:
    /**
     * @brief updateView updates the view to follow the player
     */
    void updateView();
    void handleLevelMenuButton() {
        emit golevelMenu();
    }

signals:
    void homeButtonClicked();
    void golevelMenu();
};





class LevelMenuButton : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    LevelMenuButton(QPixmap pixmap, QGraphicsItem *parent = nullptr)
        : QObject(), QGraphicsPixmapItem(pixmap, parent) {}

signals:
    void golevelMenu();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        emit golevelMenu();
    }
};




































































































































































































































































// Bien joué tu m'as trouvé


class GifItem : public QGraphicsItem {
public:
    GifItem(const QString &fileName, QGraphicsItem *parent = nullptr) : QGraphicsItem(parent) {
        movie = new QMovie(fileName);

        if (!movie->isValid()){
            delete movie;
            throw std::invalid_argument("Gif is not valid.");
        }

        if (movie->frameCount() <= 1) {
            delete movie;
            throw std::invalid_argument("This Gif does not have multiple frames.");
        }

        // Connect the frameChanged signal of QMovie to the slot for updating the graphics item
        QObject::connect(movie, &QMovie::frameChanged, [this](int frameNumber) {
            Q_UNUSED(frameNumber)
            this->update();
        });

        movie->start();
    }

    QRectF boundingRect() const override {
        return QRectF(-movie->frameRect().center(), movie->currentImage().size());
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->drawPixmap(-movie->frameRect().center(), movie->currentPixmap());
    }

private:
    QMovie *movie;
};



class AnimationHelper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    AnimationHelper(QGraphicsItem *item, QObject *parent = nullptr) : QObject(parent), m_item(item) {}
    QPointF pos() const { return m_item->pos(); }
    void setPos(const QPointF &pos) { m_item->setPos(pos); }

private:
    QGraphicsItem *m_item;
};


#endif // MAP_H
