#pragma once
/*
    关键代码：树枝内部组合该接口，并且含有内部属性list，里面放Component。
*/
#include "public.h"

//抽象类，提供组合和单个对象的一致接口
class ICompany
{
public:
    ICompany(const string& strName);
    virtual ~ICompany();

    virtual void Add(shared_ptr<ICompany>) = 0;
    virtual void Remove(const string&) = 0;
    virtual void Display(int nDepth) = 0;

    virtual const string& Name();
protected:
    string m_strName;
};

//具体的单个对象实现类，“树枝”类
class CHeadCompany: public ICompany
{
public:
    CHeadCompany(const string& strName);
    virtual ~CHeadCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;;
    void Display(int nDepth) override;
private:
    list<shared_ptr<ICompany>> m_listCompany;
};

//具体的单个对象实现类，“树叶”类
class CResearchCompany: public ICompany
{
public:
    CResearchCompany(const string& strName);
    virtual ~CResearchCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;
    void Display(int nDepth) override;
};

//具体的单个对象实现类，“树叶”类
class CSalesCompany : public ICompany
{
public:
    CSalesCompany(const string& strName);
    virtual ~CSalesCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;
    void Display(int nDepth) override;
};

//具体的单个对象实现类，“树叶”类
class CFinanceCompany : public ICompany
{
public:
    CFinanceCompany(const string& strName);
    virtual ~CFinanceCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;
    void Display(int nDepth) override;
};
