#-------------------------------------------------
#
# Project created by QtCreator 2017-05-13T17:14:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG9
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintdevice.cpp \
    chop.cpp

HEADERS  += mainwindow.h \
    myqgraphicsview.h \
    paintdata.h \
    paintdevice.h \
    chop.h

FORMS    += mainwindow.ui
