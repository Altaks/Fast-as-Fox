#include <QtTest>

// add necessary includes here

class test_mapSection : public QObject
{
    Q_OBJECT

public:
    test_mapSection();
    ~test_mapSection();

private slots:
    void test_case1();

};

test_mapSection::test_mapSection()
{

}

test_mapSection::~test_mapSection()
{

}

void test_mapSection::test_case1()
{

}

QTEST_APPLESS_MAIN(test_mapSection)

#include "tst_test_mapsection.moc"
