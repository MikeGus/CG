#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
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


void MainWindow::on_btnPartition_clicked()
{
    data.image->fill();
    scene->clear();

    data.partition = ui->lineEdit->text().toInt();
    data.painter->setPen(QColor("black"));

    std::vector<QPoint> edges(data.edges);

    if (ui->checkAccurancy->isChecked()) {

        QString textstr = ui->textEdit->toPlainText();
        QRegExp rx("[,\t\n ]");
        QStringList list = textstr.split(rx, QString::SkipEmptyParts);

        QPoint point;
        QString str;
        edges.clear();

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
    }

    if (edges.size() > 0) {
        for (unsigned i = 0; i < edges.size() - 1; ++i) {
            draw_line(edges[i], edges[i + 1], *(data.painter));
        }
        draw_line(edges[0], edges[edges.size() - 1], *(data.painter));
    }

    data.painter->drawLine(data.partition, data.image->height(), data.partition, 0);
    scene->clear();
    scene->addPixmap(*data.image);
}


void MainWindow::on_btnClear_clicked()
{
    data.edges.clear();
    data.image->fill();
    scene->clear();
}

void MainWindow::on_btnRastr_clicked()
{
    data.image->fill();
    scene->clear();
    scene->addPixmap(*data.image);

    data.partition = ui->lineEdit->text().toInt();
    data.painter->setPen(QColor("black"));

    if (ui->checkAccurancy->isChecked()) {

        QString textstr = ui->textEdit->toPlainText();
        QRegExp rx("[,\t\n ]");
        QStringList list = textstr.split(rx, QString::SkipEmptyParts);

        QPoint point;
        QString str;
        data.edges.clear();

        for (int i = 0; i < list.length(); ++i) {

            str = list[i];

            if (i % 2 == 0) {
                point.setX((int) (str.toInt() + 0.5));
            }
            else {
                point.setY((int) (str.toInt() + 0.5));
                data.edges.push_back(point);
            }
        }
    }

    if (data.edges.size() > 0) {
        for (unsigned i = 0; i < data.edges.size() - 1; ++i) {
            data.painter->drawLine(data.edges[i], data.edges[i + 1]);
        }
        data.painter->drawLine(data.edges[0], data.edges[data.edges.size() - 1]);
    }

    scene->clear();
    scene->addPixmap(*data.image);
    QApplication::processEvents();

    bool timer = ui->checkDelay->isChecked();
    rast_fill(data, scene, timer);

    scene->clear();
    scene->addPixmap(*data.image);
    QApplication::processEvents();
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    data.painter->setPen("black");
    QPoint point = ui->graphicsView->mapFromParent(e->pos());
    point.setY(point.y() - 13);
    if((e->modifiers() & Qt::ShiftModifier) && !data.edges.empty()) {
        int dx = abs(data.edges[data.edges.size() - 1].x() - point.x());
        int dy = abs(data.edges[data.edges.size() - 1].y() - point.y());
        if (dy > dx) {
            point.setX(data.edges[data.edges.size()- 1].x());
        }
        else {
            point.setY(data.edges[data.edges.size()- 1].y());
        }
    }

    if (!data.edges.empty()) {
         data.painter->drawLine(data.edges[data.edges.size() - 1], point);
         scene->clear();
         scene->addPixmap(*data.image);
    }

    data.edges.push_back(point);
}
