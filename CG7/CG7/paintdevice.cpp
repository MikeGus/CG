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
                data.lines.push_back(data.buffer_line);
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

            QColor bufcolor = data.painter->pen().color();
            data.painter->setPen(QColor("black"));

            data.painter->drawLine(data.buffer_line);
            data.final = false;

            data.painter->setPen(bufcolor);

            clear();
            addPixmap(*data.pixmap);
        }
    }
    else {
        if (!data.final_rect) {
            data.rectangle.setBottomLeft(event->pos());
            data.final_rect = true;
        }
        else {
            QPoint p = event->pos();

            if (data.rectangle.bottomLeft().x() < p.x()) {
                if (data.rectangle.bottomLeft().y() < p.y()) {
                    data.rectangle.setTopRight(p);
                }
                else {
                    data.rectangle.setTopLeft(data.rectangle.bottomLeft());
                    data.rectangle.setBottomRight(p);
                }
            }
            else {
                if (data.rectangle.bottomLeft().y() < p.y()) {
                    data.rectangle.setBottomRight(data.rectangle.bottomLeft());
                    data.rectangle.setTopLeft(p);
                }
                else {
                    data.rectangle.setTopRight(data.rectangle.bottomLeft());
                    data.rectangle.setBottomLeft(p);
                }
            }
            data.final_rect = false;
            data.is_rect = true;

            QColor bufcolor = data.painter->pen().color();
            data.painter->setPen(QColor("black"));

            data.pixmap->fill();
            data.painter->drawRect(data.rectangle);

            for (auto line : data.lines) {
                data.painter->drawLine(line);
            }

            data.painter->setPen(bufcolor);

            clear();
            addPixmap(*data.pixmap);
        }
    }
}

void Paintdevice::del_data()
{
    clear();
    data.pixmap->fill();
    data.final = false;
    data.lines.clear();
}
