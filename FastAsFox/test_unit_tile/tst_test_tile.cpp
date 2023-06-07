#include <QtTest>

// add necessary includes here
#include "../FastAsFoxGame/tile.h"


class test_tile : public QObject
{
    Q_OBJECT


private:
    QPixmap* map;
    QPixmap* map2;
    Tile * test_tiles;
    Tile * test_tiles2;
public:
    test_tile();
    ~test_tile();
    void initTestCase();
    void cleanupTestCase();
private slots:
    void test_case1();

};

test_tile::test_tile()
{

    map= new QPixmap(32,32);
    map2= new QPixmap(31,32);
    test_tiles=new Tile(map,0,1,3);
    test_tiles2=new Tile(map2,1,0,7);
}

test_tile::~test_tile()
{

}

void test_tile::test_case1()
{

}

void test_tile::initTestCase(){

}


void test_tile::cleanupTestCase(){
    delete test_tiles;
    delete test_tiles2;

}







QTEST_APPLESS_MAIN(test_tile)

#include "tst_test_tile.moc"
