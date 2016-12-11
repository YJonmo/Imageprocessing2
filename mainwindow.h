#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <iostream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int ROII;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_ROI_clicked();

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
