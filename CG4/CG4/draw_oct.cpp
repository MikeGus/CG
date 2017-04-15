#include "draw_oct.h"

void draw_oct(QGraphicsScene& scene, Point& center, int x, int y, DrawData& data)
{
    Point draw_point;
    draw_point.x = center.x + x;
    draw_point.y = center.y + y;
    draw_pixel(draw_point, data);
    draw_point.y = center.y - y;
    draw_pixel(draw_point, data);
    draw_point.x = center.x - x;
    draw_pixel(draw_point, data);
    draw_point.y = center.y + y;
    draw_pixel(draw_point, data);
}
