/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2022.1.1
*/

#ifndef BST_H
#define BST_H

#include <iostream>  //输入输出流
#include <queue>  //队列
#include <QStringList>  //Qt字符串链表
#include <QDebug>
using namespace std;

////////模板 结构体 树结点////////
template <class T>
struct node{
    T data;//数据主体
    short index;//当前结点在表格中的索引号 至多为10000
    node *leftChild, *rightChild;//左孩子 右孩子
    //构造函数
    node():leftChild(0),rightChild(0){}
    node(T d, node *lc = 0, node *rc = 0):data(d),leftChild(lc),rightChild(rc){}
};


////////模板 类 二叉搜索树///////
template <class T>
class BST
{
public:
    BST();//构造函数
    void print();//打印 层次遍历
    void insert(T info);//插入
    short sort(T info);//查找    tip:带默认值的参数需要放在最后
    bool remove(T info);//删除 tip:delete为保护字，不可重用

    void destory(node<T>* n);
    ~BST();//析构函数

protected:
    node<T> *root;
    int currentIndex;//新结点的索引号
};

////////函数定义////////
//构造函数
template <class T>
BST<T>::BST()
{
    //root = new node<T>;
    root = nullptr;//根节点 置为空
    currentIndex = 0;
}

//打印 层次遍历
template <class T>
void BST<T>::print()
{
    if(root == 0) return;
    queue< node<QString>* > q;
    node<T> *p = root;
    q.push(p);
    while(!q.empty())//当队列不为空
    {
        p = q.front();
        q.pop();
        //cout << p->index;
        qDebug() << p->index << p->data;
        if(p->leftChild != 0)
            q.push(p->leftChild);
        if(p->rightChild != 0)
            q.push(p->rightChild);
    }
}

//插入
//参数：需要插入的结点的指针
template <class T>
void BST<T>::insert(T info)
{
    //若根节点为空
    if(root == 0)
    {
        root = new node<T>(info);
        root->index = currentIndex;
        ++currentIndex;//新结点的索引号+1
        return ;
    }
    //若根节点不为空
    node<T>* find = root;//找寻指针
    node<T>* parent;//找寻指针的父亲
    while(find != 0)//当找寻指针不为空
    {
        parent = find;
        if(info <= find->data)//小于等于，置左
           find = find->leftChild;
        else
            find = find->rightChild;
    }
    node<T> *n = new node<T>(info);
    if(info <= parent->data)
        parent->leftChild = n;    //插入结点
    else
        parent->rightChild = n;
    n->index = currentIndex;//设置索引号
    ++currentIndex;//新结点的索引号+1
}

//查找  缺点:此方法只可返回找到的第一个数据的索引号
template <class T>
short BST<T>::sort(T info)
{
    if(info == 0)//信息是空的
        return -1;//没必要找了

    node<T>* find = root;//找寻指针
    while(find != 0)//当找寻指针不为空
    {
        if(info < find->data)
            find = find->leftChild;
        else if(info > find->data)
            find = find->rightChild;
        else
        {
            if(find->index != -1)//若该结点未被删除
                return find->index;//找到 返回该结点的索引号
            break;
        }
    }
    return -1;//找不到 返回-1
}

//删除
//参数：需要删除的结点的信息
//感觉可以和查找函数写在一起
template <class T>
bool BST<T>::remove(T info)
{
    node<T>* find = root;//找寻指针
    while(find != 0)//当找寻指针不为空
    {
        if(info < find->data)
            find = find->leftChild;
        else if(info > find->data)
            find = find->rightChild;
        else
        {
            if(find->index == -1)//如果该结点已被删除
                find = find->leftChild;//转向左边
            else
            {
                find->index = -1;//伪删除
                return 1;
            }
        }
    }
    return -1;//找不到 返回-1
}


//析构函数
template <class T>
void BST<T>::destory(node<T>* n)
{
    destory(n->leftChild);
    destory(n->rightChild);
    delete n;
}
template <class T>

BST<T>::~BST()
{
    if(!root)
        destory(root);
}

#endif // BST_H
