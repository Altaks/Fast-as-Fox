#include <QtTest>
#include <iostream>
#include "../FastAsFoxGame/mapsection.h"
#include "../FastAsFoxGame/constants.h"

// add necessary includes here
class mapSectionTest : public QObject
{
    Q_OBJECT

    MapSection* mapSection;
    std::pair<int, int> coordinates;

public:
    mapSectionTest();

private slots:
    void initTestCase();
    void init();

    void test_case1();

    void cleanup();
    void cleanupTestCase();
};

mapSectionTest::mapSectionTest()
{

}

void mapSectionTest::initTestCase()
{
    mapSection = new MapSection(LEVEL_ONE);
}
void mapSectionTest::init()
{
}
void mapSectionTest::test_case1()
{
    coordinates = std::pair<int,int>(0,0);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),76);
    coordinates = std::pair<int,int>(0,1);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),60);
    coordinates = std::pair<int,int>(1,0);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),76);
    coordinates = std::pair<int,int>(1,1);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),60);
}
void mapSectionTest::cleanup()
{
}
void mapSectionTest::cleanupTestCase()
{
    delete mapSection;
}
QTEST_APPLESS_MAIN(mapSectionTest)

#include "tst_mapsectiontest.moc"
