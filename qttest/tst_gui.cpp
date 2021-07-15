#include "tst_gui.hh"
//#include <QtWidgets>
#include <QLineEdit>
//#include <QtTest/QtTest>

// QTest: : keyClick ()、
// QTest: : keyPress ()、 QTest: : keyRelease ()、 QTest: : : mouseClick ()、 QTest: : : mouseDClick ()、 QTest: : mouseemove ()、 QTest: : mousePress ()和 QTest: : mouseRelease ()
void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world2");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}
