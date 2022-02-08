/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#include "mainwindow.h"
#include "bst.h"
#include <QApplication>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
//    //////测试构造函数
//    BST<QString> *tree = new BST<QString>();
//    node<QString> *n1 = new node<QString>(5),
//            *n2 = new node<QString>(5),
//            *n3 = new node<QString>(5);

//    ///////测试运算符重载
//    for(int i = 0; i < 4; i++)
//    {
//        n1->data[i] =
//        n2->data[i] =
//        n3->data[i] = QString::number(i);
//    }
//    n1->data[4] = n3->data[4] = QString::number(5);
//    n2->data[4] = QString::number(9);
//    qDebug() << "n1->data[4] > n2->data[4]" <<(n1->data[4] > n2->data[4]); //t

//    qDebug() << "n1==n2" << (n1==n2);  //f
//    qDebug() << "n1>n2" <<(n1>n2); //f
//    qDebug() << "n1<n2" << (n1<n2);  //t

//    qDebug() << "*n1>*n2" <<(*n1 > *n2); //t
//    qDebug() << "*n1<*n2" <<(*n1 < *n2);  //f

//    qDebug() << "n2->data[4] < n3->data[4]" <<(n2->data[4] < n3->data[4]);//t
//    qDebug() << "*n2<*n3" <<(*n2 < *n3);//t

//    ///////测试插入
//    tree->insert(n1);
//    tree->insert(n2);
//    tree->insert(n3);

//    ////测试展示
//    tree->print();
//    //奇怪的现象：在插入函数中，传入结构体的引用，运算符判断结果相反；传入结构体指针，判断结果正确

//    ///////测试查找
//    qDebug() << n2->data[4];
//    qDebug() << tree->sort("9",4);

//    //////测试删除
////    bool tag = 0;
////    int a = 5, b = 10;
////    tag?a:b = 2;
////    qDebug() << a << b ;
////    tag = 1;
////    tag?a:b = 2;
////    qDebug() << a << b ;

////    int &p = tag?a:b;
////    qDebug() << p;
////    int &q = (!tag)?a:b;
////    qDebug() << q;

//    if(tree->remove(n1))
//        qDebug() << tree->sort("5",4); //2√
//    if(tree->remove(n2))
//        qDebug() << tree->sort("9",4);  //-1√

    /////测试窗口
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
