#ifndef FILLING_H
#define FILLING_H
#include "draw_data.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <vector>
#include <QApplication>

void fill_image(QPoint& point, QGraphicsScene& scene, DrawData& data, bool timer);

void fill_line(int y, int x1, int x2, std::vector<QPoint>& stack, QImage& img, QPixmap& map, QPainter& painter, QGraphicsScene& scene, bool timer);

int find_left_bound(QPoint& point, QImage& img, QPainter& painter);

int find_right_bound(QPoint& point, QImage& img, QPainter& painter);

#endif // FILLING_H
