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
    Instance = 3;
    ROII = 60;
    ThreshVale = 0;

    Object1_Index = 0;
    Object2_Index = 0;
    BackGround_Index = 0;

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
    ui->Object1_Index_Show->setText(QString::number(Object1_Index));
}

void MainWindow::on_radioButton_2_clicked()
{
    Instance = 2;
    ui->Object1_Index_Show->setText(QString::number(Object1_Index));
}

void MainWindow::on_radioButton_3_clicked()
{
    Instance = 3;
    ui->Object1_Index_Show->setText(QString::number(Object1_Index));
}

void MainWindow::on_ResetButton_clicked()
{
    Object1_Index = 0;
    Object2_Index = 0;
    BackGround_Index = 0;
    ui->Object1_Index_Show->setText(QString::number(Object1_Index));
    ui->Object2_Index_Show->setText(QString::number(Object2_Index));
    ui->BackGround_Index_Show->setText(QString::number(BackGround_Index));
}


void MainWindow::on_UpdateButton_clicked()
{
    ui->Object1_Index_Show->setText(QString::number(Object1_Index));
    ui->Object2_Index_Show->setText(QString::number(Object2_Index));
    ui->BackGround_Index_Show->setText(QString::number(BackGround_Index));
}
