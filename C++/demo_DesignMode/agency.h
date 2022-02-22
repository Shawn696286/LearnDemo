#pragma once
/*
    �ؼ����룺һ������������Ҫ���ʵĶ���(Ŀ����)��һ���Ǵ������,����������������ʵ��ͬһ���ӿ�,�ȷ��ʴ���*         ���ٷ�������Ҫ���ʵĶ���
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
