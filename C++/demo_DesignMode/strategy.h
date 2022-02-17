#pragma once
/*
    传统策略模式

    关键代码：实现同一个接口。

    以下代码实例中，以游戏角色不同的攻击方式为不同的策略，游戏角色即为执行不同策略的环境角色。
*/
#include "public.h"

//抽象策略类，提供一个接口
class Hurt
{
public:
    virtual void Blood() = 0;
};

//具体的策略实现类，具体实现接口，Adc持续普通攻击
class AdcHurt: public Hurt
{
public:
    void Blood() override;
};

//具体的策略实现类，具体实现接口，Apc技能攻击
class ApcHurt : public Hurt
{
public:
    void Blood() override;
};

//环境角色类，游戏角色战士，传入一个策略类指针参数
class Soldier
{
public:
    Soldier(Hurt* pHurt);
    //在不同策略下，该游戏角色表现出不同的攻击
    void Attack();
private:
    Hurt* m_pHurt;
};

//定义策略标签
enum HurtType
{
    Hurt_Type_Adc,
    Hurt_Type_Apc,
    Hurt_Type_Num
};

//环境角色类，游戏角色法师，传入一个策略标签参数
class Mage
{
public:
    Mage(HurtType eType);
    ~Mage();
    void Attack();
private:
    Hurt* m_pHurt;
};

//环境角色类，游戏角色弓箭手，实现模板传递策略
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
