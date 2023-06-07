#include <QtTest>

// add necessary includes here

class test_tileSet : public QObject
{
    Q_OBJECT

public:
    test_tileSet();
    ~test_tileSet();

private slots:
    void test_case1();

};

test_tileSet::test_tileSet()
{

}

test_tileSet::~test_tileSet()
{

}

void test_tileSet::test_case1()
{

}

QTEST_APPLESS_MAIN(test_tileSet)

#include "tst_test_tileset.moc"
