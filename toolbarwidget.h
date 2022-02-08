/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class toolBarWidget;
}

class toolBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit toolBarWidget(QWidget *parent = 0);
    ~toolBarWidget();
    void setEnabled();

private:
    Ui::toolBarWidget *ui;
    bool enabled;

signals:
    void insertedInfo();
    void sortInfo(QStringList info);

};

#endif // TOOLBARWIDGET_H
