#pragma once
/*
    �ؼ����룺���ڲ�״̬��Ϊ��ʶ�����й���
*/
#include "public.h"

//������Ԫ�࣬�ṩ��Ԫ���ⲿ�ӿ�
class IAbstractConsumer
{
public:
    virtual ~IAbstractConsumer() {}
    virtual void SetArticle(const string&) = 0;
    virtual const string& Article() = 0;
};

//�������Ԫ��
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

//��Ԫ������
class CTrusteeship
{
public:
    ~CTrusteeship();
    void Hosting(const string& strUser, const string& strArticle);
    void Display();
private:
    map<string, shared_ptr<CConsumer>> m_mapUserAndConsumer;
};

