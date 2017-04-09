#ifndef POINT_H
#define POINT_H

#include <QGraphicsScene>
#include <QLine>

struct Point {
    double x;
    double y;
};

void draw_pixel(QGraphicsScene& scene, Point& point, QPen& pen);

#endif // POINT_H
