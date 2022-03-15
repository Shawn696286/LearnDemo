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
    //< 接收缓存
    char* m_pBuf;

    //< 接收缓存数据大小
    int m_nBufSSize;
};
