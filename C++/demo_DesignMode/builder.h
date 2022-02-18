#pragma once
#include "public.h"

//具体的产品类
class COrder
{
public:
    void SetFood(const string& strFood);
    const string& Food();
    void SetDrink(const string& strDrink);
    const string& Drink();
private:
    string m_strFood;
    string m_strDrink;
};

//抽象建造类，提供建造类接口
class IOrderBuilder
{
public:
    virtual ~IOrderBuilder();
    virtual void SetOrderFood() = 0;
    virtual void SetOrderDrink() = 0;
    virtual COrder* GetOrder() = 0;
};

//具体的建造类
class CVegetarianOrderBuilder: public IOrderBuilder
{
public:
    CVegetarianOrderBuilder();
    ~CVegetarianOrderBuilder();
    void SetOrderFood() override;
    void SetOrderDrink() override;
    COrder* GetOrder() override;
private:
    COrder* m_pOrder;
};

//具体的建造类
class CMeatOrderBuilder: public  IOrderBuilder
{
public:
    CMeatOrderBuilder();
    ~CMeatOrderBuilder();
    void SetOrderFood() override;
    void SetOrderDrink() override;
    COrder* GetOrder() override;
private:
    COrder* m_pOrder;
};

//CDirector类，负责管理实例创建的依赖关系，指挥构建者类创建实例
class CDirector
{
public:
    CDirector(IOrderBuilder* builder);
    void Construct();
private:
    IOrderBuilder* m_pOrderBuilder;
};
