#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T10:23:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG10
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintdevice.cpp \
    split.cpp

HEADERS  += mainwindow.h \
    figure.h \
    myqgraphicsview.h \
    paintdata.h \
    paintdevice.h \
    split.h

FORMS    += mainwindow.ui
