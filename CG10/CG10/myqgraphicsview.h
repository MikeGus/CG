#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QApplication>
#include "paintdevice.h"
#include <QDebug>

class MyQGraphicsView : public QGraphicsView {
public:
    MyQGraphicsView(QGraphicsScene *scene, QWidget *parent) :
        QGraphicsView(scene, parent) {}
    MyQGraphicsView(QWidget* parent = nullptr): QGraphicsView(parent) {}


    void mousePressEvent(QMouseEvent* event)
    {
        Paintdevice* scene =  dynamic_cast<Paintdevice*> (this->scene());
        scene->mousePressEvent(event);
    }
};

#endif // MYQGRAPHICSVIEW_H
