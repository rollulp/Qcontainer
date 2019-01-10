QT += core gui widgets
TARGET = Qcontainer

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    dao.cpp \
    dildo.cpp \
    myexception.cpp \
    fileselector.cpp \
    searchvalidator.cpp \
    listselector.cpp \
    mydildolistwidget.cpp

HEADERS += \
    mainwindow.h \
    dao.h \
    container.h \
    dildo.h \
    myexception.h \
    defaults.h \
    fileselector.h \
    searchvalidator.h \
    listselector.h \
    validator.h \
    mydildolistwidget.h \
    container_dildo.h

