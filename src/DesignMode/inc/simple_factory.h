#pragma once
/*
    �򵥹���ģʽ

    ��Ҫ�ص�����Ҫ�ڹ����������жϣ��Ӷ�������Ӧ�Ĳ�Ʒ���������²�Ʒʱ����Ҫ�޸Ĺ����ࡣʹ�ü򵥹���ģʽ������ֻ��Ҫ֪������Ĳ�Ʒ�ͺžͿ��Դ���һ����Ʒ��

    ȱ�㣺�����༯�������в�Ʒ��Ĵ����߼��������Ʒ���ϴ󣬻�ʹ�ù������ķǳ�ӷ�ס�

*/

#include "public.h"

/*
    �ؼ����룺���������ڹ����������
*/

//�����Ʒ������Ϣ
enum Tank_Type
{
    Tank_Type_56,
    Tank_Type_96,
    Tank_Type_Num,
};

//�����Ʒ��
class Tank
{
public:
    virtual ~Tank();
    virtual const string& Type() = 0;
};

//����Ĳ�Ʒ��
class Tank56 : public Tank
{
public:
    Tank56();
    ~Tank56();
    const string& Type() override;
private:
    string m_strType;
};

//����Ĳ�Ʒ��
class Tank96 : public Tank
{
public:
    Tank96();
    ~Tank96();
    const string& Type() override;
private:
    string m_strType;
};

//������
class SimpleTankFactory
{
public:
    //���ݲ�Ʒ��Ϣ��������Ĳ�Ʒ��ʵ��������һ�������Ʒ����
    Tank* CreateTank(Tank_Type type);
};

