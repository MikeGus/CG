#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <windows.h>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    rast_fill(data, scene);
//    fill_edge(data.edges[0], data.edges[1], data.partition, *data.image, *data.painter, scene);
//    fill_edge(data.edges[1], data.edges[2], data.partition, *data.image, *data.painter, scene);
//    fill_edge(data.edges[2], data.edges[3], data.partition, *data.image, *data.painter, scene);
//    if (data.edges.size() > 0) {
//        for (unsigned i = 0; i < data.edges.size() - 1; ++i) {
//            fill_edge(data.edges[i], data.edges[i + 1], data.partition, *data.image, *data.painter, scene);
//            scene->addPixmap(*data.image);
//        }
//        fill_edge(data.edges[0], data.edges[data.edges.size() - 1], data.partition, *data.image, *data.painter, scene);
//    }
    scene->addPixmap(*data.image);
}
