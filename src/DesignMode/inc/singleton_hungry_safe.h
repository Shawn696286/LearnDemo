#pragma once
/*
    饿汉：饿了肯定要饥不择食。所以在单例类定义的时候就进行实例化。在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间。
*/
class SingletonHungry
{
public:
    static SingletonHungry* GetInstance();
private:
    SingletonHungry() {}//构造函数私有
    SingletonHungry(const SingletonHungry&) = delete;//明确拒绝
    SingletonHungry& operator=(const SingletonHungry&) = delete;//明确拒绝
    static SingletonHungry* m_pSelf;
};

