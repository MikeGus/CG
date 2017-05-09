#include "split.h"

void split(Paintdata& data)
{
    //формирование связных списков вершин отсекателя и многоугольника
    QVector<QLinkedList<QPoint>> figure_list = form_lists(data.fig);
    QVector<QLinkedList<QPoint>> split_list = form_lists(data.split);

    data.painter->setPen(QColor("black"));
    for (auto list : split_list) {
        QVector<QPoint> vec;
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
        QPolygon buffer(vec);
        data.painter->drawPolygon(buffer);
    }

    data.painter->setPen(QColor("blue"));
    for (auto list : figure_list) {
        QVector<QPoint> vec;
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
        QPolygon buffer(vec);
        data.painter->drawPolygon(buffer);
    }

    QLinkedList<QPoint> point_in;
    QLinkedList<QPoint> point_out;

    //вычисление точек пересечения и внесение их в списки
    fill_vectors(split_list, figure_list, point_in, point_out);

    data.painter->setPen("orange");
    for (auto p : point_in) {
        data.painter->drawEllipse(p, 3, 3);
    }
    data.painter->setPen("green");
    for (auto p : point_out) {
        data.painter->drawEllipse(p, 3, 3);
    }

    data.scene->addPixmap(*data.pixmap);
}

QVector<QLinkedList<QPoint>> form_lists(figure& f)
{
    QVector<QLinkedList<QPoint>> result;
    QLinkedList<QPoint> buffer;
    for (int i = 0; i < f.bounds.size(); ++i) {
        buffer.push_back(f.bounds[i]);
    }
    if (f.bounds.size()) {
        buffer.push_back(f.bounds[0]);
    }
    result.push_back(buffer);

    for (int i = 0; i < f.holes.size(); ++i) {
        buffer.clear();
        for (int j = 0; j < f.holes[i].size(); ++j) {
            buffer.push_back(f.holes[i][j]);
        }
        if (f.holes[i].size()) {
            buffer.push_back(f.holes[i][0]);
        }
        result.push_back(buffer);
    }

    return result;
}

//вычисление точки пересечения
bool crossing(QPoint& p1, QPoint& p2, QPoint& p3, QPoint& p4, QPoint& cross)
{
    //у вырожденных прямых не бывает пересечений
    if ((p2 == p1) || (p3 == p4)) {
        return false;
    }

    double s = 0;
    double t = 0;

    if (p2.y() != p1.y()) {
        double buf_1 = (p1.x() - p3.x()) + (p2.x() - p1.x()) * (p3.y() - p1.y()) / (double)(p2.y() - p1.y());
        double buf_2 = (p4.x() - p3.x()) + (p1.x() -  p2.x()) * (p4.y() - p3.y()) / (double)(p2.y() - p1.y());

        s = buf_1 / buf_2;
        t = ((p3.y() - p1.y()) + (p4.y() - p3.y()) * s) / (double)(p2.y() - p1.y());
    }
    else {
        if (p3.y() == p4.y()) {
            return false;
        }
        s = (p1.y() - p3.y()) / (double) (p4.y() - p3.y());

        double buf_1 = (p3.x() - p1.x()) + (p4.x() - p3.x()) * s;
        double buf_2 = (p2.x() - p1.x());

        t = buf_1 / buf_2;
    }

    if (t > 1e-3 && t < 1 - 1e-3 && s > 1e-3 && s < 1 - 1e-3) {
        cross.setX(p3.x() + (p4.x() - p3.x()) * s);
        cross.setY(p3.y() + (p4.y() - p3.y()) * s);

        return true;
    }

    return false;
}


void fill_vectors(QVector<QLinkedList<QPoint>>& split_list, QVector<QLinkedList<QPoint>>& figure_list,
                  QLinkedList<QPoint>& point_in, QLinkedList<QPoint>& point_out)
{
    for (QLinkedList<QPoint>& fig : figure_list) {
        for (QLinkedList<QPoint>& spl : split_list) {
            auto prev_fig = fig.begin();
            for (auto next_fig = prev_fig + 1; next_fig != fig.end(); ++next_fig, ++prev_fig) {
                QPoint p1 = *prev_fig;
                QPoint p2 = *next_fig;
                auto prev_spl = spl.begin();
                for (auto next_spl = prev_spl + 1; next_spl != spl.end(); ++next_spl, ++prev_spl) {
                    QPoint p3 = *prev_spl;
                    QPoint p4 = *next_spl;
                    QPoint cross;
                    //занесение точки в списки
                    if (crossing(p1, p2, p3, p4, cross)) {
                        //проверка векторным произведением
                        if ((p2.x() - p1.x()) * (p4.y() - p3.y()) - (p2.y() - p1.y()) * (p4.x() - p3.x()) > 0) {
                            point_in.push_back(cross);
                        }
                        else {
                            point_out.push_back(cross);
                        }
//                        fig.insert(prev_fig, cross);
                    }
                }

            }
        }
    }
}
