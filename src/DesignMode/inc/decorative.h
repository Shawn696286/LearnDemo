#pragma once
/*
    关键代码：1、Component 类充当抽象角色，不应该具体实现。 2、修饰类引用和继承 Component 类，具体扩展类重写父类方法。
*/

//抽象构件（Component）角色：给出一个抽象接口，以规范准备接收附加责任的对象
#include "public.h"
class IComponent
{
public:
    virtual ~IComponent() {}
    virtual void Configuration() = 0;
};

//具体构件（Concrete Component）角色：定义一个将要接收附加责任的类。
class CCar: public IComponent
{
public:
    void Configuration() override;
};

//装饰（Decorator）角色：持有一个构件（Component）对象的实例，并实现一个与抽象构件接口一致的接口。
class CDecorateCar: public IComponent
{
public:
    CDecorateCar(IComponent* pCar);
    void Configuration() override;
private:
    IComponent* m_pCar;
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加附加的责任
class CDecorateLED: public CDecorateCar
{
public:
    CDecorateLED(IComponent* pCar);
    void Configuration() override;
private:
    void AddLED();
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class CDecoratePC: public CDecorateCar
{
public:
    CDecoratePC(IComponent* pCar);
    void Configuration() override;
private:
    void AddPC();
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class CDecorateEPB : public CDecorateCar
{
public:
    CDecorateEPB(IComponent* pCar);
    void Configuration() override;
private:
    void AddEPB();
};
