#pragma once
/*
    ����¼ģʽ���ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڸö���֮�Ᵽ�����״̬�������Ժ�Ϳ��Խ��ö���ָ���ԭ�������״̬��

    ����¼ģʽ����Ҫ����Ľ�ɫ�ࣺ

    1.Originator(������)�����𴴽�һ������¼Memento�����Լ�¼��ǰʱ��������ڲ�״̬������ʹ�ñ���¼�ָ��ڲ�״̬��Originator���Ը�����Ҫ����Memento�洢�Լ�����Щ�ڲ�״̬��

    2.Memento(����¼)������洢Originator������ڲ�״̬�������Է�ֹOriginator���������������ʱ���¼������¼�������ӿڣ�Caretakerֻ�ܿ�������¼��խ�ӿڣ���ֻ�ܽ�����¼���ݸ���������
    Originatorȴ�ɿ�������¼�Ŀ�ӿڣ����������ʷ��ص���ǰ״̬����Ҫ���������ݡ�

    3.Caretaker(������):������¼Memento�����ܶ�Memento�����ݽ��з��ʻ��߲�����
*/
/*
    �ؼ����룺Memento�ࡢOriginator�ࡢCaretaker�ࣻOriginator�಻��Memento����ϣ�������Caretaker����ϡ�
*/
#include "public.h"

//��Ҫ�������Ϣ
struct SGameValue
{
    int nGrade;
    string strArm;
    string strCorps;
};

//Memento��
class CMemento
{
public:
    CMemento() {}
    CMemento(SGameValue oValue);
    SGameValue GetValue();
private:
    SGameValue m_oGameValue;
};

//Originator��
class CGame
{
public:
    CGame(SGameValue oValue);
    void AddGrade();//�ȼ�����
    void ReplaceArm(string strArm);//��������
    void ReplaceCorps(string strCorps);//��������
    CMemento SaveValue();//���浱ǰ��Ϣ
    void Load(CMemento oMemento);//������Ϣ
    void ShowValue();
private:
    SGameValue m_oGameValue;
};

//Caretaker��
class CCaretake
{
public:
    void Save(CMemento oMemento);//������Ϣ
    CMemento Load();//��ȡ�ѱ������Ϣ
private:
    CMemento m_oMenento;
};
