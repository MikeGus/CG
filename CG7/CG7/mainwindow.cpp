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

    scene->data.pixmap = new QPixmap(scene->width(), scene->height());
    scene->data.pixmap->fill();

    scene->data.painter = new QPainter(scene->data.pixmap);


    ui->radioRect->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::on_radioRect_toggled(bool checked)
{
    if (checked) {
        scene->data.line_input = false;
        scene->data.final_rect = false;
        scene->data.final = false;
    }
}

void MainWindow::on_radioLines_toggled(bool checked)
{
    if (checked) {
        scene->data.line_input = true;
        scene->data.final = false;
        scene->data.final_rect = false;
    }
}

void MainWindow::on_btnClearLines_clicked()
{
    scene->data.lines.clear();
    scene->data.final = false;
    scene->data.final_rect = false;
    scene->data.pixmap->fill();

    QColor buffer = scene->data.painter->pen().color();
    scene->data.painter->setPen("black");
    if (scene->data.is_rect) {
        scene->data.painter->drawRect(scene->data.rectangle);
    }
    scene->clear();
    scene->addPixmap(*(scene->data.pixmap));
    scene->data.painter->setPen(buffer);
}

void MainWindow::on_btnClear_clicked()
{
    scene->data.lines.clear();
    scene->data.pixmap->fill();

    scene->data.final = false;
    scene->data.final_rect = false;
    scene->data.is_rect = false;

    scene->clear();
    scene->addPixmap(*(scene->data.pixmap));
}

void MainWindow::on_btnDraw_clicked()
{
    QColor bufcolor = scene->data.painter->pen().color();
    scene->data.painter->setPen(QColor("black"));

    QString textstr = ui->plainTextEdit->toPlainText();
    QRegExp rx("[,\t\n ]");
    QStringList list = textstr.split(rx, QString::SkipEmptyParts);

    QPoint p1;
    QPoint p2;

    QString str;
    if (ui->radioLines->isChecked()) {
        for (int i = 0; i < list.length(); ++i) {

            str = list[i];

            if (i % 4 == 0) {
                p1.setX((int) (str.toInt() + 0.5));
            }
            else if (i % 4 == 1) {
                p1.setY((int) (str.toInt() + 0.5));
            }
            else if (i % 4 == 2) {
                p2.setX((int) (str.toInt() + 0.5));
            }
            else {
                p2.setY((int) (str.toInt() + 0.5));
                QLine line(p1, p2);
                scene->data.lines.push_back(line);
            }
        }

        if (scene->data.is_rect) {
            chop(scene->data);
        }
        else {
            scene->data.painter->setPen(QColor("blue"));
            for (auto line : scene->data.lines) {
                scene->data.painter->drawLine(line);
            }
        }
    }
    else if (ui->radioRect->isChecked() && list.length() >= 4) {
        p1.setX((int) (list[0].toInt() + 0.5));
        p1.setY((int) (list[1].toInt() + 0.5));
        p2.setX((int) (list[2].toInt() + 0.5));
        p2.setY((int) (list[3].toInt() + 0.5));
        scene->data.rectangle = QRect(std::min(p1.x(), p2.x()), std::max(p1.y(), p2.y()),\
                                      abs(p1.x() - p2.x()), -abs(p1.y() - p2.y()));
        scene->data.is_rect = true;
        scene->data.final_rect = false;

        scene->data.painter->setPen(QColor("black"));
        scene->data.pixmap->fill();
        scene->data.painter->drawRect(scene->data.rectangle);

        chop(scene->data);
    }

    scene->addPixmap(*(scene->data.pixmap));

    scene->data.painter->setPen(QColor(bufcolor));
}
