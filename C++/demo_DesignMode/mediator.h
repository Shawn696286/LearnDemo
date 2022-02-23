#pragma once
/*
    �н���ģʽ����һ���н��������װһϵ�еĶ��󽻻����н���ʹ��������Ҫ��ʾ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮ǰ�Ľ�����

    ������������֮ǰ���ڴ����Ĺ�����ϵ����һ������ı䣬������Ҫ������֮�����Ķ��󣬲�������Ӧ�Ĵ��������Ʊػ����ϵͳ��ø��ӣ������������ο��Կ���ʹ���н���ģʽ�������������ڹ�����ϵʱ��
    Ϊ�������һ���н���󣬵�һ������ı�ʱ��ֻ��Ҫ֪ͨ�����н�������������н����֪ͨÿ��������صĶ���
*/
/*
    �ؼ����룺����ض����ͨ�ŷ�װ��һ�����е�������
*/
#include "public.h"
class IMediator;

//����ͬ����
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

//�����н���
class IMediator
{
public:
    virtual ~IMediator() {}
    virtual void SetBuyer(IBusinessMan* pBuyer) = 0;
    virtual void SetSeller(IBusinessMan* pSeller) = 0;
    virtual void Send(const string& strMsg, IBusinessMan* pMan) = 0;
};

//�����ͬ����
class CBuyer: public IBusinessMan
{
public:
    CBuyer(): IBusinessMan() {}
    CBuyer(IMediator* pMediator): IBusinessMan(pMediator) {}
    void SendMessage(const string& strMsg) override;
    void GetMessage(const string& strMsg) override;
};

//�����ͬ����
class CSeller : public IBusinessMan
{
public:
    CSeller() : IBusinessMan() {}
    CSeller(IMediator* pMediator) : IBusinessMan(pMediator) {}
    void SendMessage(const string& strMsg) override;
    void GetMessage(const string& strMsg) override;
};

//�����н���
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
