#include "tcp_server.h"

int CTcpServer::InitServer(int nPort)
{
    //创建套接字
    m_nListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_nListenSock == INVALID_SOCKET)
    {
        LOGY_DEBUG("create socket failed,port = %d\n", nPort);
        return Y_Ret_Failed;
    }

    //绑定IP和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;

    if(bind(m_nListenSock, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        LOGY_DEBUG("bind error !port = %d\n", nPort);
    }

    //开始监听
    if(listen(m_nListenSock, 5) == SOCKET_ERROR)
    {
        LOGY_DEBUG("listen error !port = %d\n", nPort);
        return 0;
    }

    LOGY_DEBUG("listen success, port = %d\n", nPort);

    #if 0
    //循环接收数据
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];

    while(true)
    {
        LOGY_DEBUG("wiat client connect...\n");
        sClient = accept(m_nListenSock, (SOCKADDR*)&remoteAddr, &nAddrlen);

        if(sClient == INVALID_SOCKET)
        {
            LOGY_DEBUG("accept error !\n");
            continue;
        }

        LOGY_DEBUG("recv connent ip = %s\n", inet_ntoa(remoteAddr.sin_addr));

        //接收数据
        int ret = recv(sClient, revData, 255, 0);

        if(ret > 0)
        {
            revData[ret] = 0x00;
            LOGY_DEBUG(revData);
            LOGY_DEBUG("\n");
        }

        //发送数据
        const char* sendData = "hello,TCP client\n";
        send(sClient, sendData, strlen(sendData), 0);
        closesocket(sClient);
    }

    #endif
    return Y_Ret_Ok;
}

int CTcpServer::Select()
{
    int nMaxFd = m_nListenSock;
    fd_set rfds, rset, wfds, wset;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_SET(m_nListenSock, &rfds);//将sListen添加进该集合

    while(true)
    {
        rset = rfds;
        wset = wfds;
        LOGY_DEBUG("wait select...\n");
        int nReady = select(nMaxFd + 1, &rset, &wset, NULL, NULL);
        #if 1

        if(FD_ISSET(m_nListenSock, &rset))
        {
            sockaddr_in addrRemote;
            int nAddrLen = sizeof(addrRemote);
            SOCKET nNewFd = accept(m_nListenSock, (sockaddr*)&addrRemote, &nAddrLen);
            FD_SET(nNewFd, &rfds);
            nMaxFd = (nMaxFd > nNewFd ? nMaxFd : nNewFd);
            LOGY_DEBUG("Clietn %s connected\n", inet_ntoa(addrRemote.sin_addr));

            if(--nReady == 0)
            {
                continue;
            }
        }

        for(int i = m_nListenSock + 1; i <= nMaxFd; ++i)
        {
            if(FD_ISSET(i, &rset))
            {
                char buffer[1024];
                memset(buffer, 0, 1024);
                int nRecev = recv(i, buffer, 1024, 0);

                if(nRecev > 0)
                {
                    LOGY_DEBUG("Received Client Msg:%s\n", buffer);

                    FD_SET(i, &wfds);
                    //send(i, buffer, strlen(buffer), 0);
                }
                else if(nRecev == 0)
                {
                    FD_CLR(i, &rfds);
                    closesocket(i);
                }

                if(--nReady == 0)
                {
                    break;
                }
            }
            else if(FD_ISSET(i, &wset))
            {
                send(i, "3edc4RFV", strlen("3edc4RFV"), 0);
                FD_CLR(i, &wfds);
            }
        }

        #else

        for(int i = 0; i < rset.fd_count; ++i)
        {
            if(m_nListenSock == rset.fd_array[i])
            {
                sockaddr_in addrRemote;
                int nAddrLen = sizeof(addrRemote);
                SOCKET nNewFd = accept(m_nListenSock, (sockaddr*)&addrRemote, &nAddrLen);
                FD_SET(nNewFd, &rfds);
                nMaxFd = (nMaxFd > nNewFd ? nMaxFd : nNewFd);
                LOGY_DEBUG("Clietn %s connected\n", inet_ntoa(addrRemote.sin_addr));
            }
            else
            {
                char buffer[1024];
                memset(buffer, 0, 1024);
                int nRecev = recv(rset.fd_array[i], buffer, 1024, 0);

                if(nRecev > 0)
                {
                    LOGY_DEBUG("Received Client Msg:%s\n", buffer);
                    send(rset.fd_array[i], buffer, strlen(buffer), 0);
                }
                else
                {
                    closesocket(rset.fd_array[i]);
                    FD_CLR(rset.fd_array[i], &rfds);
                }
            }
        }

        #endif
    }

    return Y_Ret_Ok;
}

