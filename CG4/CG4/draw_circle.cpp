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
}

void draw_default_circle(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;

    double a = fabs(start.x - end.x);
    double b = fabs(start.y - end.y);

    scene.addEllipse(data.start.x, data.start.y, a, -b, data.pen);
}

void draw_middle_point_circle(QGraphicsScene& scene, DrawData& data)
{

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

    int y = R;
    int x = 0;
    for (x = 0; x <= y; ++x) {
        y = sqrt(R * R - x * x);
        draw_oct(scene, center, x, y, data);
    }
    for (; x >= 0; --y) {
        x = sqrt(R * R - y * y);
        draw_oct(scene, center, x, y, data);
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

}
