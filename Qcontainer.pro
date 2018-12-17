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
    listselector.cpp

HEADERS += \
    mainwindow.h \
    dao.h \
    container.h \
    container_dao.h \
    deepptr.h \
    dildo.h \
    myexception.h \
    defaults.h \
    fileselector.h \
    deeptr_dao_dildo.h \
    searchvalidator.h \
    listselector.h \
    validator.h

