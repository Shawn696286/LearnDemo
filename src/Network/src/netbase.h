#pragma once
#include "windows_net.h"

//< 接收缓存大小
const int MAX_RECV_BUF = 1024 * 10;

//< epoll 最大事件数
const int MAX_POLL_SIZE = 1024;

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
