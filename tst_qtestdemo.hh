#ifndef TST_QTESTDEMO_HH
#define TST_QTESTDEMO_HH

#include "MultiTests.hh"

class QTestDemo : public QObject
{
    Q_OBJECT

public:
    QTestDemo();
    ~QTestDemo();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

//TEST_DECLARE(QTestDemo);

#endif // TST_QTESTDEMO_HH
