#pragma once
#include "netbase.h"

class CTcpServer : public CNetBase
{
public:
    //< ��ʼ��tcp������
    int InitServer(int nPort);
private:
    //< ����sock
    SOCKET m_nListenSock;
};
