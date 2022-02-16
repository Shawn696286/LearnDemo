#pragma once
/*
    使用函数指针实现策略模式
*/
#include "public.h"
void AdcHurtEx();

void ApcHurtEx();

//环境角色类，使用传统的函数指针
class SoldierEx
{
public:
    typedef void (*Function)();
    SoldierEx(Function fun);
    void Attack();
private:
    Function m_pFun;
};

//环境角色，使用std::function<>
class MageEx
{
public:
    typedef std::function<void()> Function;
    MageEx(Function fun);
    void Attack();
private:
    Function m_pFun;
};

