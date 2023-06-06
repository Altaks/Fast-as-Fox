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

    void test_firstValues();
    void test_extremitiesOfMapSection();
    void test_OOR();

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

void mapSectionTest::test_firstValues()
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

void mapSectionTest::test_extremitiesOfMapSection()
{
    coordinates = std::pair<int,int>(0,24);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),0);
    coordinates = std::pair<int,int>(74,0);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),76);
    coordinates = std::pair<int,int>(74,24);
    QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),0);
}

void mapSectionTest::test_OOR()
{
    coordinates = std::pair<int,int>(0,25);
    try
    {
        mapSection->getCoordinatesToTileId().at(coordinates);
        QFAIL("No exection thrown");
    }
    catch(std::out_of_range &oor)
    {}
    coordinates = std::pair<int,int>(75,0);
    try
    {
        mapSection->getCoordinatesToTileId().at(coordinates);
        QFAIL("No exection thrown");
    }
    catch(std::out_of_range &oor)
    {}
    coordinates = std::pair<int,int>(75,25);
    try
    {
        mapSection->getCoordinatesToTileId().at(coordinates);
        QFAIL("No exection thrown");
    }
    catch(std::out_of_range &oor)
    {}
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
