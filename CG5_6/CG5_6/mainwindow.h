#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "draw_data.h"
#include "draw_line.h"
#include "rastr_fill.h"
#include <QApplication>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene* scene;
    DrawData data;

private slots:
    void on_btnPartition_clicked();

    void on_btnClear_clicked();

    void showEvent(QShowEvent *event);

    void on_btnRastr_clicked();

    void mousePressEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
