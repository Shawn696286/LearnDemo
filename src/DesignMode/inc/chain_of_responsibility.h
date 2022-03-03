#pragma once
/*
    ְ����ģʽ��ʹ��������л��ᴦ�����󣬴Ӷ���������ķ����ߺͽ�����֮ǰ����Ϲ�ϵ������Щ��������һ��������������������������ֱ����һ����������Ϊֹ��

    ְ�����ϵĴ����߸��������󣬿ͻ�ֻ��Ҫ�������͵�ְ�����ϼ��ɣ������������Ĵ���ϸ�ں�����Ĵ��ݣ�����ְ����������ķ����ߺ�����Ĵ����߽����ˡ�
*/
/*
    �ؼ����룺Handler��ָ�����ϼ���handleRequest()���ж��Ƿ���ʣ��������򴫵ݸ��ϼ���
*/
#include "public.h"

enum ERequestLevel
{
    Level_1 = 0,
    Level_2,
    Level_3,
    Level_Num,
};

//�������ߣ�Handler����ɫ���ṩ��������ͳһ�ӿ�
class ILeader
{
public:
    ILeader(ILeader* pLeader): m_pLeader(pLeader) {}
    virtual ~ILeader() {}
    virtual void HandleRequest(ERequestLevel eLevel) = 0;
protected:
    ILeader* m_pLeader;
};

//���崦���ߣ�Concrete Handler����ɫ
class CMonitor: public ILeader //����1
{
public:
    CMonitor(ILeader* pLeader): ILeader(pLeader) {}
    void HandleRequest(ERequestLevel eLevel) override;
};

//���崦���ߣ�Concrete Handler����ɫ
class CCaptain : public ILeader //����2
{
public:
    CCaptain(ILeader* pLeader) : ILeader(pLeader) {}
    void HandleRequest(ERequestLevel eLevel) override;
};

//���崦���ߣ�Concrete Handler����ɫ
class CGeneral : public ILeader //����3
{
public:
    CGeneral(ILeader* pLeader) : ILeader(pLeader) {}
    void HandleRequest(ERequestLevel eLevel) override;
};
