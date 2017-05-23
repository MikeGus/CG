#include "paintdevice.h"

void Paintdevice::mousePressEvent(QMouseEvent *event)
{
    data.scene->clear();

    if (event->buttons() & Qt::LeftButton) {
        QPoint p(event->pos());
        split(data);

        if ((event->modifiers() & Qt::ShiftModifier) && data.buffer.size()) {
            QPoint p2(*data.buffer.rbegin());
            QLine line(p, p2);
            if (abs(line.dx()) > abs(line.dy())) {
                p.setY(p2.y());
            }
            else {
                p.setX(p2.x());
            }
        }

        switch (data.type_of_input) {
        case SPLIT:
            data.buffer.push_back(p);
            data.painter->setPen(QColor("black"));
            break;
        case SPLIT_HOLE:
            data.buffer.push_back(p);
            data.painter->setPen(QColor("black"));
            break;
        case FIGURE:
            data.buffer.push_back(p);
            data.painter->setPen(QColor("blue"));
            break;
        case FIGURE_HOLE:
            data.buffer.push_back(p);
            data.painter->setPen(QColor("blue"));
            break;
        }
        if (data.buffer.size() >= 2) {
            QLine line(*data.buffer.rbegin(), *(++data.buffer.rbegin()));
            data.painter->drawLine(line);
        }
    }
    else if (event->buttons() & Qt::RightButton) {
        data.pixmap->fill();
        if (data.buffer.size() > 2) {
            switch (data.type_of_input) {
            case SPLIT:
                data.split.bounds = data.buffer;
                data.split.holes.clear();
                data.painter->setPen(QColor("black"));
                break;
            case SPLIT_HOLE:
                data.split.holes.push_back(data.buffer);
                data.painter->setPen(QColor("black"));
                break;
            case FIGURE:
                data.fig.bounds = data.buffer;
                data.fig.holes.clear();
                data.painter->setPen(QColor("blue"));
                break;
            case FIGURE_HOLE:
                data.fig.holes.push_back(data.buffer);
                data.painter->setPen(QColor("blue"));
                break;
            }
        }
        data.buffer.clear();
        split(data);
    }
    data.scene->addPixmap(*data.pixmap);
}

void Paintdevice::del_data()
{
    clear();
    data.pixmap->fill();
}
