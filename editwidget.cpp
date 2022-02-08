/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#include "editwidget.h"
#include "ui_editwidget.h"
#include <QMessageBox>


EditWidget::EditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWidget)
{
    ui->setupUi(this);

    //用户点击取消
    connect(ui->cancelBtn,&QPushButton::clicked,[=](){
        reset();
        this->hide();
    });

    //用户点击确定
    connect(ui->confirmBtn,&QPushButton::clicked,[=](){
        this->hide();
        QStringList info;//6格信息
        info << ui->nameLineEdit->text() << ui->idLineEdit->text()
        << ui->sexLineEdit->text()<< ui->birthdayLineEdit->text()
        << ui->teleLineEdit->text()<< ui->addressLineEdit->text();
        reset();
        for(int i = 0; i < info.size(); i++)
        {
            if(info[i] != "")
            {
                emit editedInfo(info);//向主窗口发送录入信号
                return;
            }

        }
        QMessageBox::warning(this, "提示", "不可插入空信息", QMessageBox::Yes);
    });

}

//重置
void EditWidget::reset()
{
    ui->nameLineEdit->setText("");
    ui->idLineEdit->setText("");
    ui->sexLineEdit->setText("");
    ui->birthdayLineEdit->setText("");
    ui->teleLineEdit->setText("");
    ui->addressLineEdit->setText("");
}

//重写 关闭
void EditWidget::closeEvent(QCloseEvent *event)
{
    reset();
    this->hide();
}
EditWidget::~EditWidget()
{
    delete ui;
}
