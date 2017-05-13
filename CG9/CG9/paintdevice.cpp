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
            else {
                chop(data);
            }

            data.final = false;

        }
    }
    else {
        if (event->buttons() & Qt::RightButton) {
            if (data.splitter.size() > 2) {
                data.is_rect = true;
                data.painter->setPen(QColor("black"));
                data.painter->drawLine(*data.splitter.begin(), *data.splitter.rbegin());
                data.scene->clear();
                data.scene->addPixmap(*data.pixmap);
            }
        }
        else if (event->buttons() & Qt::LeftButton) {
            if (data.is_rect) {
                data.is_rect = false;
                data.scene->clear();
                data.pixmap->fill();
                data.splitter.clear();

                data.painter->setPen(QColor("blue"));
                for (auto& line : data.lines) {
                    data.painter->drawLine(line);
                }
                data.scene->addPixmap(*data.pixmap);
            }
            QPoint point(event->pos());
            if (data.splitter.size()) {
                QPoint prev_point(*data.splitter.rbegin());
                if (event->modifiers() & Qt::ShiftModifier) {
                    int dx = abs(point.x() - prev_point.x());
                    int dy = abs(point.y() - prev_point.y());
                    if (dx > dy) {
                        point.setY(prev_point.y());
                    }
                    else {
                        point.setX(prev_point.x());
                    }
                }

                data.painter->setPen(QColor("black"));
                data.painter->drawLine(prev_point, point);
            }
            data.splitter.push_back(point);
        }
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
