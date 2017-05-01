#include "rastr_fill.h"
#include <QDebug>

void rast_fill(DrawData& data, QGraphicsScene* scene)
{
    if (data.edges.size() > 0) {
        for (unsigned i = 0; i < data.edges.size() - 1; ++i) {
            fill_edge(data.edges[i], data.edges[i + 1], data.partition, *data.image, *data.painter, scene);
        }
        fill_edge(data.edges[0], data.edges[data.edges.size() - 1], data.partition, *data.image, *data.painter, scene);
    }
}

void fill_line(QPoint& pivot, qint32 partition, QPixmap& pixmap, QPainter& painter)
{
    int y = pivot.y();
    int x1 = pivot.x();
    int x2 = partition;

    QImage img = pixmap.toImage();
    QColor color;

    if (x1 > x2) {
        x2--;
        std::swap(x1, x2);
    }

    for (int x = x1 + 1; x < x2; x++) {
        color = img.pixelColor(x, y);
        if (color == "black") {
            continue;
        }
        QPoint point(x, y);
        if (color == "red") {
            painter.setPen("white");
            draw_pixel(point, painter);
        }
        else {
            painter.setPen("red");
            draw_pixel(point, painter);
        }
    }
}

void fill_edge(QPoint& start, QPoint& end, qint32 partition, QPixmap& pixmap, QPainter& painter, QGraphicsScene* scene)
{
    if (start.x() == end.x() && start.y() == end.y()) {
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

    draw_point.setX(x);
    draw_point.setY(y);

    int last = y;

    fill_line(draw_point, partition, pixmap, painter);


    for (int i = 1; i <= dx; ++i) {

        if (y != last) {
            draw_point.setX(x);
            draw_point.setY(y);
            fill_line(draw_point, partition, pixmap, painter);

            last = y;
        }

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
