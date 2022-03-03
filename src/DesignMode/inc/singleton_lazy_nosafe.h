#pragma once
/*
    懒汉：故名思义，不到万不得已就不会去实例化类，也就是说在第一次用到类实例的时候才会去实例化一个对象。在访问量较小，甚至可能不会去访问的情况下，采用懒汉实现，这是以时间换空间。
*/
/*
    关键代码：构造函数是私有的，不能通过赋值运算，拷贝构造等方式实例化对象。
*/

//懒汉式一般实现：非线程安全，getInstance返回的实例指针需要delete
class Singleton
{
public:
    static Singleton* GetInstance();
    ~Singleton() {}
private:
    Singleton() {}//构造私有
    Singleton(const Singleton& obj) = delete;//明确拒绝
    Singleton& operator=(const Singleton& obj) = delete;//明确拒绝

    static Singleton* m_pSelf;
};
