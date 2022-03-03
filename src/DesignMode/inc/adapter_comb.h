#pragma once
/*
    ʹ�ø���ʵ��������ģʽ

    �ؼ����룺�������̳л��������еĶ���ʵ����Ҫ��Ŀ��ӿڡ�

    ����ʾ���У���������֮ǰ����һ��˫�˶��У��µ�����Ҫ��ʹ��ջ�Ͷ�������ɡ�

    ˫�˶��п�����ͷβɾ��������Ԫ�ء���ջ��һ���Ƚ���������ݽṹ���������ʱ��ӵ�ջ�Ķ�����ɾ������ʱ��ɾ   ��ջ���������ݡ����������ȫ���Խ�һ�����е�˫�˶��������һ��ջ��
*/
#include "public.h"

//˫�˶��У� ��������
class Deque
{
public:
    void PushBack(int x);
    void PushFront(int x);
    void PopBack();
    void PopFront();
};

//˳���࣬����Ŀ����
class Sequence
{
public:
    virtual void Push(int x) = 0;
    virtual void Pop() = 0;
};

//ջ������ȳ���������
class Stack : public Sequence
{
public:
    //��Ԫ����ӵ���ջ�Ķ���
    void Push(int x)override;

    //�Ӷ�ջ��ɾ������Ԫ��
    void Pop() override;

private:
    Deque m_deque;
};

//���У��Ƚ��ȳ���������
class Queue: public Sequence
{
public:
    //��Ԫ����ӵ�����β��
    void Push(int x) override;

    //�Ӷ�����ɾ������Ԫ��
    void Pop() override;
private:
    Deque m_deque;
};
