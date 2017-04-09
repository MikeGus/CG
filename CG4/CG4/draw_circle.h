#ifndef DRAW_CIRCLE_H
#define DRAW_CIRCLE_H

#include "drawdata.h"
#include "draw_oct.h"
#include "algorithms.h"
#include "point.h"
#include "sign.h"
#include "parts.h"
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsEllipseItem>

void draw_circle(QGraphicsScene& scene, DrawData& data);
void draw_default_circle(QGraphicsScene& scene, DrawData& data);
void draw_middle_point_circle(QGraphicsScene& scene, DrawData& data);
void draw_canonic_circle(QGraphicsScene& scene, DrawData& data);
void draw_parametric_circle(QGraphicsScene& scene, DrawData& data);
void draw_bresenham_circle(QGraphicsScene& scene, DrawData& data);

#endif // DRAW_CIRCLE_H
