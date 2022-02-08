#-------------------------------------------------
#
# Project created by QtCreator 2021-11-11T12:56:09
#
#版权信息：该项目版权归属 陈梓青
#学生通讯录管理系统2.0
#历史版本信息：
# 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
# 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
#作者：陈梓青
#完成日期：2021.1.1
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SABMS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    toolbarwidget.cpp \
    editwidget.cpp

HEADERS += \
        mainwindow.h \
    bst.h \
    toolbarwidget.h \
    editwidget.h \
    minheap.h

FORMS += \
    mainwindow.ui \
    toolbarwidget.ui \
    editwidget.ui

