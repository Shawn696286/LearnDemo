#pragma once
/*
    �ؼ����룺������return new className(*this);
*/
#include "public.h"

//�ṩһ�������¡�ࡣ
class IClone
{
public:
    virtual IClone* Clone() = 0;
    virtual void Show() = 0;
};

//�����ʵ����
class CSheep: public IClone
{
public:
    CSheep(int nId, string strName);
    //�ؼ������¡���������� return new CSheep(*this)
    IClone* Clone() override;
    void Show() override;
private:
    int m_nId;
    string m_strName;
};

