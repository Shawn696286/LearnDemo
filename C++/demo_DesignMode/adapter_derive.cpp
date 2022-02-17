#include "adapter_derive.h"

void StackEx::Push(int x)
{
    PushFront(x);
}
void StackEx::Pop()
{
    PopFront();
}
void QueueEx::Push(int x)
{
    PushBack(x);
}
void QueueEx::Pop()
{
    PopFront();
}

