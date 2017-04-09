#include "draw.h"
#include "algorithms.h"
#include <cmath>
#include <iostream>


void draw(QGraphicsScene& scene, DrawData& data)
{
    switch (data.alg) {
    case Default:
        draw_default(scene, data);
        break;

    case MiddlePoint:
        draw_middle_point(scene, data);
        break;

    case Canonic:
        draw_canonic(scene, data);
        break;

    case Parametric:
        draw_parametric(scene, data);
        break;

    case Bresenhnam:
        draw_bresenham(scene, data);
        break;
    }
}

void draw_default(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;

    double a = fabs(start.x - end.x);
    double b = fabs(start.y - end.y);

    scene.addEllipse(data.start.x, data.start.y, a, -b, data.pen);
}

void draw_middle_point(QGraphicsScene& scene, DrawData& data)
{

}

void draw_canonic(QGraphicsScene& scene, DrawData& data)
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

    double a = fabs(start.x - end.x) / 2.0;
    double b = fabs(start.y - end.y) / 2.0;

    if (a >= b) {
        double k = b / a;
        double y = b;
        int x  = 0;
        for (x = 0; k * x <= y; ++x) {
            y = (1 - ((x * (double)x) / (a * a))) * b * b;
            y = sqrt(y);
            draw_oct(scene, center, x, y, data);
        }
        for (; x >= 0; --y) {
            x = (1 - ((y * (double)y) / (b * b))) * a * a;
            x = sqrt(x);
            draw_oct(scene, center, x, y, data);
        }
    }
    else {
        double k = a / b;
        double x = a;
        int y  = 0;
        for (y = 0; k * y <= x; ++y) {
            x = (1 - ((y * (double)y) / (b * b))) * a * a;
            x = sqrt(x);
            draw_oct(scene, center, x, y, data);
        }
        for (; y >= 0; --x) {
            y = (1 - ((x * (double)x) / (a * a))) * b * b;
            y = sqrt(y);
            draw_oct(scene, center, x, y, data);
        }
    }
}

void draw_parametric(QGraphicsScene& scene, DrawData& data)
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

    double a = fabs(start.x - end.x) / 2.0;
    double b = fabs(start.y - end.y) / 2.0;

    int length =  (int) (M_PI_2 * (a + b) + 0.5);

    for (int t = 0; t <= length; t++) {
        double angle = t * M_PI_2 / length;
        draw_oct(scene, center, round(a * cos(angle)), round(b * sin(angle)), data);
    }
}

void draw_bresenham(QGraphicsScene& scene, DrawData& data)
{

}
