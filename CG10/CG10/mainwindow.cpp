#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::showEvent(QShowEvent* event)
{
    scene = new Paintdevice(ui->graphicsView->rect(), ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->data.pixmap = new QPixmap(scene->width(), scene->height());
    scene->data.pixmap->fill();

    scene->data.painter = new QPainter(scene->data.pixmap);

    ui->radioFigure->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}


void MainWindow::on_btnClearLines_clicked()
{
    scene->data.buffer.clear();
    scene->data.fig.bounds.clear();
    scene->data.fig.holes.clear();

    scene->data.painter->setPen(QColor("black"));
    QPolygon buffer(scene->data.split.bounds);
    scene->data.painter->drawPolygon(buffer);

    for (int i = 0; i < scene->data.split.holes.size(); ++i) {
        QPolygon buffer(scene->data.split.holes[i]);
        scene->data.painter->drawPolygon(buffer);
    }

    scene->clear();
    scene->data.pixmap->fill();
    split(scene->data);
    scene->addPixmap(*(scene->data.pixmap));
}

void MainWindow::on_btnClear_clicked()
{
    scene->data.buffer.clear();

    scene->data.split.bounds.clear();
    scene->data.split.holes.clear();

    scene->data.fig.bounds.clear();
    scene->data.fig.holes.clear();

    scene->data.pixmap->fill();
    scene->clear();
    scene->addPixmap(*(scene->data.pixmap));
}

void MainWindow::add_figure()
{
    if (scene->data.buffer.size() > 2) {
        switch (scene->data.type_of_input) {
        case SPLIT:
            scene->data.split.bounds = scene->data.buffer;
            scene->data.split.holes.clear();
            break;
        case FIGURE:
            scene->data.fig.bounds = scene->data.buffer;
            scene->data.fig.holes.clear();
            break;
        }
        scene->data.painter->drawLine(*(scene->data.buffer.begin()), *(scene->data.buffer.rbegin()));
    }
    else {
        scene->data.pixmap->fill();

    }
    scene->data.buffer.clear();
}

void MainWindow::on_radioSplit_toggled(bool checked)
{
    add_figure();
    if (checked) {
        scene->data.type_of_input = SPLIT;
    }
}

void MainWindow::on_radioFigure_toggled(bool checked)
{
    add_figure();
    if (checked) {
        scene->data.type_of_input = FIGURE;
    }
}
