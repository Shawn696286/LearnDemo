#pragma once
/*
    �ؼ����룺��֦�ڲ���ϸýӿڣ����Һ����ڲ�����list�������Component��
*/
#include "public.h"

//�����࣬�ṩ��Ϻ͵��������һ�½ӿ�
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

//����ĵ�������ʵ���࣬����֦����
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

//����ĵ�������ʵ���࣬����Ҷ����
class CResearchCompany: public ICompany
{
public:
    CResearchCompany(const string& strName);
    virtual ~CResearchCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;
    void Display(int nDepth) override;
};

//����ĵ�������ʵ���࣬����Ҷ����
class CSalesCompany : public ICompany
{
public:
    CSalesCompany(const string& strName);
    virtual ~CSalesCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;
    void Display(int nDepth) override;
};

//����ĵ�������ʵ���࣬����Ҷ����
class CFinanceCompany : public ICompany
{
public:
    CFinanceCompany(const string& strName);
    virtual ~CFinanceCompany();

    void Add(shared_ptr<ICompany>) override;
    void Remove(const string&) override;
    void Display(int nDepth) override;
};
