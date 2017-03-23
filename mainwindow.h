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
    int Blurr_size;
    int Illumination; //0 = no illumination correction
    int Magnification;

    int Object1_Index;
    int Object2_Index;
    int BackGround_Index;

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
    void on_ResetButton_clicked();
    void on_UpdateButton_clicked();
    void on_pushButton_clicked();
    void on_Ill_Correct_clicked();
    void on_Ill_No_Correct_clicked();
    void on_BLurrInputButton_clicked();
    void on_Magnific_clicked();
};

#endif // MAINWINDOW_H
