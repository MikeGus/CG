#ifndef DRAWDATA_H
#define DRAWDATA_H

#include "algorithms.h"
#include "point.h"
#include <QPen>

struct DrawData {
    Algorithms alg;
    Point start;
    Point end;
    QPen pen;
};

#endif // DRAWDATA_H
