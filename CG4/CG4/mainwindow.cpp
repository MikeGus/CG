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

    double xc = ui->lineEdit->text().toDouble();
    double a = ui->lineEdit_2->text().toDouble();

    double yc = ui->lineEdit_3->text().toDouble();
    double b = ui->lineEdit_4->text().toDouble();

    start.x = xc - a;
    end.x = xc + a;
    start.y = yc + b;
    end.y = yc - b;

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
    Point start;
    Point end;

    double cx = ui->lineEdit_5->text().toDouble();
    double cy = ui->lineEdit_6->text().toDouble();

    double rad = ui->lineEdit_7->text().toDouble();

    start.x = cx - rad;
    end.x = cx + rad;

    start.y = cy + rad;
    end.y = cy - rad;

    data.start = start;
    data.end = end;

    draw_circle(*scene, data);

    ui->graphicsView->update();
}

void MainWindow::on_pushButton_8_clicked()
{
    scene->clear();
    ui->graphicsView->update();
}

void MainWindow::on_pushButton_12_clicked()
{
    scene->clear();
    ui->graphicsView->update();
}

void MainWindow::on_pushButton_10_clicked()
{
    QColor color = QColorDialog::getColor();
    data.pen.setColor(color);
}

void MainWindow::on_pushButton_7_clicked()
{
    QColor color = QColorDialog::getColor();
    data.pen.setColor(color);
}

void MainWindow::on_pushButton_9_clicked()
{
    data.alg = (Algorithms) ui->comboBox_3->currentIndex();
    Point start;
    Point end;

    double xc = ui->lineEdit_11->text().toDouble();
    double a = ui->lineEdit_10->text().toDouble();

    double yc = ui->lineEdit_8->text().toDouble();
    double b = ui->lineEdit_9->text().toDouble();

    double step_a = ui->lineEdit_12->text().toDouble();
    double step_b = step_a / a * b;

    int count  = ui->lineEdit_17->text().toInt();

    for (int i = 0; i < count; ++i) {
        start.x = xc - a;
        end.x = xc + a;
        start.y = yc + b;
        end.y = yc - b;

        data.start = start;
        data.end = end;
        data.pen.setWidth(1);

        draw(*scene, data);
        a += step_a;
        b += step_b;
    }

    ui->graphicsView->update();
}

void MainWindow::on_pushButton_11_clicked()
{
    data.alg = (Algorithms) ui->comboBox_3->currentIndex();
    Point start;
    Point end;

    double xc = ui->lineEdit_14->text().toDouble();
    double yc = ui->lineEdit_15->text().toDouble();
    double r = ui->lineEdit_13->text().toDouble();

    double step = ui->lineEdit_16->text().toDouble();

    int count  = ui->lineEdit_18->text().toInt();

    for (int i = 0; i < count; ++i) {
        start.x = xc - r;
        end.x = xc + r;
        start.y = yc + r;
        end.y = yc - r;

        data.start = start;
        data.end = end;
        data.pen.setWidth(1);

        draw(*scene, data);
        r += step;
    }
    ui->graphicsView->update();
}
