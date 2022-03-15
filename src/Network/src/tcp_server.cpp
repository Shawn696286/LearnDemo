#include "tcp_server.h"

int CTcpServer::InitServer(int nPort)
{
    //创建套接字
    m_nListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_nListenSock == INVALID_SOCKET)
    {
        printf("create socket failed,port = %d\n", nPort);
        return Y_Ret_Failed;
    }

    //绑定IP和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;

    if(bind(m_nListenSock, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !port = %d\n", nPort);
    }

    //开始监听
    if(listen(m_nListenSock, 5) == SOCKET_ERROR)
    {
        printf("listen error !port = %d\n", nPort);
        return 0;
    }

    //循环接收数据
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];

    while(true)
    {
        printf("wiat client connect...\n");
        sClient = accept(m_nListenSock, (SOCKADDR*)&remoteAddr, &nAddrlen);

        if(sClient == INVALID_SOCKET)
        {
            printf("accept error !\n");
            continue;
        }

        printf("recv connent ip = %s\n", inet_ntoa(remoteAddr.sin_addr));

        //接收数据
        int ret = recv(sClient, revData, 255, 0);

        if(ret > 0)
        {
            revData[ret] = 0x00;
            printf(revData);
            printf("\n");
        }

        //发送数据
        const char* sendData = "hello,TCP client\n";
        send(sClient, sendData, strlen(sendData), 0);
        closesocket(sClient);
    }

    return Y_Ret_Ok;
}
