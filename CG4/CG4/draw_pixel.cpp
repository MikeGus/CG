#include "draw_pixel.h"

void draw_pixel(Point& point, DrawData& data)
{
    data.painter->drawPoint(point.x, point.y);
}
