#pragma once
#include "windows_net.h"


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
