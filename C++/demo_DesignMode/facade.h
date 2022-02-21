#pragma once
/*
    �ؼ����룺�ͻ���ϵͳ֮���һ����۲㣬��۲㴦��ϵͳ�ĵ��ù�ϵ��������ϵ�ȡ�
    ����ʵ���Ե��Ե���������Ϊ�����ͻ���ֻ���ĵ��Կ����ġ��ػ��Ĺ��̣�������Ҫ�˽�����ڲ���ϵͳ���������̡�
*/
#include "public.h"
//����ؼ��࣬�ṩ�ӿ�
class IControl
{
public:
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
};

//�ӿؼ�������
class CHost: public IControl
{
public:
    void Start() override;
    void Shutdown() override;
};

//�ӿؼ�����ʾ��
class CLcdDisplay: public  IControl
{
public:
    void Start() override;
    void Shutdown() override;
};

//�ӿؼ����ⲿ�豸
class CPeripheral: public IControl
{
public:
    void Start() override;
    void Shutdown() override;
};

class CComputer
{
public:
    void Start();
    void Shutdown();
private:
    CHost m_oHost;
    CLcdDisplay m_oDisplay;
    CPeripheral moPeripheral;
};
