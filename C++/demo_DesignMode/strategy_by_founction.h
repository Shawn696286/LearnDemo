#pragma once
/*
    ʹ�ú���ָ��ʵ�ֲ���ģʽ
*/
#include "public.h"
void AdcHurtEx();

void ApcHurtEx();

//������ɫ�࣬ʹ�ô�ͳ�ĺ���ָ��
class SoldierEx
{
public:
    typedef void (*Function)();
    SoldierEx(Function fun);
    void Attack();
private:
    Function m_pFun;
};

//������ɫ��ʹ��std::function<>
class MageEx
{
public:
    typedef std::function<void()> Function;
    MageEx(Function fun);
    void Attack();
private:
    Function m_pFun;
};

