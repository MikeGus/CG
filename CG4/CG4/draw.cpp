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

    double a2 = a * a;
    double b2 = b * b;

    int p = 0;
    int x = 0;
    int y = b;
    double px = 0;
    double py = 2 * a2 * b;

    draw_oct(scene, center, x, y, data);

    // first area
    p = (int)(b2 - (a2 * b) + (a / 4) + 0.5);
    while(px <= py) {
        x++;
        px += 2 * b2;
        if (p < 0) {
            p += b2 + px;
        }
        else {
            y--;
            py -= 2 * a2;
            p += b2 + px - py;
        }
        draw_oct(scene, center, x, y, data);
    }

    // second area
    p = (int)(b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2 + 0.5);
    while(y >= 0) {
        y--;
        py -= 2 * a2;
        if (p > 0) {
            p += a2 - py;
        }
        else {
            x++;
            px += 2 * b2;
            p += a2 - py + px;
        }
        draw_oct(scene, center, x, y, data);
    }
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

    double xm = a * a / sqrt(a * a + b * b);
    int x = 0;
    int y = b;

    double a2 = a * a;
    double b2 = b * b;
    double r2 = a2 * b2;

    while (x < xm) {
        draw_oct(scene, center, x, y, data);
        x++;
        y = (int)(sqrt(r2 - b2 * x * x) / a + 0.5);
    }
    while (y >= 0) {
        draw_oct(scene, center, x, y, data);
        y--;
        x = (int)(sqrt(r2 - a2 * y * y) / b + 0.5);
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

    double t = 0;
    double dt = 1 / std::max(a, b);
    while (t <= M_PI_2) {
        int x = (int) (a * cos(t) + 0.5);
        int y = (int) (b * sin(t) + 0.5);
        draw_oct(scene, center, x, y, data);
        t += dt;
    }
}

void draw_bresenham(QGraphicsScene& scene, DrawData& data)
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

    int x = 0;
    int y = b;
    double a2 = a * a;
    double b2 = b * b;
    double d = b2 + a2 - 2 * b * a2;

    double beta = 0;
    while (y >= 0) {
        draw_oct(scene, center, x, y, data);
        if (d < 0) { // out of ellipse
            beta = 2 * d + 2 * a2 * y - a2;
            if (beta <= 0) {
                x++;
                d += 2 * b2 * x + b2;
            }
            else {
                x++;
                y--;
                d += 2 * b2 * x - 2 * a2 * y + a2 + b2;
            }
        }
        else if (d > 0) { // inside ellipse
            beta = 2 * d - 2 * b2 * x - b2;
            if (beta > 0) {
                y--;
                d -= 2 * a2 * y - a2;
            }
            else  {
                x++;
                y--;
                d += 2 * b2 * x - 2 * a2 * y + a2 + b2;
            }
        }
        else if (d == 0) { // on ellipse
            x++;
            y--;
            d += 2 * b2 * x - 2 * a2 * y + a2 + b2;
        }
    }
}
