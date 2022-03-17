#pragma once
#include "windows_net.h"

//< ���ջ����С
const int MAX_RECV_BUF = 1024 * 10;

//< epoll ����¼���
const int MAX_POLL_SIZE = 1024;

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
