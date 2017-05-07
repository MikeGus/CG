#include "chop.h"
#include <QDebug>

void chop(Paintdata& data)
{
    QColor buffer = data.painter->pen().color();
    std::vector<line_info> line_data = form_info(data);
    size_t size = std::min(line_data.size(), data.lines.size());

    for (size_t i = 0; i < size; ++i) {
        QLine current_line(data.lines[i]);
        if (line_data[i].fully_visible()) {
            data.painter->setPen(QColor("red"));
            data.painter->drawLine(current_line);
        }
        else if (line_data[i].fully_invisible()) {
            data.painter->setPen(QColor("blue"));
            data.painter->drawLine(current_line);
        }
        else {
            QPoint working;
            std::vector<QPoint> result;
            QPoint cross;
            bool crossed  = true;
            double tg = 1e30;

            if (current_line.dx() != 0) {
                tg =  (double) current_line.dy() / current_line.dx();
            }

            for (int step = 1; step < 3; ++step) {
                if (step == 1) {
                    if (line_data[i].p1 == ZERO) { //если первая точка внутри - заносим ее в результат
                        result.push_back(current_line.p1());
                        working = current_line.p2(); //рабочая точка - вторая
                        step = 3;
                    }
                    else {
                        if (line_data[i].p2 == ZERO) { //если вторая точка внутри - заносим ее в результат
                            result.push_back(current_line.p2());
                            step = 3;
                        }
                        working = current_line.p1(); //рабочая точка - первая
                    }
                }
                else {
                    working = current_line.p2(); //рабочая точка - вторая
                }
                if (current_line.dx() != 0) { //если линия не вертикальна
                    if (!(working.x() > data.rectangle.left())) { //пересечение с левой границей
                        cross.setY(tg * (data.rectangle.left() - working.x()) + working.y());
                        if (cross.y() < data.rectangle.top() && cross.y() > data.rectangle.bottom()) {
                            cross.setX(data.rectangle.left());
                            result.push_back(cross);
                            continue;
                        }
                    }
                    else if (!(working.x() < data.rectangle.right())) { //пересечение с правой границей
                        cross.setY(tg * (data.rectangle.right() - working.x()) + working.y());
                        if (cross.y() < data.rectangle.top() && cross.y() > data.rectangle.bottom()) {
                            cross.setX(data.rectangle.right());
                            result.push_back(cross);
                            continue;
                        }
                    }
                }
                //нет пересечений с левой и правой границей
                if (tg != 0) {
                    if (working.y() >= data.rectangle.top()) {//пересечение с верхней границей
                        cross.setX((data.rectangle.top() - working.y()) / tg + working.x());
                        if (cross.x() > data.rectangle.left() && cross.x() < data.rectangle.right()) {
                            cross.setY(data.rectangle.top());
                            result.push_back(cross);
                            continue;
                        }
                    }
                    else if (working.y() <= data.rectangle.bottom()) { //пересечение с нижней границей
                        cross.setX((data.rectangle.bottom() - working.y()) / tg + working.x());
                        if (cross.x() > data.rectangle.left() && cross.x() < data.rectangle.right()) {
                            cross.setY(data.rectangle.bottom());
                            result.push_back(cross);
                            continue;
                        }
                    }
                    else {
                        crossed = false;
                        break;
                    }
                }

            }
            if (crossed && result.size() >= 2) { //линия пересекла окно
                QLine line(result[0], result[1]);
                line_info info(line, data.rectangle);
                if (info.fully_visible()) {
                    data.painter->setPen(QColor("red"));
                    data.painter->drawLine(line);

                    data.painter->setPen(QColor("blue"));

                    if (current_line.dx() != 0) {
                        if ((current_line.x1() < current_line.x2() && line.x1() < line.x2()) ||
                               (current_line.x1() > current_line.x2() && line.x1() > line.x2() )){
                            if (current_line.p1() != line.p1()) {
                                data.painter->drawLine(current_line.p1(), line.p1());
                            }
                            if (current_line.p2() != line.p2()) {
                                data.painter->drawLine(current_line.p2(), line.p2());
                            }
                        }
                        else {
                            if (current_line.p1() != line.p2()) {
                                data.painter->drawLine(current_line.p1(), line.p2());
                            }
                            if (current_line.p2() != line.p1()) {
                                data.painter->drawLine(current_line.p2(), line.p1());
                            }
                        }
                    }
                    else {
                        if ((current_line.y1() < current_line.y2() && line.y1() < line.y2()) ||
                                (current_line.y1() > current_line.y2() && line.y1() > line.y2())) {
                            if (current_line.p1() != line.p1()) {
                                data.painter->drawLine(current_line.p1(), line.p1());
                            }
                            if (current_line.p2() != line.p2()) {
                                data.painter->drawLine(current_line.p2(), line.p2());
                            }
                        }
                        else {
                            if (current_line.p1() != line.p2()) {
                                data.painter->drawLine(current_line.p1(), line.p2());
                            }
                            if (current_line.p2() != line.p1()) {
                                data.painter->drawLine(current_line.p2(), line.p1());
                            }
                        }
                    }
                }
                else {
                    data.painter->setPen(QColor("blue"));
                    data.painter->drawLine(line);
                }
            }
            else { //линия не пересекла окно
                data.painter->setPen(QColor("blue"));
                data.painter->drawLine(current_line);
            }
        }
    }
    data.painter->setPen(buffer);
}

std::vector<line_info> form_info(Paintdata& data)
{
    std::vector<line_info> result;

    for (QLine& line : data.lines) {
        line_info buffer(line, data.rectangle);
        result.push_back(buffer);
    }

    return result;
}
