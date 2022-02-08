/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>  //Qt字符串
#include <QStringList> //Qt字符串链表
#include <QPushButton>  //按钮控件
#include <QFile>
#include <QDataStream>
#include <QFileDialog>  //文件对话框
#include <QMessageBox>  //消息对话框
#include <QLabel>  //标签控件
#include <QTableWidgetItem>  //表格项类
#include "toolbarwidget.h"  //自定义工具栏窗口

#include <iostream>
#include <fstream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sheet = 0;
    rowCount = 0;
    minHeap = new MinHeap<QString>(100);
    minLabel = new QLabel();
    ui->statusBar->addWidget(minLabel);

    /////////窗口设置//////
    setWindowTitle("学生通讯录管理系统 2.0");
    //setWindowIcon(QIcon(":/res/icon.png"));

    //设置工具栏
    toolBarWidget *t = new toolBarWidget();
    ui->toolBar->addWidget(t);

    //信息录入窗口
    ew_Insert = new EditWidget();
    ew_Edit = new EditWidget();

    ////////功能键设置////////
    //打开文件
    connect(ui->actionOpen,&QAction::triggered,[=](){
        read();
        if(filePath != "")
            t->setEnabled();//顶栏可使用
    });

    //保存文件
    connect(ui->actionSave,&QAction::triggered,[=](){
        write(0);
    });

    //另存为
    connect(ui->actionSaveAs,&QAction::triggered,this,[=](){
        write(1);
    });


    //退出
    connect(ui->actionClose,&QAction::triggered,[=](){
        this->close();
    });

    //插入
    connect(t,&toolBarWidget::insertedInfo,[=](){  //成功点击插入按钮
        ew_Insert->show();
    });
    connect(ew_Insert,&EditWidget::editedInfo,this,&MainWindow::insertInfo);

    //编辑(通用)
    connect(ew_Edit,&EditWidget::editedInfo,this,&MainWindow::editInfo);

    //查询
    connect(t,&toolBarWidget::sortInfo,this,&MainWindow::sortInfo);

}

//读取文件
void MainWindow::read()
{
    clear();

    //指定父对象（this），“open”具体操作，打开，“../”默认，之后可以添加要打开文件的格式
    filePath = QFileDialog::getOpenFileName(this,"open","","data(*.txt)");//维护文件路径
    qDebug() << filePath;

    if(filePath.isEmpty() == false)//用户选择文件后
    {
        ifstream read(filePath.toStdString(), ios::in);
        if (!read) {
            qDebug() << "文件打开失败！" << endl;
            return;
        }
        string str;
        int sheet = -1;//每10万行为1工作簿
        int row = 0;
        while (getline(read, str))//逐行读取
        {
            QString qstr = QString(QString::fromLocal8Bit(str.c_str()));//有效防止乱码
            qDebug() << qstr << qstr.length();

            if(row % 1000 == 0)
            {
                sheet++;
                row = 0;
                tables.push_back(new QTableWidget());//新建表格(工作簿)
                initTableWidget(sheet, 1000);
                qDebug() << "当前栈窗口索引号" << ui->stackedWidget->currentIndex();
                nameTrees.push_back(new BST<QString>());//新建树
                idTrees.push_back(new BST<QString>());
                teleTrees.push_back(new BST<QString>());
            }

            for(int i = 2; i < 8; i++)
            {
                int position = qstr.indexOf("\t");
                qDebug() << position;
                QString subStr = qstr.left(position);//截取信息
                qDebug() << subStr;
                if(i == 2)//姓名树
                    nameTrees[sheet]->insert(subStr);
                else if(i == 3)//学号树
                    idTrees[sheet]->insert(subStr);
                else if(i == 6)//电话树
                    teleTrees[sheet]->insert(subStr);
                else if(i == 5)//生日堆
                    minHeap->put(subStr);
                tables[sheet]->setItem(row,i,new QTableWidgetItem(subStr));//写入表格
                qstr = qstr.right(qstr.length() - position - 1);//丢弃已录入的字符串
            }

            rowCount++;
            row++;
        }
        minLabel->setText("最小年龄的学生信息: " + minHeap->top());
        QMessageBox::warning(this,tr("读取情况"),tr("读取完成！"),QMessageBox::Yes);
        read.close();
    }
    ui->stackedWidget->setCurrentIndex( sheet );
}

//导出文件
void MainWindow::write(bool saveAs)
{
    QString tempPath = filePath;
    if(saveAs)//若用户点击了另存为，则先让用户选择保存路径
    {
        tempPath = QFileDialog::getSaveFileName(this, "保存文件", "", "文本(*.txt)");
        qDebug() << tempPath;
        if(tempPath == "")//path==""说明用户未选择另存为的路径
            return;
        else
            filePath = tempPath;
    }
    if(filePath != "")
    {
        ofstream write(filePath.toUtf8().data(), ios::out);
        if (!write) {
            qDebug() << "文件打开失败！" << endl;
            return;
        }
        for(int i = 0; i < rowCount; i++)
        {
            for(int j = 2; j < 8; j++)
                if(tables[sheet]->item(i,j))//确保单元格指针不为空
                    write << tables[sheet]->item(i,j)->text().toUtf8().data() << '\t';
            write << '\n';

        }
        QMessageBox::warning(this,tr("保存情况"),tr("保存成功！"),QMessageBox::Yes);
        write.close();
    }
}

//初始化表格  参数：该表格的索引号 该表格的行数
void MainWindow::initTableWidget(int index, int row)
{
    if(index < 0)
    {
        qDebug() << "表格窗口数组越界！";
        return;
    }
    QStringList headerText;
    headerText<<""<<""<<"姓名"<<"学号"<<"性别"<<"出生日期"<<"电话"<<"地址";
    tables[index]->setColumnCount(headerText.count());//列数与headerText的列数相等
    tables[index]->setHorizontalHeaderLabels(headerText);//设置水平表头
    tables[index]->horizontalHeader()->setStretchLastSection(true); //行头自适应表格
    tables[index]->setRowCount(row);//需要先设置行数 否则设置单元格无用
    tables[index]->setShowGrid(false);//不显示网格线
    tables[index]->verticalHeader()->setHidden(true);//隐藏默认行号
    tables[index]->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁用编辑
    tables[index]->setTabletTracking(1);
    tables[index]->setSelectionBehavior(QAbstractItemView::SelectRows);//设定选择行为，按行选择

    for(int r = 0; r < row; r++)
    {
        //在第一列放入编辑按钮
        QPushButton *editBtn = new QPushButton("编辑");
//        editBtn->setStyleSheet("{background-color:transparent; text-color:green;}");
        connect(editBtn,&QPushButton::clicked,[=](){
            ew_Edit->show();
        });
        tables[index]->setCellWidget(r,0,editBtn);
        //在第二列放入删除按钮
        QPushButton *removeBtn = new QPushButton("删除");
        connect(removeBtn,&QPushButton::clicked,[=](){
            nameTrees[index]->remove(tables[index]->item(r, 2)->text());
            nameTrees[index]->print();//打印
            idTrees[index]->remove(tables[index]->item(r, 3)->text());
            teleTrees[index]->remove(tables[index]->item(r, 6)->text());
            tables[index]->setRowHidden(r, 1);//隐藏行，不会改变索引号
        });
        tables[index]->setCellWidget(r,1,removeBtn);
    }

    ui->stackedWidget->insertWidget(index, tables[index]); //加入栈窗口
    /*如果用addWidget，那么第一个被加入的表格将会被放到索引号为2的栈窗口   不知道为什么*/
    ui->stackedWidget->setCurrentWidget(tables[index]);//不加这句 表格无法显示
}

//插入信息 参数是有6格的行信息
void MainWindow::insertInfo(QStringList info)
{
    qDebug() << "插入数据:" << info[0] << info[1];
    //判断 更新最小年龄的学生
    if(info[3] > minHeap->top())
    {
        minHeap->put(info[3]);
        minLabel->setText("最小年龄的学生信息: " + info[3]);
    }
    //插入树中
    nameTrees[sheet]->insert(info[0]);
    nameTrees[sheet]->print();
    idTrees[sheet]->insert(info[1]);
    teleTrees[sheet]->insert(info[4]);
    //插入表格中 放在最后一行
    int row = tables[sheet]->rowCount();
    tables[sheet]->setRowCount(row+1);
    //写入字符串
    for(int i = 2; i <= 8; i++)
    {
        tables[sheet]->setItem(row, i, new QTableWidgetItem(""));
        /*不知道为什么 用info[i-2]无法new QTableWidgetItem*/
        if(tables[sheet]->item(row, i))
            tables[sheet]->item(row, i)->setText(info.at(i-2));
    }
    //在第一列放入编辑按钮
    QPushButton *editBtn = new QPushButton("编辑");
    editBtn->setStyleSheet("{background-color:transparent; text-color:green;}");
    connect(editBtn,&QPushButton::clicked,[=](){
        ew_Edit->show();
    });
    tables[sheet]->setCellWidget(row,0,editBtn);
    //在第二列放入删除按钮
    QPushButton *removeBtn = new QPushButton("删除");
    connect(removeBtn,&QPushButton::clicked,[=](){
        nameTrees[sheet]->remove(tables[sheet]->item(row, 2)->text());
        nameTrees[sheet]->print();//打印
        idTrees[sheet]->remove(tables[sheet]->item(row, 3)->text());
        teleTrees[sheet]->remove(tables[sheet]->item(row, 6)->text());
        tables[sheet]->setRowHidden(row, 1);//隐藏行，不会改变索引号
    });
    tables[sheet]->setCellWidget(row,1,removeBtn);
    //跳转栈窗口
    ui->stackedWidget->setCurrentIndex(sheet);
}

//槽函数 搜索
//搜索用户提供的信息 并在表格中显示 参数是3格的信息 找到返回树中的索引号 找不到返回-1
//改进策略：设计一个QVector容器，存放找到的多个相同信息的不同位置，确保不会略过同名同姓的情况
void MainWindow::sortInfo(QStringList info)
{
    qDebug() << info[0] << info[1] << info[2];

    //////内容为空 无需执行查找
    if(info[0] == "" && info[1] == "" && info[2] == "")
        return;

    //////内容不为空 执行查找
    int i, row = -1, temp;//容器中的第k个表格 某次被找到的信息的索引号是temp  则此行数为temp%1000
    for(i = 0; i <= sheet; i++)
    {
        temp = sortTree(i, info);
        if(temp != -1)
            break;
    }

    //////展示查找结果
    if(temp == -1)//如果找不到
        QMessageBox::information(this, "提示", "查无此人", QMessageBox::Yes);
    else//如果找到了
    {
        qDebug() << "当前页面的索引号" << ui->stackedWidget->currentIndex();
        ui->stackedWidget->setCurrentIndex(i);
        qDebug() << "row=" << temp % 1000 << "sheet=" << i;
        for(int j = 2; j < 8; j++)//j列
        {
            //设置选中行的背景色，必须要显示设置，即代码设置或者在ui文件的控件中设置，用系统默认的是无法代码选中高亮某行
            tables[i]->setStyleSheet("selection-background-color:rgb(0,0,180)");
            //设置要选中高亮的行，这里会触发QTableWidget::itemClicked的信号
            tables[i]->selectRow(temp % 1000);
//            if(tables[i]->item(j,temp % 1000))//如果单元格不为空
//            {
//                tables[i]->item(j,temp % 1000)->setBackgroundColor(QColor("0000ff"));//背景色强调
//            }
        }
    }
}

//void sortInfo(QStringList info);的子函数，负责搜索三棵树并返回找到的值的结点
//参数: 第s棵树 数据内容为info
int MainWindow::sortTree(int s, QStringList info)
{
    int i = -1, temp = -1;
    for(int j = 0; j < 3; j++)
    {
        qDebug() << info[j];
        if(info[j] != "")
        {
            if(j == 0)
                temp = nameTrees[s]->sort(info[j]);
            else if(j == 1)
                temp = idTrees[s]->sort(info[j]);
            else if(j == 2)
                temp = teleTrees[s]->sort(info[j]);
            qDebug() << "s:" << s << "temp:" << temp << "i:" << i;

            //①当i未曾被赋值，且找到了对应的结点
            //②原本找到的结点与新找到的结点一致
            if((i == -1 && temp != -1) || (i == temp && i != -1))
                i = temp;//将i初始化为找到的索引号,继续查找
            //其它情况则视为找不到，则跳出循环
            else
                break;
        }
    }
    return temp;
}

//槽函数 为二插搜索树和表格实现编辑
void MainWindow::editInfo(QStringList info)
{
    int p = ui->stackedWidget->currentIndex();//当前表格的索引号
    qDebug() << "当前表格的索引号" << p;
    int i = tables[p]->currentRow();//所要编辑的行号
    qDebug() << "所要编辑的行号" << i;
    for(int j = 2; j < 9; j++)
    {
        if(tables[p]->item(i,j))//单元格不为空
            tables[p]->item(i,j)->setText(info[j-2]);
    }
    //暂时未实现树的编辑
//    nameTrees[p]->insert(info[0]);
//    idTrees[p]->insert(info[1]);
//    teleTrees[p]->insert(info[4]);
}

//清空数据
void MainWindow::clear()
{
    nameTrees.clear();
    idTrees.clear();
    teleTrees.clear();
    tables.clear();

    sheet = 0;
    rowCount = 0;
}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}
