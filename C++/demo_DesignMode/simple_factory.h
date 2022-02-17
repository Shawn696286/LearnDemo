#pragma once
/*
    简单工厂模式

    主要特点是需要在工厂类中做判断，从而创造相应的产品，当增加新产品时，需要修改工厂类。使用简单工厂模式，我们只需要知道具体的产品型号就可以创建一个产品。

    缺点：工厂类集中了所有产品类的创建逻辑，如果产品量较大，会使得工厂类变的非常臃肿。

*/

#include "public.h"

/*
    关键代码：创建工程在工厂类中完成
*/

//定义产品类型信息
enum Tank_Type
{
    Tank_Type_56,
    Tank_Type_96,
    Tank_Type_Num,
};

//抽象产品类
class Tank
{
public:
    virtual ~Tank();
    virtual const string& Type() = 0;
};

//具体的产品类
class Tank56 : public Tank
{
public:
    Tank56();
    ~Tank56();
    const string& Type() override;
private:
    string m_strType;
};

//具体的产品类
class Tank96 : public Tank
{
public:
    Tank96();
    ~Tank96();
    const string& Type() override;
private:
    string m_strType;
};

//工厂类
class SimpleTankFactory
{
public:
    //根据产品信息创建具体的产品类实例，返回一个抽象产品类型
    Tank* CreateTank(Tank_Type type);
};

