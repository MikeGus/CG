#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QGraphicsScene>
#include <QPainter>
#include <QLine>
#include <vector>

struct Paintdata
{
    QGraphicsScene* scene;
    QPainter* painter;
    QPixmap* pixmap;
    std::vector<QLine> lines;

    bool final;
    QLine buffer_line;
    QRect rectangle;

    bool line_input;
    bool final_rect;

    bool is_rect;

    Paintdata()
    {
        scene = nullptr;
        painter = nullptr;
        pixmap = nullptr;
        final = false;

        line_input = true;
        final_rect = false;

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
