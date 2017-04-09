#include "draw_oct.h"

void draw_oct(QGraphicsScene& scene, Point& center, int x, int y, DrawData& data)
{
    Point draw_point;
    draw_point.x = center.x + x;
    draw_point.y = center.y + y;
    draw_pixel(scene, draw_point, data.pen);
    draw_point.y = center.y - y;
    draw_pixel(scene, draw_point, data.pen);
    draw_point.x = center.x - x;
    draw_pixel(scene, draw_point, data.pen);
    draw_point.y = center.y + y;
    draw_pixel(scene, draw_point, data.pen);
}
