#pragma once
/*
    ʹ�ü̳�ʵ��������ģʽ
*/
#include "adapter_comb.h"

class StackEx: public  Sequence, private Deque
{
public:
    void Push(int x) override;
    void Pop() override;
};

class QueueEx : public  Sequence, private Deque
{
public:
    void Push(int x) override;
    void Pop() override;
};
