#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T14:30:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM_Lecteur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clickablelabel.cpp

HEADERS  += mainwindow.h \
    clickablelabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
