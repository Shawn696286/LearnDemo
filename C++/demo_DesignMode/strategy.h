#pragma once
/*
    ��ͳ����ģʽ

    �ؼ����룺ʵ��ͬһ���ӿڡ�

    ���´���ʵ���У�����Ϸ��ɫ��ͬ�Ĺ�����ʽΪ��ͬ�Ĳ��ԣ���Ϸ��ɫ��Ϊִ�в�ͬ���ԵĻ�����ɫ��
*/
#include "public.h"

//��������࣬�ṩһ���ӿ�
class Hurt
{
public:
    virtual void Blood() = 0;
};

//����Ĳ���ʵ���࣬����ʵ�ֽӿڣ�Adc������ͨ����
class AdcHurt: public Hurt
{
public:
    void Blood() override;
};

//����Ĳ���ʵ���࣬����ʵ�ֽӿڣ�Apc���ܹ���
class ApcHurt : public Hurt
{
public:
    void Blood() override;
};

//������ɫ�࣬��Ϸ��ɫսʿ������һ��������ָ�����
class Soldier
{
public:
    Soldier(Hurt* pHurt);
    //�ڲ�ͬ�����£�����Ϸ��ɫ���ֳ���ͬ�Ĺ���
    void Attack();
private:
    Hurt* m_pHurt;
};

//������Ա�ǩ
enum HurtType
{
    Hurt_Type_Adc,
    Hurt_Type_Apc,
    Hurt_Type_Num
};

//������ɫ�࣬��Ϸ��ɫ��ʦ������һ�����Ա�ǩ����
class Mage
{
public:
    Mage(HurtType eType);
    ~Mage();
    void Attack();
private:
    Hurt* m_pHurt;
};

//������ɫ�࣬��Ϸ��ɫ�����֣�ʵ��ģ�崫�ݲ���
template<typename T>
class Archer
{
public:
    void Attack()
    {
        m_hurt.Blood();
    }
private:
    T m_hurt;
};
