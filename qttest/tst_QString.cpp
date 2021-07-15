#include "tst_QString.hh"


TestQString::TestQString()
{
    qDebug(this->metaObject()->className());
}

TestQString::~TestQString()
{

}

void TestQString::initTestCase()
{

}

void TestQString::cleanupTestCase()
{

}

void TestQString::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

void TestQString::toLower()
{
    QString str = "Hello";
    QCOMPARE(str.toLower(), QString("hello"));
}


//#include "tst_Qstring.moc"
