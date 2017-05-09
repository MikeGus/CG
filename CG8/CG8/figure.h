#ifndef FIGURE_H
#define FIGURE_H

#include <QPoint>
#include <QVector>

struct figure
{
    QVector<QPoint> bounds;
    QVector<QVector<QPoint>> holes;
};


#endif // FIGURE_H
