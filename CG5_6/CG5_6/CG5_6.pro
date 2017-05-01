#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T12:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG5_6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rastr_fill.cpp \
    draw_line.cpp \
    draw_pixel.cpp

HEADERS  += mainwindow.h \
    draw_data.h \
    rastr_fill.h \
    draw_line.h \
    draw_pixel.h \
    sign.h

FORMS    += mainwindow.ui
