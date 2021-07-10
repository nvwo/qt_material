#include "tst_QString.hh"
#include "tst_qtestdemo.hh"
#include "tst_gui.hh"

//TEST_DECLARE(TestQString);
//TEST_DECLARE(QTestDemo);
//MULTI_TESTS_MAIN



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TEST_DECLARE(TestQString);
    TEST_DECLARE(QTestDemo);
    TEST_DECLARE(TestGui);
    srand (time(NULL));
    return MultiTests::run(argc, argv);
}

