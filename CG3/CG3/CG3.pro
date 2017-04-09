#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T18:30:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draw.cpp \
    point.cpp \
    parts.cpp

HEADERS  += mainwindow.h \
    algorithms.h \
    drawdata.h \
    point.h \
    draw.h \
    sign.h \
    parts.h

FORMS    += mainwindow.ui
