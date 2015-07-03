#-------------------------------------------------
#
# Project created by QtCreator 2015-06-19T08:21:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BPNN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    para.cpp \
    workerthread.cpp \
    bp.cpp

HEADERS  += mainwindow.h \
    para.h \
    workerthread.h \
    bp.h \


FORMS    += mainwindow.ui
