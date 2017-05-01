#ifndef DRAW_DATA_H
#define DRAW_DATA_H

#include <QImage>
#include <vector>
#include <QPixmap>
#include <QPainter>

struct DrawData {
    std::vector<QPoint> edges;
    qint32 partition;
    QPixmap* image;
    QPainter* painter;
};
#endif // DRAW_DATA_H
