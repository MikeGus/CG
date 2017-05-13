#include "chop.h"

void chop(Paintdata& data)
{
    data.painter->setPen(QColor("blue"));
    for (auto& line: data.lines) {
        data.painter->drawLine(line);
    }


}

//вектор нормали
QPoint norm(QLine &line)
{
    QPoint p(-line.dy(), line.dx());
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

double get_t(QLine& line, QLine& edge)
{
   QPoint normal = norm(edge);
   QLine check_line(edge.p1(), line.p2());

   QPoint check_vector(vector(check_line));
   QPoint line_vector(vector(line));

   int top = - scalar(normal, check_vector);
   int bottom = scalar(normal, line_vector);

   return ((double) top) / bottom;
}

