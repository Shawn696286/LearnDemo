#pragma once
#include "public.h"
#include "windows_net.h"
const int MAX_RECV_BUF = 1024 * 10;
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
