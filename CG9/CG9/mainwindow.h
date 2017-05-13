#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintdevice.h"
#include <QDebug>
#include "myqgraphicsview.h"
#include "chop.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showEvent(QShowEvent* event);

private slots:
    void on_radioRect_toggled(bool checked);

    void on_radioLines_toggled(bool checked);

    void on_btnClearLines_clicked();

    void on_btnClear_clicked();

    void on_btnDraw_clicked();

private:
    Ui::MainWindow *ui;
    Paintdevice* scene;
};

#endif // MAINWINDOW_H
