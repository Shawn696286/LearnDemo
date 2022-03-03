#pragma once
/*
    中介者模式：用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显示地相互引用，从而使其耦合松散，而且可以独立地改变它们之前的交互。

    如果对象与对象之前存在大量的关联关系，若一个对象改变，常常需要跟踪与之关联的对象，并做出相应的处理，这样势必会造成系统变得复杂，遇到这种情形可以考虑使用中介者模式。当多个对象存在关联关系时，
    为它们设计一个中介对象，当一个对象改变时，只需要通知它的中介对象，再由它的中介对象通知每个与它相关的对象。
*/
/*
    关键代码：将相关对象的通信封装到一个类中单独处理。
*/
#include "public.h"
class IMediator;

//抽象同事类
class IBusinessMan
{
public:
    IBusinessMan() {}
    IBusinessMan(IMediator* pMediator): m_pMediator(pMediator) {}
    virtual ~IBusinessMan() {};
    virtual void SetMediator(IMediator* pM);
    virtual void SendMessage(const string& strMsg) = 0;
    virtual void GetMessage(const string& strMsg) = 0;
protected:
    IMediator* m_pMediator;
};

//抽象中介类
class IMediator
{
public:
    virtual ~IMediator() {}
    virtual void SetBuyer(IBusinessMan* pBuyer) = 0;
    virtual void SetSeller(IBusinessMan* pSeller) = 0;
    virtual void Send(const string& strMsg, IBusinessMan* pMan) = 0;
};

//具体的同事类
class CBuyer: public IBusinessMan
{
public:
    CBuyer(): IBusinessMan() {}
    CBuyer(IMediator* pMediator): IBusinessMan(pMediator) {}
    void SendMessage(const string& strMsg) override;
    void GetMessage(const string& strMsg) override;
};

//具体的同事类
class CSeller : public IBusinessMan
{
public:
    CSeller() : IBusinessMan() {}
    CSeller(IMediator* pMediator) : IBusinessMan(pMediator) {}
    void SendMessage(const string& strMsg) override;
    void GetMessage(const string& strMsg) override;
};

//具体中介类
class CHouseMediator: public IMediator
{
public:
    void SetBuyer(IBusinessMan* pBuyer) override;
    void SetSeller(IBusinessMan* pSeller) override;
    void Send(const string& strMsg, IBusinessMan* pMan) override;
private:
    IBusinessMan* m_pBuyer;
    IBusinessMan* m_pSeller;
};
