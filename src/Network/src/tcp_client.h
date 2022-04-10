#pragma once
#include "netbase.h"

class CTcpClient: public CNetBase
{
public:
    CTcpClient();
    ~CTcpClient() {}
    //< ��ʼ��tcp�ͻ���
    int InitClient(std::string strIp, int nPort);

    //< �ͻ��˷�����Ϣ
    int Send(std::string strMsg);

    //< �ر�Tcp�ͻ���
    int CloseClient();
private:
    //< �ͻ��˽�����Ϣ
    int OnRecv(std::string strMsg);

private:
    //< ����sock
    SOCKET m_nSock;

    //< ���ӿͻ���ip
    std::string m_strIp;

    //< ���ӿͻ���port
    int m_nPort;
};
