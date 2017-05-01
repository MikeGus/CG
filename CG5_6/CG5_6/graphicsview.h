#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGuiApplication>

class MyQGraphicsView : public QGraphicsView {
public:
    MyQGraphicsView(QWidget *parent = nullptr) : QGraphicsView(QWidget *parent = nullptr)
    {
        setMouseTracking(true);
    }

private:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

void MyQGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (QGuiApplication::queryKeyboardModifiers() == Qt::ControlModifier) {
    }
}

#endif // GRAPHICSVIEW_H
