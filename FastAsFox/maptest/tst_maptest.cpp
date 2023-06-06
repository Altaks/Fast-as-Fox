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

    void test_case1();

    void cleanup();
    void cleanupTestCase();
};

MapTest::MapTest()
{

}

void MapTest::initTestCase()
{
    mapSection = new MapSection(LEVEL_ONE);
    tileSet = new TileSet(GROUND_TILES,32,0);
    availableTileSets.push_back(tileSet);
}

void MapTest::init()
{
    map = new Map(mapSection, availableTileSets);
}

void MapTest::test_case1()
{

}

void MapTest::cleanup()
{

}

void MapTest::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(MapTest)

#include "tst_maptest.moc"
