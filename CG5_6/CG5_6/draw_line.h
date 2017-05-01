#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include <QPoint>
#include <QPixmap>

#include "draw_pixel.h"
#include "sign.h"

void draw_line(QPoint& start, QPoint& end, QPainter& painter);

#endif // DRAW_LINE_H
