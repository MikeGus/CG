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
