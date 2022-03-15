#include "tcp_client.h"

int CTcpClient::InitClient(std::string strIp, int nPort)
{
    // 创建一个TCP的socket
    m_nSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_nSock == INVALID_SOCKET)
    {
        LOGY_DEBUG("create socket failed,ret = %d\n", m_nSock);
        return Y_Ret_Failed;
    }

    //指定连接的服务端信息
    SOCKADDR_IN addrServ;
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(nPort);
    //客户端只需要连接指定的服务器地址，127.0.0.1是本机的回环地址
    addrServ.sin_addr.S_un.S_addr = inet_addr(strIp.c_str());

    // 服务器Bind 客户端是进行连接
    int ret = connect(m_nSock, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));//开始连接

    if(SOCKET_ERROR == ret)
    {
        LOGY_DEBUG("socket connect failed\n");
        closesocket(m_nSock);
        return Y_Ret_Failed;
    }

    return Y_Ret_Ok;
}

int CTcpClient::Send(std::string strMsg)
{
    int nRet = send(m_nSock, strMsg.c_str(), strMsg.size(), 0);

    if(SOCKET_ERROR == nRet)
    {
        LOGY_DEBUG("socket send failed\n");
        return Y_Ret_Failed;
    }

    nRet = recv(m_nSock, m_pBuf, MAX_RECV_BUF - m_nBufSSize, 0);

    if(SOCKET_ERROR == nRet)
    {
        LOGY_DEBUG("socket recv failed\n");
        return Y_Ret_Failed;
    }

    OnRecv(std::string(m_pBuf, nRet));
    return Y_Ret_Ok;
}

int CTcpClient::OnRecv(std::string strMsg)
{
    LOGY_DEBUG("socket recv msg = %s\n", strMsg.c_str());
    return Y_Ret_Ok;
}
