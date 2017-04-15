#ifndef DRAWDATA_H
#define DRAWDATA_H

#include "algorithms.h"
#include "point.h"
#include <QPen>
#include <QPainter>

struct DrawData {
    Algorithms alg;
    Point start;
    Point end;
    QPainter* painter;
    QPixmap* map;
};

#endif // DRAWDATA_H
