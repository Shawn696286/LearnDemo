#pragma once
/*
    职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之前的耦合关系，将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。

    职责链上的处理者负责处理请求，客户只需要将请求发送到职责链上即可，无需关心请求的处理细节和请求的传递，所有职责链将请求的发送者和请求的处理者解耦了。
*/
/*
    关键代码：Handler内指明其上级，handleRequest()里判断是否合适，不合适则传递给上级。
*/
#include "public.h"

enum ERequestLevel
{
    Level_1 = 0,
    Level_2,
    Level_3,
    Level_Num,
};

//抽象处理者（Handler）角色，提供责任链的统一接口
class ILeader
{
public:
    ILeader(ILeader* pLeader): m_pLeader(pLeader) {}
    virtual ~ILeader() {}
    virtual void HandleRequest(ERequestLevel eLevel) = 0;
protected:
    ILeader* m_pLeader;
};

//具体处理者（Concrete Handler）角色
class CMonitor: public ILeader //链扣1
{
public:
    CMonitor(ILeader* pLeader): ILeader(pLeader) {}
    void HandleRequest(ERequestLevel eLevel) override;
};

//具体处理者（Concrete Handler）角色
class CCaptain : public ILeader //链扣2
{
public:
    CCaptain(ILeader* pLeader) : ILeader(pLeader) {}
    void HandleRequest(ERequestLevel eLevel) override;
};

//具体处理者（Concrete Handler）角色
class CGeneral : public ILeader //链扣3
{
public:
    CGeneral(ILeader* pLeader) : ILeader(pLeader) {}
    void HandleRequest(ERequestLevel eLevel) override;
};
