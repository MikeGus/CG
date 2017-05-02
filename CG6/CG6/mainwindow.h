#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "draw_data.h"
#include "draw_line.h"
#include <QApplication>
#include <QMouseEvent>
#include "filling.h"
#include <QDebug>

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

    void on_btnClear_clicked();

    void showEvent(QShowEvent *event);

    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void on_btnColor_clicked();

    void on_btnShow_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
