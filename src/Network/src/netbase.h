#pragma once
#include "windows_net.h"


class CNetBase
{
public:
    CNetBase();

    virtual ~CNetBase();
protected:
    //< ���ջ���
    char* m_pBuf;

    //< ���ջ������ݴ�С
    int m_nBufSSize;
};
