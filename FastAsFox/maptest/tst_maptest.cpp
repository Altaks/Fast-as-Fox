#include <QtTest>


#include "../FastAsFoxGame/map.h"
#include "../FastAsFoxGame/mapsection.h"
#include "../FastAsFoxGame/tileset.h"
#include "../FastAsFoxGame/constants.h"
#include <vector>
// add necessary includes here

class MapTest : public QObject
{
    Q_OBJECT

    Map * map;
    MapSection * mapSection;
    TileSet * tileSet;
    std::vector<TileSet*> availableTileSets;
public:
    MapTest();

private slots:
    void initTestCase();
    void init();

    //void test_getters();

    void cleanup();
    void cleanupTestCase();

};

MapTest::MapTest()
{

}

void MapTest::initTestCase()
{
    tileSet = new TileSet(":/texture/sprites/texture/TX Tileset Ground.png",32,0);
    mapSection = new MapSection(LEVEL_ONE);
    availableTileSets.push_back(tileSet);
}

void MapTest::init()
{
    map = new Map(mapSection,availableTileSets);
}

/*void MapTest::test_getters()
{
    //QCOMPARE(map->getMap()->at(0),mapSection);
}*/

void MapTest::cleanup()
{

}

void MapTest::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(MapTest)

#include "tst_maptest.moc"
