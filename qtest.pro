QT += core testlib
QT += gui widgets
#CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++11

#TEMPLATE = app

SOURCES +=  tst_qtestdemo.cpp \
    main.cpp \
    tst_QString.cpp \
    tst_gui.cpp

HEADERS += MultiTests.hh \
    tst_QString.hh \
    tst_gui.hh \
    tst_qtestdemo.hh


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
