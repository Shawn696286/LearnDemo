#pragma once
/*
    ����һ����������Ľӿڣ�������ȥ������ʵ����ӿ�����ɾ���Ĵ��������������Ҫ�����µĲ�Ʒ�ֻ࣬��Ҫ��չһ����Ӧ�Ĺ����༴�ɡ�

    ȱ�㣺��Ʒ�����ݽ϶�ʱ����Ҫʵ�ִ����Ĺ����࣬�����������˴�������
*/
#include "public.h"
#include "simple_factory.h"

/*
    �ؼ����룺����������������ִ��
*/


//���󹤳��࣬�ṩһ�������ӿ�
class TankFactory
{
public:
    virtual ~TankFactory();
    //�ṩ������Ʒʵ���Ľӿڣ����س����Ʒ��
    virtual Tank* CreateTank() = 0;
};

//����Ĵ��������࣬ʹ�ó��󹤳����ṩ�Ľӿڣ�ȥ��������Ĳ�Ʒʵ��
class Tank56Factory : public  TankFactory
{
public:
    ~Tank56Factory();
    Tank* CreateTank() override;
};

//����Ĵ��������࣬ʹ�ó��󹤳����ṩ�Ľӿڣ�ȥ��������Ĳ�Ʒʵ��
class Tank96Factory : public  TankFactory
{
public:
    ~Tank96Factory();
    Tank* CreateTank() override;
};