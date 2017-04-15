#ifndef DRAW_H
#define DRAW_H

#include "drawdata.h"
#include "draw_oct.h"
#include "algorithms.h"
#include "point.h"
#include "sign.h"
#include "parts.h"
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsEllipseItem>

void draw(QGraphicsScene& scene, DrawData& data);
void draw_default(DrawData& data);
void draw_middle_point(QGraphicsScene& scene, DrawData& data);
void draw_canonic(QGraphicsScene& scene, DrawData& data);
void draw_parametric(QGraphicsScene& scene, DrawData& data);
void draw_bresenham(QGraphicsScene& scene, DrawData& data);

#endif // DRAW_H
