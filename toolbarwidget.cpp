/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"
#include <QMessageBox>

toolBarWidget::toolBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toolBarWidget)
{
    ui->setupUi(this);
    enabled = 0;//新建或导入资源信息前，都不可操作表格

    //插入
    connect(ui->insertBtn,&QPushButton::clicked,[=](){
        if(enabled)
            emit insertedInfo();
        else
            QMessageBox::warning(this, "提示", "请先打开资源信息", QMessageBox::Yes);

    });

    //查找
    connect(ui->sortBtn,&QPushButton::clicked,[=](){
        if(enabled)
        {
            QStringList s;
            s << ui->sortEdit_Name->text() << ui->sortEdit_ID->text() <<ui->sortEdit_Tele->text();
            emit sortInfo(s);
        }
        else
            QMessageBox::warning(this, "提示", "请先打开资源信息", QMessageBox::Yes);
    });
}

//设置可操作
void toolBarWidget::setEnabled()
{
    enabled = 1;
}

toolBarWidget::~toolBarWidget()
{
    delete ui;
}
