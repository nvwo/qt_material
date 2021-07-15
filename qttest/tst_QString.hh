#ifndef TST_QSTRING_HH
#define TST_QSTRING_HH

#include "MultiTests.hh"

class TestQString: public QObject
{
    Q_OBJECT
public:
    TestQString();
    ~TestQString();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void toUpper();
    void toLower();
};

//TEST_DECLARE(TestQString);

#endif // TST_QSTRING_HH
