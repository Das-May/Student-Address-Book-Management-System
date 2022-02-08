/*版权信息：该项目版权归属 陈梓青
*学生通讯录管理系统2.0
*历史版本信息：
* 1.0 使用lixbl读取和存储表格文件.xls .xlsx .csv 效率高，但仅能实现百条数据的读写
* 2.0 使用.txt文件读取和存储文本文件 .txt 可以实现万条数据的读写
*作者：陈梓青
*完成日期：2021.1.1
*/

#ifndef MINHEAP_H
#define MINHEAP_H

#include <QDebug>
//#include <QObject>
//模板类不能继承QObject
template <class T>
class MinHeap
{
    //Q_OBJECT//如果自定义类使用了信号/槽机制，就需要在定义类时加上Q_OBJECT宏，否则singnals、slots定义编译器无法识别
public:
    //构造函数
    MinHeap(int n = 1):maxSize(n)
    {
        heap = new T[n];
        if(!heap)
        {
            abort();
        }
        currentSize = 0;
    }

    //插入元素
    void put(T data)
    {
        if(currentSize < maxSize)
        {
            heap[currentSize] = data;
            currentSize++;
        }
        else
        {
            heap[currentSize - 1] = data;
        }
        //上滑调整
        int i = currentSize - 1;
        int j = i / 2;
        T temp = heap[i];
        while(i > 0)
        {
            if(heap[j] > temp)
                break;
            else
            {
                heap[i] = heap[j];
                i = j;
                j = j / 2;
            }
        }
        heap[i] = temp;
//        qDebug() << "插入元素成功！";
    }

    //获取堆顶元素
    T top() const
    {
        return heap[0];
    }

    //弹出堆顶元素
    T pop()
    {
        T top = heap[0];
        currentSize--;
        heap[0] = heap[currentSize];
        //下滑调整
        int i = 0;
        int j = i * 2 + 1;//左孩子
        T temp = heap[i];
        while(j < currentSize)
        {
            if(heap[j + 1] > heap[j])//如果右孩子更小，则转为右孩子
                j++;
            if(heap[i] > heap[j])
                break;
            else
            {
                heap[i] = heap[j];
                i = j;
                j = j * 2 + 1;
            }
        }
        heap[i] = temp;
//        qDebug() << "弹出堆顶元素！";
        return top;
    }

    ~MinHeap()
    {
        delete heap;
    }

private:
    T *heap;
    int maxSize, currentSize;

};

#endif // MINHEAP_H
