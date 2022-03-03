#include "builder.h"

void COrder::SetFood(const string& strFood)
{
    m_strFood = strFood;
}

void COrder::SetDrink(const string& strDrink)
{
    m_strDrink = strDrink;
}

const string& COrder::Food()
{
    cout << m_strFood.data() << endl;
    return m_strFood;
}

const string& COrder::Drink()
{
    cout << m_strDrink.data() << endl;
    return m_strDrink;
}

IOrderBuilder::~IOrderBuilder()
{
    cout << "~IOrderBuilder()" << endl;
}

CVegetarianOrderBuilder::CVegetarianOrderBuilder()
{
    m_pOrder = new COrder;
}

CVegetarianOrderBuilder::~CVegetarianOrderBuilder()
{
    cout << "~CVegetarianOrderBuilder()" << endl;
    delete m_pOrder;
    m_pOrder = nullptr;
}

void CVegetarianOrderBuilder::SetOrderFood()
{
    m_pOrder->SetFood("vegetable salad");
}

void CVegetarianOrderBuilder::SetOrderDrink()
{
    m_pOrder->SetDrink("water");
}

COrder* CVegetarianOrderBuilder::GetOrder()
{
    return m_pOrder;
}

CMeatOrderBuilder::CMeatOrderBuilder()
{
    m_pOrder = new COrder;
}

CMeatOrderBuilder::~CMeatOrderBuilder()
{
    cout << "~CMeatOrderBuilder()" << endl;
    delete m_pOrder;
    m_pOrder = nullptr;
}

void CMeatOrderBuilder::SetOrderFood()
{
    m_pOrder->SetFood("beef");
}

void CMeatOrderBuilder::SetOrderDrink()
{
    m_pOrder->SetDrink("beer");
}

COrder* CMeatOrderBuilder::GetOrder()
{
    return m_pOrder;
}

CDirector::CDirector(IOrderBuilder* builder)
{
    m_pOrderBuilder = builder;
}

void CDirector::Construct()
{
    m_pOrderBuilder->SetOrderFood();
    m_pOrderBuilder->SetOrderDrink();
}

