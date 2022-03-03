#include "adapter_comb.h"

void Deque::PushBack(int x)
{
    cout << "Deque push_back:" << x << endl;

}

void Deque::PushFront(int x)
{
    cout << "Deque push_front:" << x << endl;
}

void Deque::PopBack()
{
    cout << "Deque pop_back" << endl;
}

void Deque::PopFront()
{
    cout << "Deque pop_front" << endl;
}

void Stack::Push(int x)
{
    m_deque.PushFront(x);
}

void Stack::Pop()
{
    m_deque.PopFront();
}

void Queue::Push(int x)
{
    m_deque.PushBack(x);
}

void Queue::Pop()
{
    m_deque.PopFront();
}


