#include "draw_line.h"

void draw_line(QPoint& start, QPoint& end, QPainter& painter)
{
    if (start.x() == end.x() && start.y() == end.y()) {
        draw_pixel(start, painter);
        return;
    }

    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    int sx = get_sign(dx);
    int sy = get_sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;

    if (dx < dy) {
        int t = dy;
        dy = dx;
        dx = t;
        swap = true;
    }

    int k = 2 * dy;
    int error = k - dx;

    int x = start.x();
    int y = start.y();

    QPoint draw_point;

    for (int i = 1; i <= dx; ++i) {
        draw_point.setX(x);
        draw_point.setY(y);
        draw_pixel(draw_point, painter);

        if (error >= 0) {
            if (!swap) {
                y += sy;
            }
            else {
                x += sx;
            }
            error -= 2 * dx;
        }
        if (error < 0) {
            if (!swap) {
                x += sx;
            }
            else {
                y += sy;
            }
        }
        error += k;
    }
}
