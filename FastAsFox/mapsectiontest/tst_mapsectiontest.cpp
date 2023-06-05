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

private slots:
    void initTestCase();
    void init();

    void test_case1();

    void cleanup();
    void cleanupTestCase();
};

void mapSectionTest::initTestCase()
{
    mapSection = new MapSection(LEVEL_ONE);
}

void mapSectionTest::init()
{

}

void mapSectionTest::test_case1()
{
    for (std::map<std::pair<int, int>,int>::iterator it=mapSection->getCoordinatesToTileId().begin(); it!=mapSection->getCoordinatesToTileId().end(); it++)
        std::cout << it->first.first << "; " << it->first.second << " => " << it->second << '\n';
    //coordinates = std::pair<int,int>(0,0);
    //QCOMPARE(mapSection->getCoordinatesToTileId().at(coordinates),0);
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
