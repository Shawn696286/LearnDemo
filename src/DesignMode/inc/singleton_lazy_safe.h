#pragma once
#include "public.h"

extern mutex g_oMtx;
class SingletonEx
{
public:
    static SingletonEx* GetInstance();
private:
    SingletonEx() {} //构造函数私有
    SingletonEx(const SingletonEx&) = delete;//明确拒绝
    SingletonEx& operator=(const SingletonEx&) = delete;//明确拒绝

    static SingletonEx* m_pSelf;
};

