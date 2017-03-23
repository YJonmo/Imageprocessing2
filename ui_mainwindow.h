/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *ResetButton;
    QPushButton *UpdateButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *Object1_Index_Show;
    QLineEdit *Object2_Index_Show;
    QLineEdit *BackGround_Index_Show;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ROI;
    QLineEdit *InputROI;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *Ill_No_Correct;
    QRadioButton *Ill_Correct;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QPushButton *BLurrInputButton;
    QLineEdit *InputBlurrSize;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Magnific;
    QLineEdit *MagInput;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(297, 369);
        MainWindow->setDocumentMode(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QStringLiteral("ResetButton"));
        ResetButton->setGeometry(QRect(20, 280, 80, 21));
        UpdateButton = new QPushButton(centralWidget);
        UpdateButton->setObjectName(QStringLiteral("UpdateButton"));
        UpdateButton->setGeometry(QRect(120, 280, 80, 21));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 190, 127, 78));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Object1_Index_Show = new QLineEdit(layoutWidget);
        Object1_Index_Show->setObjectName(QStringLiteral("Object1_Index_Show"));

        verticalLayout->addWidget(Object1_Index_Show);

        Object2_Index_Show = new QLineEdit(layoutWidget);
        Object2_Index_Show->setObjectName(QStringLiteral("Object2_Index_Show"));

        verticalLayout->addWidget(Object2_Index_Show);

        BackGround_Index_Show = new QLineEdit(layoutWidget);
        BackGround_Index_Show->setObjectName(QStringLiteral("BackGround_Index_Show"));

        verticalLayout->addWidget(BackGround_Index_Show);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(7, 189, 101, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget1);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget1);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setEnabled(false);

        verticalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(layoutWidget1);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setEnabled(true);
        radioButton_3->setChecked(true);

        verticalLayout_2->addWidget(radioButton_3);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 150, 191, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ROI = new QPushButton(layoutWidget2);
        ROI->setObjectName(QStringLiteral("ROI"));

        horizontalLayout_2->addWidget(ROI);

        InputROI = new QLineEdit(layoutWidget2);
        InputROI->setObjectName(QStringLiteral("InputROI"));

        horizontalLayout_2->addWidget(InputROI);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 10, 168, 47));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        Ill_No_Correct = new QRadioButton(layoutWidget3);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(Ill_No_Correct);
        Ill_No_Correct->setObjectName(QStringLiteral("Ill_No_Correct"));
        Ill_No_Correct->setEnabled(true);
        Ill_No_Correct->setChecked(true);

        verticalLayout_4->addWidget(Ill_No_Correct);

        Ill_Correct = new QRadioButton(layoutWidget3);
        buttonGroup->addButton(Ill_Correct);
        Ill_Correct->setObjectName(QStringLiteral("Ill_Correct"));

        verticalLayout_4->addWidget(Ill_Correct);

        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 60, 281, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        BLurrInputButton = new QPushButton(layoutWidget4);
        BLurrInputButton->setObjectName(QStringLiteral("BLurrInputButton"));
        BLurrInputButton->setCheckable(false);
        BLurrInputButton->setChecked(false);
        BLurrInputButton->setFlat(false);

        horizontalLayout->addWidget(BLurrInputButton);

        InputBlurrSize = new QLineEdit(layoutWidget4);
        InputBlurrSize->setObjectName(QStringLiteral("InputBlurrSize"));
        InputBlurrSize->setReadOnly(false);

        horizontalLayout->addWidget(InputBlurrSize);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 110, 111, 24));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Magnific = new QPushButton(widget);
        Magnific->setObjectName(QStringLiteral("Magnific"));

        horizontalLayout_3->addWidget(Magnific);

        MagInput = new QLineEdit(widget);
        MagInput->setObjectName(QStringLiteral("MagInput"));

        horizontalLayout_3->addWidget(MagInput);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        ResetButton->raise();
        UpdateButton->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        Magnific->raise();
        MagInput->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 297, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(radioButton_2, radioButton_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        UpdateButton->setText(QApplication::translate("MainWindow", "Update", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Object Type 1", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Oject Type 2", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Background", 0));
        ROI->setText(QApplication::translate("MainWindow", "ROI size (pixel)", 0));
        InputROI->setText(QApplication::translate("MainWindow", "60", 0));
        Ill_No_Correct->setText(QApplication::translate("MainWindow", "No Illumination Correction", 0));
        Ill_Correct->setText(QApplication::translate("MainWindow", "Illumination Correction", 0));
        BLurrInputButton->setText(QApplication::translate("MainWindow", "Blurr size (pixel) for illumination correction", 0));
        InputBlurrSize->setText(QApplication::translate("MainWindow", "500", 0));
        Magnific->setText(QApplication::translate("MainWindow", "Magnification", 0));
        MagInput->setText(QApplication::translate("MainWindow", "5", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
