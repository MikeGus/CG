#ifndef SPLIT_H
#define SPLIT_H
#include "paintdata.h"
#include <QLinkedList>
#include <QDebug>
#include <QLine>

void split(Paintdata& data);

QVector<QLinkedList<QPoint>> form_lists(figure& f);

bool crossing(QPoint& p1, QPoint& p2, QPoint& p3, QPoint& p4, QPoint& cross);

void fill_vectors(QVector<QLinkedList<QPoint>>& split_list, QVector<QLinkedList<QPoint>>& figure_list,
                  QLinkedList<QPoint>& point_in, QLinkedList<QPoint>& point_out);

bool in_line(QPoint& p1, QPoint& p2, QPoint& p);

bool in_list(QLinkedList<QPoint>& list, QPoint& p);
void insert_crossing(QLinkedList<QPoint>& list, QLinkedList<QPoint>& in, QLinkedList<QPoint>& out);

#endif // SPLIT_H
