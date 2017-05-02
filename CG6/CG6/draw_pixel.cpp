#include "draw_pixel.h"

void draw_pixel(QPoint& point, QPainter& painter)
{
    painter.drawPoint(point.x(), point.y());
}
