#ifndef SPLIT_H
#define SPLIT_H
#include "paintdata.h"
#include <QLinkedList>
#include <QDebug>
#include <QLine>

void split(Paintdata& data);

bool crossing(QPoint& p1, QPoint& p2, QPoint& p3, QPoint& p4, QPoint& cross);

bool inside_edge(QPoint& S, QLine& edge);

int scalar(QPoint& vec_1, QPoint& vec_2);

QPoint norm(QPoint& p1, QPoint& p2);

QPoint norm(QLine& vec);

bool invert(QVector<QPoint>& splitter);

#endif // SPLIT_H
