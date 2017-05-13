#ifndef CHOP_H
#define CHOP_H

#include "paintdata.h"

void chop(Paintdata& data);

QPoint norm(QLine& line);

QPoint vector(QLine &line);

int scalar(QPoint& vector_1, QPoint& vector_2);

int get_side(QPoint& point, QLine& edge);

double get_t(QLine& line, QLine& edge);

#endif // CHOP_H
