#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QObject>
#include <QRectF>
#include <QDebug>
#include "paintdata.h"
#include "split.h"


class Paintdevice : public QGraphicsScene
{
public:
    Paintdevice(QObject* parent = nullptr) : QGraphicsScene(parent)
    {
        data.scene = dynamic_cast<QGraphicsScene*> (this);
    }
    Paintdevice(const QRectF& sceneRect, QObject* parent = nullptr) : QGraphicsScene(sceneRect, parent)
    {
        data.scene = dynamic_cast<QGraphicsScene*> (this);
    }
    Paintdevice(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr) :
        QGraphicsScene(x, y, width, height, parent){
        data.scene = dynamic_cast<QGraphicsScene*> (this);
    }


    void mousePressEvent(QMouseEvent* event);
    void del_data();

    Paintdata data;
};

#endif // GRAPHICSVIEW_H
