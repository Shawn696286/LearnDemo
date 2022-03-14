#include "netbase.h"

CNetBase::CNetBase()
{
    InitNet();
    m_pBuf = new char[MAX_RECV_BUF];
    memset(m_pBuf, 0, MAX_RECV_BUF);
    m_nBufSSize = 0;
}

CNetBase::~CNetBase()
{
    UnInitNet();
    delete []m_pBuf;
}

