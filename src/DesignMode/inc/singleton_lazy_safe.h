#pragma once
#include "public.h"

extern mutex g_oMtx;
class SingletonEx
{
public:
    static SingletonEx* GetInstance();
private:
    SingletonEx() {} //���캯��˽��
    SingletonEx(const SingletonEx&) = delete;//��ȷ�ܾ�
    SingletonEx& operator=(const SingletonEx&) = delete;//��ȷ�ܾ�

    static SingletonEx* m_pSelf;
};

