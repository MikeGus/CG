#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    QRectF sizes(-150, -150, 300, 300);
    scene->setSceneRect(sizes);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

//change color sun
void MainWindow::on_pushButton_4_clicked()
{
    QColor color = QColorDialog::getColor();
    data.pen.setColor(color);
}

//change color line
void MainWindow::on_pushButton_3_clicked()
{
    QColor color = QColorDialog::getColor();
    data.pen.setColor(color);
}

//clear scene
void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
    ui->graphicsView->update();
}

void MainWindow::on_pushButton_6_clicked()
{
    scene->clear();
    ui->graphicsView->update();
}

//draw line
void MainWindow::on_pushButton_clicked()
{
    data.alg = (Algorithms) ui->comboBox->currentIndex();
    Point start;
    Point end;

    start.x = ui->lineEdit->text().toDouble();
    end.x = ui->lineEdit_2->text().toDouble();

    start.y = ui->lineEdit_3->text().toDouble();
    end.y = ui->lineEdit_4->text().toDouble();

    data.start = start;
    data.end = end;
    data.pen.setWidth(1);

    draw(*scene, data);

    ui->graphicsView->update();
}

//draw sun
void MainWindow::on_pushButton_5_clicked()
{
    data.alg = (Algorithms) ui->comboBox_2->currentIndex();
    Point center;
    Point end;

    center.x = ui->lineEdit_5->text().toDouble();
    center.y = ui->lineEdit_6->text().toDouble();

    double rad = 50;
    rad = ui->lineEdit_7->text().toDouble();

    double angle = M_PI / 2.0;

    angle = ui->lineEdit_8->text().toDouble() / 180 * M_PI;

    if (angle == 0) {
        angle = 0.01;
    }

    data.start = center;

    for (double a = 0; a < 2 * M_PI; a += angle) {
        end.x = center.x + cos(a) * rad;
        end.y = center.y + sin(a) * rad;

        data.end = end;
        data.pen.setWidth(1);

        draw(*scene, data);
    }

    ui->graphicsView->update();
}
