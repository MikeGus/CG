#include "draw_circle.h"
#include "algorithms.h"
#include <cmath>
#include <iostream>

void draw_circle(QGraphicsScene& scene, DrawData& data)
{
    switch (data.alg) {
    case Default:
        draw_default_circle(scene, data);
        break;

    case MiddlePoint:
        draw_middle_point_circle(scene, data);
        break;

    case Canonic:
        draw_canonic_circle(scene, data);
        break;

    case Parametric:
        draw_parametric_circle(scene, data);
        break;

    case Bresenhnam:
        draw_bresenham_circle(scene, data);
        break;
    }
    scene.addPixmap((*data.map));
}

void draw_default_circle(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;

    double a = fabs(start.x - end.x);
    double b = fabs(start.y - end.y);

    data.painter->drawEllipse(data.start.x, data.start.y, a, -b);
}

void draw_middle_point_circle(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point center;

    int x1 = round(start.x);
    int x2 = round(end.x);

    int y1 = round(start.y);
    int y2 = round(end.y);

    center.x = (x1 + x2) / 2.0;
    center.y = (y1 + y2) / 2.0;

    double R = fabs(start.x - end.x) / 2.0;

    int p = (int) (1 - R);
    int x = 0;
    int y = R;

    draw_oct(scene, center, x, y, data);
    draw_oct(scene, center, y, x, data);

    while (x < y) {
        x++;
        if (p < 0) { // горизонтальный
            p += 2 * x + 1;
        }
        else {
            y -= 1;
            p += 2 * (x - y) + 1; // диагональный
        }

        draw_oct(scene, center, x, y, data);
        draw_oct(scene, center, y, x, data);
    }

}

void draw_canonic_circle(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point center;

    int x1 = round(start.x);
    int x2 = round(end.x);

    int y1 = round(start.y);
    int y2 = round(end.y);

    center.x = (x1 + x2) / 2.0;
    center.y = (y1 + y2) / 2.0;

    double R = fabs(start.x - end.x) / 2.0;
    int x = 0;
    int y = R;

    while (x <= y) {
        draw_oct(scene, center, x, y, data);
        draw_oct(scene, center, y, x, data);
        x++;
        y = (int) (sqrt(R * R - x * x) + 0.5);
    }
}

void draw_parametric_circle(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point center;

    int x1 = round(start.x);
    int x2 = round(end.x);

    int y1 = round(start.y);
    int y2 = round(end.y);

    center.x = (x1 + x2) / 2.0;
    center.y = (y1 + y2) / 2.0;

    double R = abs(x2 - x1) / 2.0;

    //Point draw_point;
    int length =  (int) (M_PI_2 * R + 0.5);

    for (int t = 0; t <= length; t++) {
        double angle = (t * M_PI_2 / length);
        draw_oct(scene, center, round(R * cos(angle)), round(R * sin(angle)), data);
    }
}

void draw_bresenham_circle(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point center;

    int x1 = round(start.x);
    int x2 = round(end.x);

    int y1 = round(start.y);
    int y2 = round(end.y);

    center.x = (x1 + x2) / 2.0;
    center.y = (y1 + y2) / 2.0;

    double R = fabs(start.x - end.x) / 2.0;
    int x = 0;
    int y = (int) (R  + 0.5);
    int d = (int) (2 - 2 * R); // разность расстояний от центра до окружности и до диагонального пикселя
    int b = 0;

    while (true) {
        draw_oct(scene, center, x, y, data);
        if (y <=0) {
            break;
        }//диагональный внутри окружности
        if (d < 0) {
            b = 2 * d + 2 * y - 1; // разность расстояний от центра до гор. и от центра до диаг.
            x++;
            if (b <= 0) {
                d += 2 * x + 2; //горизонтальный
            }
            else {
                y--;
                d += 2 * x - 2 * y + 2;//диагональный
            }
        } //диагональный вне окружности
        else if (d > 0) {
             b = 2 * d - 2 * x - 1;
             y--;
             if (b > 0) {
                 d += (-2) * y + 2;//вертикальный
             }
             else {
                 x++;
                 d += 2 * x - 2 * y + 2;//диагональный
             }
        }//диагональный на окружности
        else if (d == 0) {
            x++;
            y--;
            d += 2 * x - 2 * y + 2;//диагональный
        }
    }
}
