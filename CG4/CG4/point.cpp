#include "point.h"

void draw_pixel(QGraphicsScene& scene, Point& point, QPen& pen)
{
    QLine line(point.x, point.y, point.x, point.y);
    scene.addLine(line, pen);
}
