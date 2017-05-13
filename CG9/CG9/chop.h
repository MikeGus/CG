#ifndef CHOP_H
#define CHOP_H

#include "paintdata.h"
#include <QDebug>

void chop(Paintdata& data);

QPoint norm(QLine& line);

QPoint vector(QLine &line);

int scalar(QPoint& vector_1, QPoint& vector_2);

int get_side(QPoint& point, QLine& edge);

double get_t(int Qi, int Pi);

void chop_line(QVector<QPoint>& splitter, QLine& line, Paintdata& data);

#endif // CHOP_H
