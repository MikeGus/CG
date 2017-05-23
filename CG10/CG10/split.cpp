#include "split.h"

double range(QPoint& p1, QPoint& p2)
{
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();
    return sqrt(dx * dx + dy * dy);
}


void split(Paintdata& data)
{
    QVector<QPoint> clipper(data.split.bounds);
    bool correct = true;

    if (!clipper.empty()) {
        clipper.push_back(*clipper.begin());
        correct = invert(clipper);
    }

    QVector<QPoint> output_list(data.fig.bounds);

    if (clipper.empty() || output_list.empty() || !correct) {
        if (!clipper.empty()) {
            data.painter->setPen(QColor("black"));
            data.painter->drawPolygon(clipper);
        }
        if (!output_list.empty()) {
            data.painter->setPen(QColor("blue"));
            data.painter->drawPolygon(output_list);
        }
        return;
    }

    if (!output_list.empty()) {
        data.painter->setPen(QColor("blue"));
        data.painter->drawPolygon(output_list);
    }

    auto it_1 = clipper.begin();
    //цикл по всем ребрам
    for (auto it_2 = it_1 + 1; it_2 != clipper.end(); ++it_1, ++it_2) {
        QLine edge(*it_1, *it_2);
        QVector<QPoint> input_list(output_list);
        output_list.clear();

        //сначала берем за точку S - заключительную
        QPoint S(*input_list.rbegin());
        //за точку E берем все точки по порядку
        for (QPoint& E : input_list) {
            QPoint cross;
            if (crossing(S, E, *it_1, *it_2, cross)) {
                //если E внутри полуплоскости
                if (inside_edge(E, edge)) {
                    //если S не внутри полуплоскости
                    //заносим в список точку пересечения ребер
                    if (!inside_edge(S, edge)) {
                        output_list.push_back(cross);
                    }
                    //точно заносим точку E
                    output_list.push_back(E);
                }
                //если E снаружи, а S - внутри
                //S уже занесен на предыдущем шаге,
                //заносим точку пересечения
                else if (inside_edge(S, edge)) {
                    output_list.push_back(cross);
                }
                //смещаем S
                S = E;
            }
        }
    }

    data.painter->setPen(QColor("black"));
    data.painter->drawPolygon(clipper);

    data.painter->setPen(QColor("red"));
    data.painter->drawPolygon(output_list);

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

    int x = p3.x() + (p4.x() - p3.x()) * s + 0.5;
    int y = p3.y() + (p4.y() - p3.y()) * s + 0.5;
    cross.setX(x);
    cross.setY(y);

    return true;
}

QPoint norm(QPoint& p1, QPoint& p2)
{
    QPoint result;
    result.setX(p1.y() - p2.y());
    result.setY(p2.x() - p1.x());

    return result;
}

QPoint norm(QLine& vec)
{
    QPoint result(-vec.dy(), vec.dx());
    return result;
}

int scalar(QPoint& vec_1, QPoint& vec_2)
{
    return vec_1.x() * vec_2.x() + vec_1.y() * vec_2.y();
}

bool invert(QVector<QPoint>& splitter)
{
    QPoint start(*splitter.begin());
    QPoint start_2(*(splitter.begin() + 1));
    QLine l(start, start_2);

    QPoint previous_norm(norm(l));

    auto it_1 = splitter.begin() + 1;
    int correct = 0;
    for (auto it_2 = it_1 + 1; it_2 != splitter.end(); ++it_2) {
        QLine line(*it_1, *it_2);
        QPoint line_dir(line.dx(), line.dy());

        if (scalar(line_dir, previous_norm) >= 0) {
            if (correct != -1) {
                correct = 1;
            }
            else {
                return false;
            }

        }
        else {
            if (correct != 1) {
                correct = -1;
            }
            else {
                return false;
            }
        }

        previous_norm = norm(line);
    }

    if (correct == -1) {
        QVector<QPoint> buffer;
        for (auto it = splitter.rbegin(); it != splitter.rend(); ++it) {
            buffer.push_back(*it);
        }
        splitter = buffer;
    }

    return true;
}

bool inside_edge(QPoint& S, QLine& edge)
{
    QPoint normal(norm(edge));

    QLine check_line(edge.p1(), S);
    QPoint vector(check_line.dx(), check_line.dy());

    return scalar(normal, vector) >= 0;
}
