#pragma once
/*
    �ؼ����룺��Ŀ����������һ��ArrayList����Ź۲����ǡ�
*/
#include "public.h"

class IView;

//���۲��߳�����   ����ģ��
class IDataModel
{
public:
    virtual ~IDataModel() {}
    virtual void AddView(shared_ptr<IView> pView) = 0;
    virtual void RemoveView(shared_ptr<IView> pView) = 0;
    virtual void Notify() = 0;//֪ͨ����
};

//�۲��߳�����    ��ͼ
class IView
{
public:
    virtual ~IView()
    {
        cout << "~IView()" << endl;
    }
    virtual void Update() = 0;
    virtual void SetViewName(string& strName) = 0;
    virtual const string& Name() = 0;
};

//����ı��۲��࣬����ģ��
class CIntDataModel: public IDataModel
{
public:
    ~CIntDataModel()
    {
        m_listPView.clear();
    }
    void AddView(shared_ptr<IView> pView) override;
    void RemoveView(shared_ptr<IView> pView) override;
    void Notify() override;
private:
    list<shared_ptr<IView>>m_listPView;
};

//����Ĺ۲�����   ����ͼ
class CTableView: public IView
{
public:
    CTableView(): m_strName("unknow") {}
    CTableView(const string& strName): m_strName(strName) {}
    ~CTableView()
    {
        cout << "~CTableView():" << m_strName << endl;
    }
    void SetViewName(string& strName) override;
    const string& Name() override;
    void Update() override;
private:
    string m_strName;
};
