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

    QLinkedList<QPoint> point_in;
    QLinkedList<QPoint> point_out;

    //вычисление точек пересечения и внесение их в списки
    fill_vectors(split_list, figure_list, point_in, point_out);


    //просмотр ребер и закраска
    for (auto& list : figure_list) {
        int visible = check_visibility(list, split_list, point_in, point_out);
        if ((*split_list.begin()).size() == 0) {
            visible = -1;
        }

        if (visible < 0) {
            data.painter->setPen("blue");
            auto it_1(list.begin());
            for (auto it_2 = it_1 + 1; it_2 != list.end(); ++it_1, ++it_2) {
                data.painter->drawLine(*it_1, *it_2);
            }
            continue;
        }
        else if (visible > 0) {
            data.painter->setPen("red");
            auto it_1(list.begin());
            for (auto it_2 = it_1 + 1; it_2 != list.end(); ++it_1, ++it_2) {
                data.painter->drawLine(*it_1, *it_2);
            }
            continue;
        }

        data.painter->setPen("blue");
        bool is_in = false;
        for (auto& p : list) {
            if (in_list(point_in, p)) {
                break;
            }
            if (in_list(point_out, p)) {
                data.painter->setPen("red");
                is_in = true;
                break;
            }
        }
        auto it_first = list.begin();
        for (auto it_second = it_first + 1; it_second != list.end(); ++it_second, ++it_first) {
            data.painter->drawLine(*it_first, *it_second);
            if (!is_in) {
                if (in_list(point_in, *it_second)) {
                    is_in = true;
                    data.painter->setPen("red");
                }
            }
            else {
                if (in_list(point_out, *it_second)) {
                    is_in = false;
                    data.painter->setPen("blue");
                }
            }
        }
    }

    //просмотр ребер и закраска
    for (auto& list : split_list) {

        int visible = check_visibility(list, figure_list, point_in, point_out);
        if ((*figure_list.begin()).size() == 0) {
            visible = -1;
        }
        if (visible < 0) {
            data.painter->setPen("black");
            auto it_1(list.begin());
            for (auto it_2 = it_1 + 1; it_2 != list.end(); ++it_1, ++it_2) {
                data.painter->drawLine(*it_1, *it_2);
            }
            continue;
        }
        else if (visible > 0) {
            data.painter->setPen("red");
            auto it_1(list.begin());
            for (auto it_2 = it_1 + 1; it_2 != list.end(); ++it_1, ++it_2) {
                data.painter->drawLine(*it_1, *it_2);
            }
            continue;
        }


        data.painter->setPen("black");
        bool is_in = false;
        for (auto& p : list) {
            if (in_list(point_in, p)) {
                data.painter->setPen("red");
                break;
            }
            if (in_list(point_out, p)) {
                is_in = true;
                break;
            }
        }
        auto it_first = list.begin();
        for (auto it_second = it_first + 1; it_second != list.end(); ++it_second, ++it_first) {
            data.painter->drawLine(*it_first, *it_second);
            if (!is_in) {
                if (in_list(point_in, *it_second)) {
                    is_in = true;
                    data.painter->setPen("black");
                }
            }
            else {
                if (in_list(point_out, *it_second)) {
                    is_in = false;
                    data.painter->setPen("red");
                }
            }
        }
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
            QVector<Trio> cr_vec;
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
                        Trio buffer_trio(cross, next_fig, next_spl);
                        cr_vec.push_back(buffer_trio);
                    }
                }
            }
            insert_crossing(spl, fig, cr_vec);
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

//сортировка точек по удалению от cmp
void sort_p(QVector<QPoint>& vec, QPoint& cmp)
{
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = i + 1; j < vec.size(); ++j) {
            int r1 = (vec[i].x() - cmp.x()) * (vec[i].x() - cmp.x()) + (vec[i].y() - cmp.y()) * (vec[i].y() - cmp.y());
            int r2 = (vec[j].x() - cmp.x()) * (vec[j].x() - cmp.x()) + (vec[j].y() - cmp.y()) * (vec[j].y() - cmp.y());
            if (r2 > r1) {
                QPoint buf(vec[i]);
                vec[i] = vec[j];
                vec[j] = buf;
            }
        }
    }
}

//корректная вставка точек пересечения многоугольников
void insert_crossing(QLinkedList<QPoint>& list_spl, QLinkedList<QPoint>& list_fig, QVector<Trio>& trio)
{
    QVector<QLinkedList<QPoint>::iterator> vec_spl;
    QVector<QLinkedList<QPoint>::iterator> vec_fig;

    for (Trio& data : trio) {
        if (vec_spl.indexOf(data.spl) == -1) {
            vec_spl.push_back(data.spl);
        }
        if (vec_fig.indexOf(data.fig) == -1) {
            vec_fig.push_back(data.fig);
        }
    }

    for (QLinkedList<QPoint>::iterator& p : vec_fig) {
        QVector<QPoint> insert_p;
        for (Trio& data : trio) {
            if (data.fig == p) {
                insert_p.push_back(data.p);
            }
        }
        sort_p(insert_p, *p);

        for (QPoint& point : insert_p) {
            list_fig.insert(p, point);
        }
    }

    for (QLinkedList<QPoint>::iterator& p : vec_spl) {
        QVector<QPoint> insert_p;
        for (Trio& data : trio) {
            if (data.spl == p) {
                insert_p.push_back(data.p);
            }
        }
        sort_p(insert_p, *p);

        for (QPoint& point : insert_p) {
            list_spl.insert(p, point);
        }
    }
}

QPoint norm(QPoint& p1, QPoint& p2)
{
    QPoint result;
    result.setX(p1.y() - p2.y());
    result.setY(p2.x() - p1.x());

    return result;
}

int scalar(QPoint& vec_1, QPoint& vec_2)
{
    return vec_1.x() * vec_2.x() + vec_1.y() * vec_2.y();
}

//0 - cross, 1 - visible, -1 - invisible
int check_visibility(QLinkedList<QPoint>& list_1, QVector<QLinkedList<QPoint>>& list_of_list_2, QLinkedList<QPoint>& list_in,\
                     QLinkedList<QPoint>& list_out)
{
    for (auto& point : list_1) {
        if ((in_list(list_in, point)) || (in_list(list_out, point))) {
            return 0;
        }
    }

    QPoint p1(*list_1.begin());
    QPoint p2(p1);
    p2.setY(0);

    QPoint b;

    auto list_2 = *list_of_list_2.begin();
    auto it_1 = list_2.begin();
    unsigned cross = 0;
    for (auto it_2 = it_1 + 1; it_2 != list_2.end(); ++it_1, ++it_2) {
//        QPoint n(norm(*it_1, *it_2));
//        QPoint v(p1.x() - (*it_1).x(), p1.y() - (*it_1).y());
//        if (scalar(n, v) > 0) {
//            return -1;
//        }
        if (crossing(p1, p2, *it_1, *it_2, b)) {
            if (b!= p2) {
                cross++;
            }
        }
    }

    if (cross % 2 == 0) {
        return -1;
    }

    bool found = false;
    for (auto it = list_of_list_2.begin() + 1; it != list_of_list_2.end(); ++it) {
        found = false;
        list_2 = *it;
        auto it_1 = list_2.rbegin();
        cross = 0;
        for (auto it_2 = it_1 + 1; it_2 != list_2.rend(); ++it_1, ++it_2) {
            if (crossing(p1, p2, *it_1, *it_2, b)) {
                cross++;
            }
        }
        if (cross % 2 != 0) {
            return -1;
        }
    }

    return 1;
}
