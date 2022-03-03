#pragma once
/*
    关键代码：拷贝，return new className(*this);
*/
#include "public.h"

//提供一个抽象克隆类。
class IClone
{
public:
    virtual IClone* Clone() = 0;
    virtual void Show() = 0;
};

//具体的实现类
class CSheep: public IClone
{
public:
    CSheep(int nId, string strName);
    //关键代码克隆函数，返回 return new CSheep(*this)
    IClone* Clone() override;
    void Show() override;
private:
    int m_nId;
    string m_strName;
};

