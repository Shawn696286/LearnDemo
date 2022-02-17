#pragma once
/*
    使用复合实现适配器模式

    关键代码：适配器继承或依赖已有的对象，实现想要的目标接口。

    以下示例中，假设我们之前有了一个双端队列，新的需求要求使用栈和队列来完成。

    双端队列可以在头尾删减或增加元素。而栈是一种先进后出的数据结构，添加数据时添加到栈的顶部，删除数据时先删   除栈顶部的数据。因此我们完全可以将一个现有的双端队列适配成一个栈。
*/
#include "public.h"

//双端队列， 被适配类
class Deque
{
public:
    void PushBack(int x);
    void PushFront(int x);
    void PopBack();
    void PopFront();
};

//顺序类，抽象目标类
class Sequence
{
public:
    virtual void Push(int x) = 0;
    virtual void Pop() = 0;
};

//栈，后进先出，适配类
class Stack : public Sequence
{
public:
    //将元素添加到堆栈的顶部
    void Push(int x)override;

    //从堆栈中删除顶部元素
    void Pop() override;

private:
    Deque m_deque;
};

//队列，先进先出，适配类
class Queue: public Sequence
{
public:
    //将元素添加到队列尾部
    void Push(int x) override;

    //从队列中删除顶部元素
    void Pop() override;
private:
    Deque m_deque;
};
