#pragma once
/*
    这种单例模式实现方式多线程可能存在不确定性：任何一种non-const static对象，不论它是local或non-local,在多线程环境下“等待某事发生”都会有麻烦。
    解决的方法：在程序的单线程启动阶段手工调用所有reference-returning函数。这种实现方式的好处是不需要去delete它。
*/
class SingletonEx2
{
public:
    static SingletonEx2& GetInstance();
private:
    SingletonEx2() {}
    SingletonEx2(const SingletonEx2&) = delete;  //明确拒绝
    SingletonEx2& operator=(const SingletonEx2&) = delete; //明确拒绝
};


