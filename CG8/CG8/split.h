#ifndef SPLIT_H
#define SPLIT_H
#include "paintdata.h"
#include <QLinkedList>
#include <QDebug>
#include <QLine>

struct Trio
{
    public:
        Trio() = default;
        Trio(QPoint& p1, QLinkedList<QPoint>::iterator& p2, QLinkedList<QPoint>::iterator& p3): p(p1), fig(p2), spl(p3){}

        QPoint p;
        QLinkedList<QPoint>::iterator fig;
        QLinkedList<QPoint>::iterator spl;
};


void split(Paintdata& data);

QVector<QLinkedList<QPoint>> form_lists(figure& f);

bool crossing(QPoint& p1, QPoint& p2, QPoint& p3, QPoint& p4, QPoint& cross);

void fill_vectors(QVector<QLinkedList<QPoint>>& split_list, QVector<QLinkedList<QPoint>>& figure_list,
                  QLinkedList<QPoint>& point_in, QLinkedList<QPoint>& point_out);

bool in_line(QPoint& p1, QPoint& p2, QPoint& p);

bool in_list(QLinkedList<QPoint>& list, QPoint& p);

void insert_crossing(QLinkedList<QPoint>& list_spl, QLinkedList<QPoint>& list_fig, QVector<Trio>& trio);

int check_visibility(QLinkedList<QPoint>& list_1, QVector<QLinkedList<QPoint> >& list_2, QLinkedList<QPoint>& list_in, QLinkedList<QPoint>& list_out);

#endif // SPLIT_H
