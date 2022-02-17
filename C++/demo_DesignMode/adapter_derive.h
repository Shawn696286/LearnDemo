#pragma once
/*
    使用继承实现适配器模式
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
