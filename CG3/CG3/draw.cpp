#include "draw.h"
#include "algorithms.h"
#include <cmath>
#include <iostream>

void draw(QGraphicsScene& scene, DrawData& data)
{
    switch (data.alg) {
    case CDA:
        draw_cda(scene, data);
        break;

    case Bres_int:
        draw_bres_int(scene, data);
        break;

    case Bres_float:
        draw_bres_float(scene, data);
        break;

    case Bres_step:
        draw_bres_step(scene, data);
        break;

    case Default:
        draw_default(scene, data);
        break;

    case Vu:
        draw_vu(scene, data);
        break;
    }
}


void draw_cda(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point draw_point;

    int x1 = round(start.x);
    int y1 = round(start.y);
    int x2 = round(end.x);
    int y2 = round(end.y);

    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);

    int length = deltax > deltay ? deltax : deltay;

    if (length == 0) {
        draw_point.x = x1;
        draw_point.y = y1;
        draw_pixel(scene, draw_point, data.pen);
        return;
    }

    double dx = (x2 - x1) / (double)length;
    double dy = (y2 - y1) / (double)length;

    double x = x1;
    double y = y1;

    length++;
    while (length--)
    {
        x += dx;
        y += dy;
        draw_point.x = round(x);
        draw_point.y = round(y);
        draw_pixel(scene, draw_point, data.pen);
    }

}

void draw_bres_int(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point draw_point;

    //get integer coordinates
    int x1 = round(start.x);
    int y1 = round(start.y);
    int x2 = round(end.x);
    int y2 = round(end.y);

    if (x1 == x2 && y1 == y2) {
        draw_pixel(scene, start, data.pen);
        return;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int sx = get_sign(dx);
    int sy = get_sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;

    if (dx < dy) {
        int t = dy;
        dy = dx;
        dx = t;
        swap = true;
    }

    int k = 2 * dy;
    int error = k - dx;

    int x = x1;
    int y = y1;

    for (int i = 1; i <= dx; ++i) {
        draw_point.x = x;
        draw_point.y = y;
        draw_pixel(scene, draw_point, data.pen);

        if (error >= 0) {
            if (!swap) {
                y += sy;
            }
            else {
                x += sx;
            }
            error -= 2 * dx;
        }
        if (error < 0) {
            if (!swap) {
                x += sx;
            }
            else {
                y += sy;
            }
        }
        error += k;
    }

}

void draw_bres_float(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point draw_point;

    //get integer coordinates
    int x1 = round(start.x);
    int y1 = round(start.y);
    int x2 = round(end.x);
    int y2 = round(end.y);

    if (x1 == x2 && y1 == y2) {
        draw_pixel(scene, start, data.pen);
        return;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int sx = get_sign(dx);
    int sy = get_sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;

    if (dx < dy) {
        int t = dy;
        dy = dx;
        dx = t;
        swap = true;
    }

    double k = (double) dy / (double)dx;
    double error = k - 0.5;

    int x = x1;
    int y = y1;

    for (int i = 1; i <= dx; ++i) {
        draw_point.x = x;
        draw_point.y = y;
        draw_pixel(scene, draw_point, data.pen);

        if (error >= 0) {
            if (!swap) {
                y += sy;
            }
            else {
                x += sx;
            }
            error -= 1;
        }
        if (error < 0) {
            if (!swap) {
                x += sx;
            }
            else {
                y += sy;
            }
        }
        error += k;
    }

}


void draw_bres_step(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;
    Point draw_point;
    QColor color = data.pen.color();

    //get integer coordinates
    int x1 = round(start.x);
    int y1 = round(start.y);
    int x2 = round(end.x);
    int y2 = round(end.y);

    if (x1 == x2 && y1 == y2) {
        draw_pixel(scene, start, data.pen);
        return;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int sx = get_sign(dx);
    int sy = get_sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    bool swap = false;

    if (dx < dy) {
        int t = dy;
        dy = dx;
        dx = t;
        swap = true;
    }

    int intencity = 255;

    int k = 2 * dy * intencity; //k = dy / dx * intencity;
    int error = intencity * dx; // error = intencity / 2;

    int w = intencity * 2 * dx - k; // w = intencity - k;

    int x = x1;
    int y = y1;

    for (int i = 1; i <= dx; ++i) {

        color.setAlpha(255 - error / dx / 2); // 255 - error
        data.pen.setColor(color);
        draw_point.x = x;
        draw_point.y = y;
        draw_pixel(scene, draw_point, data.pen);

        if (error > w) {
            x += sx;
            y += sy;
            error -= w;
        }
        else {
            if (swap) {
                y += sy;
            }
            else {
                x += sx;
            }
            error += k;
        }
    }

}


void draw_default(QGraphicsScene& scene, DrawData& data)
{
    Point start = data.start;
    Point end = data.end;

    QLine line(start.x, start.y, end.x, end.y);
    scene.addLine(line, data.pen);
}

void draw_vu(QGraphicsScene &scene, DrawData &data)
{
    Point start = data.start;
    Point end = data.end;
    QColor color = data.pen.color();
    Point draw_point;

    double x1 = start.x;
    double x2 = end.x;
    double y1 = start.y;
    double y2 = end.y;

    if (round(x1) == round(x2) && round(y1) == round(y2)) {
        draw_pixel(scene, start, data.pen);
        return;
    }

    if (fabs(x2 - x1) > fabs(y2 - y1)) {

        if (x2 < x1) {
            double buf = x1;
            x1 = x2;
            x2 = buf;
            buf = y1;
            y1 = y2;
            y2 = buf;
        }

        double dx = x2 - x1;
        double dy = y2 - y1;
        double gradient = dy / dx;

        double xend = round(x1);
        double yend = y1 + gradient * (xend - x1);
        double xgap = 1- fpart(x1  + 0.5);
        double xpxl1 = xend;
        double ypxl1 = ipart(yend);

        draw_point.x = xpxl1;
        draw_point.y = ypxl1;
        color.setAlpha(255 * (1 - fpart(yend) * xgap));
        data.pen.setColor(color);
        draw_pixel(scene, draw_point, data.pen);

        draw_point.y = ypxl1 + 1;
        color.setAlpha(255 * (fpart(yend * xgap)));
        data.pen.setColor(color);
        draw_pixel(scene, draw_point, data.pen);


        xend = round(x2);
        yend = y2 + gradient * (xend - x2);
        xgap = fpart(x2 + 0.5);
        double xpxl2 = xend;
        double ypxl2 = ipart(yend);
        draw_point.x = xpxl2;
        draw_point.y = ypxl2;
        color.setAlpha(255 * (1 - fpart(yend) * xgap));
        data.pen.setColor(color);
        draw_pixel(scene, draw_point, data.pen);
        color.setAlpha(255 * (fpart(yend * xgap)));
        data.pen.setColor(color);
        draw_point.y += 1;
        draw_pixel(scene, draw_point, data.pen);

        double intery = ypxl1 + gradient;

        for (int x = xpxl1 + 1; x < xpxl2; ++x) {
            draw_point.x = x;
            draw_point.y = ipart(intery);
            color.setAlpha(255 * (1 - fpart(intery)));
            data.pen.setColor(color);
            draw_pixel(scene, draw_point, data.pen);

            draw_point.y = ipart(intery) + 1;
            color.setAlpha(255 * fpart(intery));
            data.pen.setColor(color);
            draw_pixel(scene, draw_point, data.pen);
            intery += gradient;
        }
    }
    else {
        if (y2 < y1) {
            double buf = x1;
            x1 = x2;
            x2 = buf;
            buf = y1;
            y1 = y2;
            y2 = buf;
        }

        double dx = x2 - x1;
        double dy = y2 - y1;
        double gradient = dx / dy;

        double yend = round(y1);
        double xend = x1 + gradient * (yend - y1);
        double ygap = 1 - fpart(y1  + 0.5);
        double ypxl1 = yend;
        double xpxl1 = ipart(xend);

        draw_point.x = xpxl1;
        draw_point.y = ypxl1;
        color.setAlpha(255 * (1 - fpart(xend) * ygap));
        data.pen.setColor(color);
        draw_pixel(scene, draw_point, data.pen);

        draw_point.x = xpxl1 + 1;
        color.setAlpha(255 * (fpart(xend * ygap)));
        data.pen.setColor(color);
        draw_pixel(scene, draw_point, data.pen);


        yend = round(y2);
        xend = x2 + gradient * (yend - y2);
        ygap = fpart(y2 + 0.5);
        double ypxl2 = yend;
        double xpxl2 = ipart(xend);
        draw_point.y = ypxl2;
        draw_point.x = xpxl2;
        color.setAlpha(255 * (1 - fpart(xend) * ygap));
        data.pen.setColor(color);
        draw_pixel(scene, draw_point, data.pen);
        color.setAlpha(255 * (fpart(xend * ygap)));
        data.pen.setColor(color);
        draw_point.x += 1;
        draw_pixel(scene, draw_point, data.pen);

        double intery = xpxl1 + gradient;

        for (int y = ypxl1 + 1; y < ypxl2; ++y) {
            draw_point.y = y;
            draw_point.x = ipart(intery);
            color.setAlpha(255 * (1 - fpart(intery)));
            data.pen.setColor(color);
            draw_pixel(scene, draw_point, data.pen);

            draw_point.x = ipart(intery) + 1;
            color.setAlpha(255 * fpart(intery));
            data.pen.setColor(color);
            draw_pixel(scene, draw_point, data.pen);
            intery += gradient;
        }
    }
}
