#include "draw_pixel.h"

void draw_pixel(Point& point, QPainter& painter)
{
    painter.drawPoint(point.x(), point.y());
}
