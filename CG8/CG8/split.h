#ifndef SPLIT_H
#define SPLIT_H
#include "paintdata.h"
#include <QLinkedList>
#include <QDebug>

void split(Paintdata& data);

QVector<QLinkedList<QPoint>> form_lists(figure& f);

bool crossing(QPoint& p1, QPoint& p2, QPoint& p3, QPoint& p4, QPoint& cross);

void fill_vectors(QVector<QLinkedList<QPoint>>& split_list, QVector<QLinkedList<QPoint>>& figure_list,
                  QLinkedList<QPoint>& point_in, QLinkedList<QPoint>& point_out);

#endif // SPLIT_H
