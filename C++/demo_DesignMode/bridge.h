#pragma once
/*
    �ؼ����룺����ʵ����������������������ʵ�ࡣ
    ����ʾ���У�������App�������ֻ�����������ʵ�ָ���App�͸����ֻ��������Žӡ�
*/
#include "public.h"
//����App�࣬�ṩ�ӿ�
class IApp
{
public:
    virtual ~IApp()
    {
        cout << "~IApp()" << endl;
    }
    virtual  void Run() = 0;
};

//�����Appʵ����
class CGameeApp : public IApp
{
public:
    void Run() override;
};

//�����Appʵ����
class CTranslateApp: public IApp
{
public:
    void Run() override;
};

//�����ֻ��࣬�ṩ�ӿ�
class IMobilePhone
{
public:
    virtual ~IMobilePhone()
    {
        cout << "~IMobilePhone()" << endl;
    }
    virtual void AppRun(IApp* pApp) = 0;//ʵ��App���ֻ����Ž�
};

//������ֻ�ʵ����
class CXiaoMi: public IMobilePhone
{
public:
    void AppRun(IApp* pApp) override;
};

//������ֻ�ʵ����
class CHuaWei : public IMobilePhone
{
public:
    void AppRun(IApp* pApp) override;
};
