/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bst.h"  //二叉搜索树
#include <QString>  //Qt字符串
#include <QStringList>  //Qt字符串链表
#include <QVector> //容器
#include <QTableWidget>  //表格窗口控件
#include <QLabel>
#include "editwidget.h"  //自定义信息编辑窗口
#include "minheap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void read();//读入
    void initTableWidget(int index, int row);
    void write(bool saveAs = 0);//saveAs==0时保存 saveAs==1时另存为

    ~MainWindow();

private:
    void clear();//清空数据

    Ui::MainWindow *ui;
    QVector<BST<QString>*> nameTrees;//记录姓名的树林
    QVector<BST<QString>*> idTrees;//记录学号的树林
    QVector<BST<QString>*> teleTrees;//记录电话的树林
    QVector<QTableWidget*> tables;  //表格

    MinHeap<QString> *minHeap;//最小堆保存年龄小的的同学们
    QLabel *minLabel;
    int sheet;//工作簿数量
    int rowCount;//数据量

    QString filePath;//记录文件读取/保存路径
    EditWidget *ew_Insert;//编辑信息窗口  为插入学生信息而服务
    EditWidget *ew_Edit;//编辑信息窗口  为编辑学生信息而服务

    void insertInfo(QStringList info);//槽函数 为二插搜索树和表格实现插入
    void editInfo(QStringList info);//槽函数 为二插搜索树和表格实现编辑
    void sortInfo(QStringList info);//槽函数 搜索用户提供的信息 并在表格中显示
    int sortTree(int s, QStringList info);//void sortInfo(QStringList info);的子函数，负责搜索三棵树并返回找到的值的结点
};

#endif // MAINWINDOW_H
