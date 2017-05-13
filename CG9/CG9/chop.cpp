#include "chop.h"

void chop(Paintdata& data)
{
//    data.painter->setPen(QColor("blue"));
//    for (auto& line: data.lines) {
//        data.painter->drawLine(line);
//    }

    for (auto& line: data.lines) {
        chop_line(data.splitter, line, data);
    }

    data.scene->clear();
    data.scene->addPixmap(*data.pixmap);

}

//вектор нормали
QPoint norm(QLine &line)
{
    QPoint p(line.dy(), -line.dx());
    return p;
}

//направляющий вектор
QPoint vector(QLine &line)
{
    QPoint p(line.dx(), line.dy());
    return p;
}


int scalar(QPoint& vector_1, QPoint& vector_2)
{
    return vector_1.x() * vector_2.x() + vector_1.y() * vector_2.y();
}


//<0 - снаружи, 0 - на границе, >0 - внутри
int get_side(QPoint& point, QLine& edge)
{
    QPoint normal = norm(edge);
    QLine line(edge.p1(), point);

    QPoint vec = vector(line);

    return scalar(normal, vec);
}

double get_t(int Qi, int Pi)
{
   return -((double)Qi / Pi);
}


void chop_line(QVector<QPoint>& splitter, QLine& line, Paintdata& data)
{
    splitter.push_back(*splitter.begin());

    QPoint vector_line = vector(line); // вектор, определяющие направление отрезка

    double t0 = 0; //начало и конец отсекаемого отрезка
    double t1 = 1;

//    bool inside = false;

    // цикл по всем ребрам отрезка
    auto it_first = splitter.begin();
    for (auto it_second = it_first + 1; it_second != splitter.end(); ++it_second, ++it_first) {
        QLine edge(*it_first, *it_second); // ребро
        QLine check_line(edge.p1(), line.p1());

        QPoint check_vec = vector(check_line);
        QPoint normal = norm(edge); // внутренняя нормаль к ребру

        int Qi = scalar(check_vec, normal); // скалярное произведения вектора из начала ребра в начало отрезка и нормали
        int Pi = scalar(vector_line, normal); // скалярное произведение вектора отрезка и нормали

        //если отрезок не параллелен ребру
        if (Pi != 0) {
            double t = get_t(Qi, Pi);
            if (Pi < 0) { // прямая идет изнутри наружу
                if (t < t1) {
                    t1 = t;
                }
            }
            else { // прямая идет внутрь снаружи
                if (t > t0) {
                    t0 = t;
                }
            }
        }
        else {
            //если отрезок параллелен ребру и за границами окна
            if (Qi < 0) {
                data.painter->setPen("blue");
                data.painter->drawLine(line);
                return;
            }
            //иначе продолжаем поиск
        }
    }

    data.painter->setPen("blue");
    if (t1 < t0) {
        data.painter->drawLine(line);
    }
    else {
        QPoint start(line.p1().x() + t0 * line.dx() + 0.5, line.p1().y() + t0 * line.dy() + 0.5);
        QPoint end(line.p1().x() + t1 * line.dx() + 0.5, line.p1().y() + t1 * line.dy() + 0.5);

        data.painter->drawLine(line.p1(), start);
        data.painter->drawLine(end, line.p2());

        data.painter->setPen(QColor("red"));
        data.painter->drawLine(start, end);
    }

    splitter.pop_back();
}
