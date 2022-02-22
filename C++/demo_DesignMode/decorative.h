#pragma once
/*
    �ؼ����룺1��Component ��䵱�����ɫ����Ӧ�þ���ʵ�֡� 2�����������úͼ̳� Component �࣬������չ����д���෽����
*/

//���󹹼���Component����ɫ������һ������ӿڣ��Թ淶׼�����ո������εĶ���
#include "public.h"
class IComponent
{
public:
    virtual ~IComponent() {}
    virtual void Configuration() = 0;
};

//���幹����Concrete Component����ɫ������һ����Ҫ���ո������ε��ࡣ
class CCar: public IComponent
{
public:
    void Configuration() override;
};

//װ�Σ�Decorator����ɫ������һ��������Component�������ʵ������ʵ��һ������󹹼��ӿ�һ�µĽӿڡ�
class CDecorateCar: public IComponent
{
public:
    CDecorateCar(IComponent* pCar);
    void Configuration() override;
private:
    IComponent* m_pCar;
};

//����װ�Σ�Concrete Decorator����ɫ�����������������Ӹ��ӵ�����
class CDecorateLED: public CDecorateCar
{
public:
    CDecorateLED(IComponent* pCar);
    void Configuration() override;
private:
    void AddLED();
};

//����װ�Σ�Concrete Decorator����ɫ�������������������ϸ��ӵ����Ρ�
class CDecoratePC: public CDecorateCar
{
public:
    CDecoratePC(IComponent* pCar);
    void Configuration() override;
private:
    void AddPC();
};

//����װ�Σ�Concrete Decorator����ɫ�������������������ϸ��ӵ����Ρ�
class CDecorateEPB : public CDecorateCar
{
public:
    CDecorateEPB(IComponent* pCar);
    void Configuration() override;
private:
    void AddEPB();
};
