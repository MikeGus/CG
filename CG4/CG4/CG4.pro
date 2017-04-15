#-------------------------------------------------
#
# Project created by QtCreator 2017-04-02T14:10:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draw.cpp \
    parts.cpp \
    draw_circle.cpp \
    draw_oct.cpp \
    draw_pixel.cpp

HEADERS  += mainwindow.h \
    algorithms.h \
    draw.h \
    drawdata.h \
    parts.h \
    point.h \
    sign.h \
    draw_circle.h \
    draw_oct.h \
    draw_pixel.h

FORMS    += mainwindow.ui
