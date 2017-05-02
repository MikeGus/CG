#include "filling.h"
#include <QDebug>

void fill_image(QPoint& point, QGraphicsScene& scene, DrawData& data, bool timer)
{
    std::vector<QPoint> stack;
    stack.push_back(point);


    QPoint work_point;

    while (!stack.empty()) {

        work_point = stack[stack.size() - 1];
        stack.pop_back();
        data.painter->drawPoint(work_point);
        QImage img = data.image->toImage();

        int left = find_left_bound(work_point, img, *data.painter);
        int right = find_right_bound(work_point, img, *data.painter);

        if (timer) {
            scene.clear();
            scene.addPixmap(*data.image);
            QApplication::processEvents();
        }

        if (work_point.y() > 0) {
            fill_line(work_point.y() - 1, left, right, stack, img, *data.image, *data.painter, scene, timer);
        }
        if (work_point.y() < data.image->height()) {
            fill_line(work_point.y() + 1, left, right, stack, img, *data.image, *data.painter, scene, timer);
        }
    }
    scene.clear();
    scene.addPixmap(*data.image);
}

void fill_line(int y, int x1, int x2, std::vector<QPoint>& stack, QImage& img, QPixmap& map, QPainter& painter, QGraphicsScene& scene, bool timer)
{
    QColor bound_color("black");
    QColor work_color = painter.pen().color();

    int x = x1;
    while (x <= x2) {
        bool found_wrong_pixel = false;
        int k = 0;
        while ((img.pixelColor(x, y) != bound_color) && (img.pixelColor(x, y) != work_color) && (x < x2)) {
            painter.drawPoint(x, y);
            ++x;
            ++k;
            if (!found_wrong_pixel) {
                found_wrong_pixel = true;
            }
            if (timer && ((k % 20) == 0)) {
                scene.clear();
                scene.addPixmap(map);
                QApplication::processEvents();
            }
        }
        if (found_wrong_pixel) {
            if ((img.pixelColor(x, y) != bound_color) && (img.pixelColor(x, y) != work_color) && (x == x2)) {
                stack.push_back(QPoint(x, y));
            }
            else {
                stack.push_back(QPoint(x - 1, y));
            }
            found_wrong_pixel = false;
        }
        int xn = x;
        while (((img.pixelColor(x, y) == bound_color) || (img.pixelColor(x, y) == work_color)) && (x < x2)) {
            ++x;
        }
        if (xn == x) {
            ++x;
        }
    }

}

int find_left_bound(QPoint& point, QImage& img, QPainter& painter)
{
    int y = point.y();
    QColor bound_color("black");
    for (int x = point.x(); x >= 0; --x) {
        if (img.pixelColor(x, y) != bound_color) {
            painter.drawPoint(x, y);
        }
        else {
            return x + 1;
        }
    }
    return 0;
}

int find_right_bound(QPoint& point, QImage& img, QPainter& painter)
{
    int y = point.y();
    QColor bound_color("black");
    int right_bound = img.width() - 1;

    for (int x = point.x(); x <= right_bound; ++x) {
        if (img.pixelColor(x, y) != bound_color) {
            painter.drawPoint(x, y);
        }
        else {
            return x - 1;
        }
    }
    return right_bound;
}
