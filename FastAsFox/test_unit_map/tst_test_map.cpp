#include <QtTest>

// add necessary includes here

class test_map : public QObject
{
    Q_OBJECT

public:
    test_map();
    ~test_map();

private slots:
    void test_case1();

};

test_map::test_map()
{

}

test_map::~test_map()
{

}

void test_map::test_case1()
{

}

QTEST_APPLESS_MAIN(test_map)

#include "tst_test_map.moc"
