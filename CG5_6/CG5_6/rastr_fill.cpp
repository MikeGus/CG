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

    if (pixmap.width() < partition) {
        x2 = pixmap.width();
    }

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
    if (start.y() == end.y()) {
        return;
    }

    int dy = end.y() - start.y();
    int dx = end.x() - start.x();

    int sy = get_sign(dy);
    int sx = get_sign(dx);

    int y1 = start.y();
    int y2 = end.y();

    int x1 = start.x();
    int x2 = end.x();

    if (sy > 0) {
        std::swap(x1, x2);
        std::swap(y1, y2);
        dy = -dy;
        dx = -dx;
    }

    QPoint point;
    for (int y = y1; y != y2; y -= 1) {
        int x = !sx ? x1 : (int) (x1 + (double) (y - y1) / dy * dx + 0.5);
        point.setX(x);
        point.setY(y);
        fill_line(point, partition, pixmap, painter);
    }
}
