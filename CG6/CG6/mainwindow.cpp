#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColorDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
    ui->radioArea->setChecked(true);
    //data.painter->setPen(QColor("blue"));
}

void MainWindow::showEvent(QShowEvent *event) {

    scene = new QGraphicsScene(ui->graphicsView->viewport()->geometry(), ui->graphicsView);
    ui->graphicsView->setScene(scene);

    data.image = new QPixmap(scene->width(), scene->height());
    data.image->fill();

    data.painter = new QPainter(data.image);

    scene->addPixmap(*data.image);
}

MainWindow::~MainWindow()
{
    delete data.painter;
    delete data.image;
    delete scene;
    delete ui;
}



void MainWindow::on_btnClear_clicked()
{
    data.image->fill();
    scene->clear();
    scene->addPixmap(*data.image);
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        QPoint point = ui->graphicsView->mapFromParent(e->pos());
        point.setY(point.y() - 13);
        if (ui->radioPoint->isChecked()) {
            bool timer = ui->checkDelay->isChecked();
            if (data.painter->pen().color() == QColor("black")) {
                data.painter->setPen(QColor("blue"));
            }
            fill_image(point, *scene, data, timer);
        }
        else if (ui->radioArea->isChecked()) {

            QColor bufcolor = data.painter->pen().color();
            data.painter->setPen(QColor("black"));

            draw_pixel(point, *data.painter);
            scene->clear();
            scene->addPixmap(*data.image);

            data.painter->setPen(QColor(bufcolor));
            data.lastpoint = point;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (ui->radioArea->isChecked() && (e->buttons() & Qt::LeftButton)) {
        QPoint point = ui->graphicsView->mapFromParent(e->pos());
        point.setY(point.y() - 13);

        QColor bufcolor = data.painter->pen().color();
        data.painter->setPen(QColor("black"));

        draw_line(point, data.lastpoint, *data.painter);
        data.lastpoint = point;

        scene->clear();
        scene->addPixmap(*data.image);

        data.painter->setPen(QColor(bufcolor));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (ui->radioArea->isChecked()) {
        QPoint point = ui->graphicsView->mapFromParent(e->pos());
        point.setY(point.y() - 13);

        QColor bufcolor = data.painter->pen().color();
        data.painter->setPen(QColor("black"));

        draw_line(point, data.lastpoint, *data.painter);
        scene->clear();
        scene->addPixmap(*data.image);

        data.painter->setPen(QColor(bufcolor));
    }
}

void MainWindow::on_btnColor_clicked()
{
    QPen pen;
    QColor color = QColorDialog::getColor();
    pen.setColor(color);
    data.painter->setPen(pen);
}

void MainWindow::on_btnShow_clicked()
{
    data.image->fill();
    scene->clear();

    QColor bufcolor = data.painter->pen().color();
    data.painter->setPen(QColor("black"));

    std::vector<QPoint> edges;

    QString textstr = ui->textEdit->toPlainText();
    QRegExp rx("[,\t\n ]");
    QStringList list = textstr.split(rx, QString::SkipEmptyParts);

    QPoint point;
    QString str;

    for (int i = 0; i < list.length(); ++i) {

        str = list[i];

        if (i % 2 == 0) {
            point.setX((int) (str.toInt() + 0.5));
        }
        else {
            point.setY((int) (str.toInt() + 0.5));
            edges.push_back(point);
        }
    }

    if (edges.size() > 0) {
        for (unsigned i = 0; i < edges.size() - 1; ++i) {
            draw_line(edges[i], edges[i + 1], *(data.painter));
        }
        draw_line(edges[0], edges[edges.size() - 1], *(data.painter));
    }

    data.painter->drawLine(data.partition, data.image->height(), data.partition, 0);
    scene->addPixmap(*data.image);

    data.painter->setPen(QColor(bufcolor));
}
