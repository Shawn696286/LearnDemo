#pragma once
/*
    关键代码：一个是真正的你要访问的对象(目标类)，一个是代理对象,真正对象与代理对象实现同一个接口,先访问代理*         类再访问真正要访问的对象。
*/
#include "public.h"
class CGril
{
public:
    CGril(const string& strName = "girl");
    string GetName();
private:
    string m_strName;
};

class IProfession
{
public:
    virtual ~IProfession() {}
    virtual void Profess() = 0;
};

class CYoungMan: public IProfession
{
public:
    CYoungMan(const CGril& oGril);
    void Profess() override;
private:
    CGril m_oGril;
};

class CManProxy: public IProfession
{
public:
    CManProxy(const CGril& oGril);
    ~CManProxy();
    void Profess() override;
private:
    CYoungMan* m_pMan;
};
