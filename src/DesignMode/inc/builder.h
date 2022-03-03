#pragma once
#include "public.h"

//����Ĳ�Ʒ��
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

//�������࣬�ṩ������ӿ�
class IOrderBuilder
{
public:
    virtual ~IOrderBuilder();
    virtual void SetOrderFood() = 0;
    virtual void SetOrderDrink() = 0;
    virtual COrder* GetOrder() = 0;
};

//����Ľ�����
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

//����Ľ�����
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

//CDirector�࣬�������ʵ��������������ϵ��ָ�ӹ������ഴ��ʵ��
class CDirector
{
public:
    CDirector(IOrderBuilder* builder);
    void Construct();
private:
    IOrderBuilder* m_pOrderBuilder;
};
