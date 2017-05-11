#include "split.h"

double range(QPoint& p1, QPoint& p2)
{
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();
    return sqrt(dx * dx + dy * dy);
}


void split(Paintdata& data)
{
    //формирование связных списков вершин отсекателя и многоугольника
    QVector<QLinkedList<QPoint>> figure_list = form_lists(data.fig);
    QVector<QLinkedList<QPoint>> split_list = form_lists(data.split);

    //отрисовка разделителя
    data.painter->setPen(QColor("black"));
    for (auto list : split_list) {
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

//    for (auto& list : figure_list) {
//        insert_crossing(list, point_in, point_out);
//    }

//    for (auto& list : split_list) {
//        insert_crossing(list, point_in, point_out);
//    }

//    //просмотр ребер и закраска
//    for (auto& list : figure_list) {
//        data.painter->setPen("blue");
//        bool is_in = false;
//        for (auto& p : list) {
//            if (in_list(point_in, p)) {
//                break;
//            }
//            if (in_list(point_out, p)) {
//                data.painter->setPen("red");
//                is_in = true;
//                break;
//            }
//        }
//        auto it_first = list.begin();
//        for (auto it_second = it_first + 1; it_second != list.end(); ++it_second, ++it_first) {
//            data.painter->drawLine(*it_first, *it_second);
//            if (!is_in) {
//                if (in_list(point_in, *it_second)) {
//                    is_in = true;
//                    data.painter->setPen("red");
//                }
//            }
//            else {
//                if (in_list(point_out, *it_second)) {
//                    is_in = false;
//                    data.painter->setPen("blue");
//                }
//            }
//        }
//    }

    data.painter->setPen(QColor("blue"));
    for (auto list : figure_list) {
        QVector<QPoint> vec;
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
        QPolygon buffer(vec);
        data.painter->drawPolygon(buffer);
    }

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
        int buf_1 = (p1.x() - p3.x()) * (p2.y() - p1.y()) + (p2.x() - p1.x()) * (p3.y() - p1.y());
        int buf_2 = (p4.x() - p3.x()) * (p2.y() - p1.y()) + (p1.x() -  p2.x()) * (p4.y() - p3.y());

        s = buf_1 / (double) buf_2;
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

    if (t >= 0 && t <= 1 && s >= 0 && s <= 1) {
        int x = p3.x() + (p4.x() - p3.x()) * s + 0.5;
        int y = p3.y() + (p4.y() - p3.y()) * s + 0.5;
        cross.setX(x);
        cross.setY(y);
        return true;
    }

    return false;
}


void fill_vectors(QVector<QLinkedList<QPoint>>& split_list, QVector<QLinkedList<QPoint>>& figure_list,
                  QLinkedList<QPoint>& point_in, QLinkedList<QPoint>& point_out)
{
    //проходимся по всем фигурам
    for (QLinkedList<QPoint>& fig : figure_list) {
        //по всем разделителям
        for (QLinkedList<QPoint>& spl : split_list) {
            auto prev_fig = fig.begin();
            //смотрим все ребра фигуры
            for (auto next_fig = prev_fig + 1; next_fig != fig.end(); ++prev_fig, ++next_fig) {
                QPoint p1 = *prev_fig;
                QPoint p2 = *next_fig;
                auto prev_spl = spl.begin();
                //смотрим все ребра отсекателя
                for (auto next_spl = prev_spl + 1; next_spl != spl.end(); ++next_spl, ++prev_spl) {
                    QPoint p3 = *prev_spl;
                    QPoint p4 = *next_spl;
                    QPoint cross;
                    //занесение точек пересечения в списки
                    if (crossing(p1, p2, p3, p4, cross)) {
                        //проверка векторным произведением
                        if ((p2.x() - p1.x()) * (p4.y() - p3.y()) - (p2.y() - p1.y()) * (p4.x() - p3.x()) > 0) {
                            point_in.push_back(cross);
                        }
                        else {
                            point_out.push_back(cross);
                        }
                    }
                }
            }
        }
    }
}

bool in_line(QPoint& p1, QPoint& p2, QPoint& p)
{
    if (p1.x() != p2.x()) {
        double t = (double) (p.x() - p2.x()) / (p1.x() - p2.x());
        if (t >= 0 && t <=1) {
            int y = t * p1.y() +  p2.y() - p2.y() * t + 0.5;
            if (abs(y - p.y()) < 2) {
                return true;
            }
        }
    }
    else {
        if ((p.x() - p1.x() < 2) && (p1.y() <= p.y()) && (p.y() <= p2.y())) {
            return true;
        }
    }
    return false;
}

bool in_list(QLinkedList<QPoint>& list, QPoint& p)
{
    for (auto& p1 : list) {
        if (p1 == p) {
            return true;
        }
    }
    return false;
}

void insert_crossing(QLinkedList<QPoint>& list, QLinkedList<QPoint>& in, QLinkedList<QPoint>& out)
{
    for (auto iter = in.begin(); iter != in.end(); ++iter) {
        auto iter_1 = list.begin();
        for (auto iter_2 = iter_1 + 1; iter_2 != list.end(); ++iter_1, ++iter_2) {
            if (in_line(*iter_1, *iter_2, *iter)) {
                list.insert(iter_2, *iter);
                qDebug() << "in";
                break;
            }
        }
    }
    for (auto iter = out.begin(); iter != out.end(); ++iter) {
        auto iter_1 = list.begin();
        for (auto iter_2 = iter_1 + 1; iter_2 != list.end(); ++iter_1, ++iter_2) {
            if (in_line(*iter_1, *iter_2, *iter)) {
                list.insert(iter_2, *iter);
                qDebug() << "out";
                break;
            }
        }
    }
}
