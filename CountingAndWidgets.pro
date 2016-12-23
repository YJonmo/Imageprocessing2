#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T19:11:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test3
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
LIBS += `pkg-config opencv --libs`

SOURCES +=\
        mainwindow.cpp \
    Grid_Histogram.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
