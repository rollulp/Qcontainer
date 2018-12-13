#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T19:29:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qcontainer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


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
    listselector.h

FORMS +=
