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
    int Instance ;
    int ThreshVale;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_ROI_clicked();

public:
    Ui::MainWindow *ui;
private slots:
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_Replica_cursorPositionChanged(int arg1, int arg2);
};

#endif // MAINWINDOW_H
