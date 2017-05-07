#include "paintdevice.h"

void Paintdevice::mousePressEvent(QMouseEvent *event)
{
    if (data.line_input) {
        if (!data.final) {
            data.buffer_line.setP1(event->pos());
            data.final = true;
        }
        else {
            if (!(event->modifiers() & Qt::ShiftModifier)) {
                data.buffer_line.setP2(event->pos());
            }
            else {
                qint32 x = event->pos().x();
                qint32 y = event->pos().y();
                qint32 dx = abs(x - data.buffer_line.p1().x());
                qint32 dy = abs(y - data.buffer_line.p1().y());
                if (dx > dy) {
                    data.buffer_line.setP2(QPoint(x, data.buffer_line.p1().y()));
                }
                else {
                    data.buffer_line.setP2(QPoint(data.buffer_line.p1().x(), y));
                }
            }
            data.lines.push_back(data.buffer_line);

            if (!data.is_rect) {
                QColor bufcolor = data.painter->pen().color();
                data.painter->setPen(QColor("blue"));
                data.painter->drawLine(data.buffer_line);
                data.painter->setPen(bufcolor);
            }

            data.final = false;

        }
    }
    else {
        if (!data.final_rect) {
            data.buffer_rectangle.setBottomLeft(event->pos());
            data.final_rect = true;
        }
        else {
            QPoint p = event->pos();

            if (data.buffer_rectangle.bottomLeft().x() < p.x()) {
                if (data.buffer_rectangle.bottomLeft().y() < p.y()) {
                    data.buffer_rectangle.setTopRight(p);
                }
                else {
                    data.buffer_rectangle.setTopLeft(data.buffer_rectangle.bottomLeft());
                    data.buffer_rectangle.setBottomRight(p);
                }
            }
            else {
                if (data.buffer_rectangle.bottomLeft().y() < p.y()) {
                    data.buffer_rectangle.setBottomRight(data.buffer_rectangle.bottomLeft());
                    data.buffer_rectangle.setTopLeft(p);
                }
                else {
                    data.buffer_rectangle.setTopRight(data.buffer_rectangle.bottomLeft());
                    data.buffer_rectangle.setBottomLeft(p);
                }
            }
            data.final_rect = false;
            data.is_rect = true;
            data.rectangle = data.buffer_rectangle;
        }
    }


    if (data.is_rect && !data.final_rect) {
        QColor bufcolor = data.painter->pen().color();

        data.pixmap->fill();
        data.painter->setPen(QColor("black"));
        data.painter->drawRect(data.rectangle);
        data.painter->setPen(bufcolor);

        chop(data);
    }

    clear();
    addPixmap(*data.pixmap);
}

void Paintdevice::del_data()
{
    clear();
    data.pixmap->fill();
    data.final = false;
    data.lines.clear();
}
