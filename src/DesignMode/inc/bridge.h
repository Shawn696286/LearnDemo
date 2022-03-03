#pragma once
/*
    关键代码：将现实独立出来，抽象类依赖现实类。
    以下示例中，将各类App、各类手机独立开来，实现各种App和各种手机的自由桥接。
*/
#include "public.h"
//抽象App类，提供接口
class IApp
{
public:
    virtual ~IApp()
    {
        cout << "~IApp()" << endl;
    }
    virtual  void Run() = 0;
};

//具体的App实现类
class CGameeApp : public IApp
{
public:
    void Run() override;
};

//具体的App实现类
class CTranslateApp: public IApp
{
public:
    void Run() override;
};

//抽象手机类，提供接口
class IMobilePhone
{
public:
    virtual ~IMobilePhone()
    {
        cout << "~IMobilePhone()" << endl;
    }
    virtual void AppRun(IApp* pApp) = 0;//实现App与手机的桥接
};

//具体的手机实现类
class CXiaoMi: public IMobilePhone
{
public:
    void AppRun(IApp* pApp) override;
};

//具体的手机实现类
class CHuaWei : public IMobilePhone
{
public:
    void AppRun(IApp* pApp) override;
};
