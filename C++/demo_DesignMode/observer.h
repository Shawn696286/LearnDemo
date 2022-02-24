#pragma once
/*
    关键代码：在目标类中增加一个ArrayList来存放观察者们。
*/
#include "public.h"

class IView;

//被观察者抽象类   数据模型
class IDataModel
{
public:
    virtual ~IDataModel() {}
    virtual void AddView(shared_ptr<IView> pView) = 0;
    virtual void RemoveView(shared_ptr<IView> pView) = 0;
    virtual void Notify() = 0;//通知函数
};

//观察者抽象类    视图
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

//具体的被观察类，整数模型
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

//具体的观察者类   表视图
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
