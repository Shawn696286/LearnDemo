#include "strategy_by_founction.h"

void AdcHurtEx()
{
    cout << "Adc Hurt" << endl;
}

void ApcHurtEx()
{
    cout << "Apc Hurt" << endl;
}

SoldierEx::SoldierEx(Function fun)
{
    m_pFun = fun;
}

void SoldierEx::Attack()
{
    m_pFun();
}

MageEx::MageEx(Function fun)
{
    m_pFun = fun;
}

void MageEx::Attack()
{
    m_pFun();
}
