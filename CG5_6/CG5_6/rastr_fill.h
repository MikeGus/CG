#ifndef RASTR_FILL_H
#define RASTR_FILL_H

#include "draw_data.h"
#include "draw_line.h"
#include <QGraphicsScene>
#include <QApplication>

void rast_fill(DrawData& data, QGraphicsScene *scene, bool timer);

void fill_edge(QPoint& start, QPoint& end, qint32 partition, QPixmap &pixmap, QPainter &painter, QGraphicsScene *scene, bool timer);

void fill_line(QPoint& pivot, qint32 partition, QPixmap& pixmap, QPainter& painter);


#endif // RASTR_FILL_H
