#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T13:06:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG8
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintdevice.cpp \
    split.cpp

HEADERS  += mainwindow.h \
    myqgraphicsview.h \
    paintdata.h \
    paintdevice.h \
    figure.h \
    split.h

FORMS    += mainwindow.ui
