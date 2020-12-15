#-------------------------------------------------
#
# Project created by QtCreator 2020-10-27T14:00:17
#
#-------------------------------------------------

QT       += core gui
QT+=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manageMagazine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    movelabel.cpp \
    mydb.cpp \
    mainwindow2.cpp \
    bookwidget.cpp \
    sqlthread.cpp \
    promptwindow.cpp \
    orderwindow.cpp

HEADERS += \
        mainwindow.h \
    movelabel.h \
    mydb.h \
    mainwindow2.h \
    bookwidget.h \
    sqlthread.h \
    promptwindow.h \
    orderwindow.h

FORMS += \
    mainwindow.ui \
    mainwindow2.ui \
    bookwidget.ui \
    promptwindow.ui \
    orderwindow.ui

RESOURCES += \
    myicon.qrc

