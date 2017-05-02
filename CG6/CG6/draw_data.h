#ifndef DRAW_DATA_H
#define DRAW_DATA_H

#include <QImage>
#include <vector>
#include <QPixmap>
#include <QPainter>

struct DrawData {
    qint32 partition;
    QPixmap* image;
    QPainter* painter;
    QPoint lastpoint;
};
#endif // DRAW_DATA_H
