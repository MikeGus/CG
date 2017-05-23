#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QGraphicsScene>
#include <QPainter>
#include "figure.h"

const unsigned char ZERO = 0x00;

const unsigned char SPLIT = 0x01;
const unsigned char SPLIT_HOLE = 0x02;
const unsigned char FIGURE = 0x04;
const unsigned char FIGURE_HOLE = 0x08;

struct Paintdata
{
    QGraphicsScene* scene;
    QPainter* painter;
    QPixmap* pixmap;

    figure fig;
    figure split;

    QVector<QPoint> buffer;
    unsigned char type_of_input;

    Paintdata()
    {
        scene = nullptr;
        painter = nullptr;
        pixmap = nullptr;

        type_of_input = ZERO;
    }

    ~Paintdata()
    {
        if (painter != nullptr) {
            delete painter;
        }
        if (pixmap != nullptr) {
            delete pixmap;
        }
    }
};

#endif // PAINTDATA_H
