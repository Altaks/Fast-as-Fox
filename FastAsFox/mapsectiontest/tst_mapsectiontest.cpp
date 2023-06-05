#include <QtTest>

// add necessary includes here

class mapSectionTest : public QObject
{
    Q_OBJECT

public:
    mapSectionTest();
    ~mapSectionTest();

private slots:
    void test_case1();

};

mapSectionTest::mapSectionTest()
{

}

mapSectionTest::~mapSectionTest()
{

}

void mapSectionTest::test_case1()
{

}

QTEST_APPLESS_MAIN(mapSectionTest)

#include "tst_mapsectiontest.moc"
