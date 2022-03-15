#pragma once
#include "netbase.h"

class CTcpServer : public CNetBase
{
public:
    //< 初始化tcp服务器
    int InitServer(int nPort);

    //< tcp服务器select
    int Select();
private:
    //< 监听sock
    SOCKET m_nListenSock;
};
