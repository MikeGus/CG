#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QGraphicsScene>
#include <QPainter>
#include <QLine>
#include <QVector>

struct Paintdata
{
    QGraphicsScene* scene;
    QPainter* painter;
    QPixmap* pixmap;
    QVector<QLine> lines;

    QVector<QPoint> splitter;

    bool final;
    QLine buffer_line;

    bool line_input;

    bool is_rect;

    Paintdata()
    {
        scene = nullptr;
        painter = nullptr;
        pixmap = nullptr;
        final = false;

        line_input = true;

        is_rect = false;
    }

    ~Paintdata()
    {
        if (painter != nullptr) {
            delete painter;
        }
        if (pixmap != nullptr) {
            delete pixmap;
        }
    }
};

#endif // PAINTDATA_H
