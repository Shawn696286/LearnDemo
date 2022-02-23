#pragma once
/*
    备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原来保存的状态。

    备忘录模式中需要定义的角色类：

    1.Originator(发起人)：负责创建一个备忘录Memento，用以记录当前时刻自身的内部状态，并可使用备忘录恢复内部状态。Originator可以根据需要决定Memento存储自己的哪些内部状态。

    2.Memento(备忘录)：负责存储Originator对象的内部状态，并可以防止Originator以外的其他对象访问备忘录。备忘录有两个接口：Caretaker只能看到备忘录的窄接口，他只能将备忘录传递给其他对象。
    Originator却可看到备忘录的宽接口，允许它访问返回到先前状态所需要的所有数据。

    3.Caretaker(管理者):负责备忘录Memento，不能对Memento的内容进行访问或者操作。
*/
/*
    关键代码：Memento类、Originator类、Caretaker类；Originator类不与Memento类耦合，而是与Caretaker类耦合。
*/
#include "public.h"

//需要保存的信息
struct SGameValue
{
    int nGrade;
    string strArm;
    string strCorps;
};

//Memento类
class CMemento
{
public:
    CMemento() {}
    CMemento(SGameValue oValue);
    SGameValue GetValue();
private:
    SGameValue m_oGameValue;
};

//Originator类
class CGame
{
public:
    CGame(SGameValue oValue);
    void AddGrade();//等级增加
    void ReplaceArm(string strArm);//更换武器
    void ReplaceCorps(string strCorps);//更换工会
    CMemento SaveValue();//保存当前信息
    void Load(CMemento oMemento);//载入信息
    void ShowValue();
private:
    SGameValue m_oGameValue;
};

//Caretaker类
class CCaretake
{
public:
    void Save(CMemento oMemento);//保存信息
    CMemento Load();//读取已保存的信息
private:
    CMemento m_oMenento;
};
