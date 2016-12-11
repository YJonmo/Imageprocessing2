#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ROII = 10;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ROI_clicked()
{
    QString ROISize = ui->InputROI->text();
    ui->Replica->setText((ui->InputROI->text()));
    std::cout << ROISize.toStdString() << std::endl;
    //return (ROISize.toStdString());
    ROII = ROISize.split(" ")[0].toInt();
    //ROII = ROISize.toStdString());
}



