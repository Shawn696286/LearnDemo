#pragma once
#include "netbase.h"

class CTcpServer : public CNetBase
{
public:
    //< ��ʼ��tcp������
    int InitServer(int nPort);

    //< tcp������select
    int Select();
private:
    //< ����sock
    SOCKET m_nListenSock;
};
