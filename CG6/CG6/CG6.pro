#-------------------------------------------------
#
# Project created by QtCreator 2017-05-02T11:21:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draw_line.cpp \
    draw_pixel.cpp \
    filling.cpp

HEADERS  += mainwindow.h \
    draw_data.h \
    draw_line.h \
    draw_pixel.h \
    sign.h \
    filling.h

FORMS    += mainwindow.ui
