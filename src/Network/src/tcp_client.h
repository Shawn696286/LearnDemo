#pragma once
#include "netbase.h"

class CTcpClient: public CNetBase
{
public:
    //< 初始化tcp客户端
    int InitClient(std::string strIp, int nPort);

    //< 客户端发送消息
    int Send(std::string strMsg);
private:
    //< 客户端接收消息
    int OnRecv(std::string strMsg);

private:
    //< 本地sock
    SOCKET m_nSock;

    //< 连接客户端ip
    std::string m_strIp;

    //< 连接客户端port
    int m_nPort;
};
