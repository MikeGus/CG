#ifndef DRAW_H
#define DRAW_H

#include "drawdata.h"
#include "algorithms.h"
#include "point.h"
#include "sign.h"
#include "parts.h"
#include <QGraphicsScene>
#include <QPen>

void draw(QGraphicsScene& scene, DrawData& data);

void draw_cda(QGraphicsScene& scene, DrawData& data);
void draw_bres_int(QGraphicsScene& scene, DrawData& data);
void draw_bres_float(QGraphicsScene& scene, DrawData& data);
void draw_bres_step(QGraphicsScene& scene, DrawData& data);
void draw_default(QGraphicsScene& scene, DrawData& data);
void draw_vu(QGraphicsScene& scene, DrawData& data);

#endif // DRAW_H
