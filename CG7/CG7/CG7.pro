#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T15:06:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintdevice.cpp \
    chop.cpp

HEADERS  += mainwindow.h \
    paintdevice.h \
    paintdata.h \
    myqgraphicsview.h \
    chop.h

FORMS    += mainwindow.ui
