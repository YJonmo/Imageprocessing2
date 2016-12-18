#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initializing
    Instance = 0;
    ROII = 200;
    ThreshVale = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ROI_clicked()
{
    QString ROISize = ui->InputROI->text();
    //ui->Replica->setText((ui->InputROI->text()));
    std::cout << ROISize.toStdString() << std::endl;
    //return (ROISize.toStdString());
    ROII = ROISize.split(" ")[0].toInt();
    //ROII = ROISize.toStdString());
    QString ThreshValueS = ui->Replica->text();
    ThreshVale = ThreshValueS.split(" ")[0].toInt();
}


void MainWindow::on_radioButton_clicked()
{
    Instance = 1;
}

void MainWindow::on_radioButton_2_clicked()
{
    Instance = 2;
}

void MainWindow::on_radioButton_3_clicked()
{
    Instance = 3;
}
