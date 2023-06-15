#ifndef MAP_H
#define MAP_H

#include <vector>
#include <set>
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
    QGraphicsScene * mapScene = nullptr;
    QGraphicsView * mapView = nullptr;
    std::vector<MapSection *> sections;
    std::vector<TileSet *> * tileSets;
    std::map<int, QPixmap*> loadedTiles;
    std::vector<Tile *> * actuallyLoadedTiles = nullptr;
    std::set<Tile*> * toCheckForCollision = nullptr;
    Player* itsPlayer;
    std::string lcdCount;
    QPushButton *homeButton;
public:
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();
    void load();
    std::vector<MapSection *>* getMap();
    QGraphicsScene * getScene();
    QGraphicsView * getView();
    std::vector<Tile *> *getActuallyLoadedTiles() const;
    std::vector<MapSection *> getSections() const;
    void setItsPlayer(Player* player);
    Player* getItsPlayer();
    std::set<Tile *> * getToCheckForCollision() const;
    void setLcdCount(const std::string &value);
    void displayAnimation();
public slots:
    void updateView();
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

