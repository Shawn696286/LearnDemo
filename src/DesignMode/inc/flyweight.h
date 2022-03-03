#pragma once
/*
    关键代码：将内部状态作为标识，进行共享
*/
#include "public.h"

//抽象享元类，提供享元类外部接口
class IAbstractConsumer
{
public:
    virtual ~IAbstractConsumer() {}
    virtual void SetArticle(const string&) = 0;
    virtual const string& Article() = 0;
};

//具体的享元类
class CConsumer: public  IAbstractConsumer
{
public:
    CConsumer(const string& strName);
    ~CConsumer();
    void SetArticle(const string&) override;
    const string& Article() override;
private:
    string m_strUser;
    string m_strArticle;
};

//享元工厂类
class CTrusteeship
{
public:
    ~CTrusteeship();
    void Hosting(const string& strUser, const string& strArticle);
    void Display();
private:
    map<string, shared_ptr<CConsumer>> m_mapUserAndConsumer;
};

