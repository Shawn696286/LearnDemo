#include "tcp_server.h"

int CTcpServer::InitServer(int nPort)
{
    //�����׽���
    m_nListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_nListenSock == INVALID_SOCKET)
    {
        LOGY_DEBUG("create socket failed,port = %d\n", nPort);
        return Y_Ret_Error;
    }

    //��socket����Ϊ��������ʽ
    //setnonblocking(listenfd);

    //��IP�Ͷ˿�
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);
    #ifdef _WIN32
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    #else
    sin.sin_addr.s_addr = INADDR_ANY;
    #endif // _WIN32


    if(bind(m_nListenSock, (sockaddr*)&sin, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        LOGY_DEBUG("bind error !port = %d\n", nPort);
    }

    //��ʼ����
    if(listen(m_nListenSock, 5) == SOCKET_ERROR)
    {
        LOGY_DEBUG("listen error !port = %d\n", nPort);
        return 0;
    }

    LOGY_DEBUG("listen success, port = %d\n", nPort);

    #if 0
    //ѭ����������
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

        //��������
        int ret = recv(sClient, revData, 255, 0);

        if(ret > 0)
        {
            revData[ret] = 0x00;
            LOGY_DEBUG(revData);
            LOGY_DEBUG("\n");
        }

        //��������
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
    FD_SET(m_nListenSock, &rfds);//��sListen��ӽ��ü���

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
            #ifdef _WIN32
            SOCKET nNewFd = accept(m_nListenSock, (sockaddr*)&addrRemote, &nAddrLen);
            #else
            SOCKET nNewFd = accept(m_nListenSock, (sockaddr*)&addrRemote, (socklen_t*)&nAddrLen);
            #endif // _WIN32

            if(nNewFd < 0)
            {
                LOGY_ERROR("nNewFd<0");
                continue;
            }

            FD_SET(nNewFd, &rfds);
            nMaxFd = (nMaxFd > nNewFd ? nMaxFd : nNewFd);
            LOGY_DEBUG("Clietn %s:%d connected\n", inet_ntoa(addrRemote.sin_addr), ntohs(addrRemote.sin_port));

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
/*
     1.int epoll_create(int size);
     http://man7.org/linux/man-pages/man2/epoll_create.2.html
     size:    ���ڸ���kernel���ܱ���ӵ�caller�������ں˹�����Ҫ���ٵĿռ�
              2.6.8�����ԣ�kernel���Զ�������Ҫ�Ŀռ䡣���������0�����ݣ���
     return:  epoll��ؾ����һ�����ӵĹ���ֻ��Ҫһ��
    ����һ��epoll�ľ����size���������ں������������Ŀһ���ж�����������ͬ��select()�еĵ�һ��������������������fd+1��ֵ����Ҫע����ǣ���������epoll����������ǻ�ռ��һ��fdֵ����linux������鿴/proc/����id/fd/�����ܹ��������fd�ģ�������ʹ����epoll�󣬱������close()�رգ�������ܵ���fd���ľ���
    2.int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    epoll���¼�ע�ắ��������ͬ��select()���ڼ����¼�ʱ�����ں�Ҫ����ʲô���͵��¼���������������ע��Ҫ�������¼����͡���һ��������epoll_create()�ķ���ֵ���ڶ���������ʾ������������������ʾ��
    EPOLL_CTL_ADD��ע���µ�fd��epfd�У�
    EPOLL_CTL_MOD���޸��Ѿ�ע���fd�ļ����¼���
    EPOLL_CTL_DEL����epfd��ɾ��һ��fd��
    ��������������Ҫ������fd�����ĸ������Ǹ����ں���Ҫ����ʲô��
    events���������¼�����ļ��ϣ�
    EPOLLIN ����ʾ��Ӧ���ļ����������Զ��������Զ�SOCKET�����رգ���
    EPOLLOUT����ʾ��Ӧ���ļ�����������д��
    EPOLLPRI����ʾ��Ӧ���ļ��������н��������ݿɶ�������Ӧ�ñ�ʾ�д������ݵ�������
    EPOLLERR����ʾ��Ӧ���ļ���������������
    EPOLLHUP����ʾ��Ӧ���ļ����������Ҷϣ�
    EPOLLET�� ��EPOLL��Ϊ��Ե����(Edge Triggered)ģʽ�����������ˮƽ����(Level Triggered)��˵�ġ�
    EPOLLONESHOT��ֻ����һ���¼���������������¼�֮���������Ҫ�����������socket�Ļ�����Ҫ�ٴΰ����socket���뵽EPOLL������
    3.int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
    �ȴ��¼��Ĳ�����������select()���á�����events�������ں˵õ��¼��ļ��ϣ�maxevents��֮�ں����events�ж����� maxevents��ֵ���ܴ��ڴ���epoll_create()ʱ��size������timeout�ǳ�ʱʱ�䣨���룬0���������أ�-1����ȷ����Ҳ��˵��˵���������������ú���������Ҫ������¼���Ŀ���緵��0��ʾ�ѳ�ʱ
    4.����ET��LT���ֹ���ģʽ��
    ���Եó������Ľ���:
    ETģʽ����״̬�����仯��ʱ��Ż��֪ͨ,������ν��״̬�ı仯���������������л���δ���������,Ҳ����˵,���Ҫ����ETģʽ,��Ҫһֱread/writeֱ������Ϊֹ,�ܶ��˷�ӳΪʲô����ETģʽֻ������һ�������ݾ���Ҳ�ò���֪ͨ��,�����Ϊ����;��LTģʽ��ֻҪ������û�д���ͻ�һֱ֪ͨ��ȥ��.
    5.��������
    ����ͨ��create_epoll(int maxfds)������һ��epoll�ľ��������maxfdsΪ��epoll��֧�ֵ������������������᷵��һ���µ�epoll�����֮������в�����ͨ�������������в�����������֮�󣬼ǵ���close()���ر��������������epoll�����

    ֮�������������ѭ�����棬ÿһ֡�ĵ���epoll_wait(int epfd, epoll_event events, int max events, int timeout)����ѯ���е�����ӿڣ�����һ�����Զ�����һ������д�ˡ��������﷨Ϊ��
    nfds = epoll_wait(kdpfd, events, maxevents, -1);
    ����kdpfdΪ��epoll_create����֮��ľ����events��һ��epoll_event*��ָ�룬��epoll_wait������������ɹ�֮��epoll_events���潫�������еĶ�д�¼���max_events�ǵ�ǰ��Ҫ����������socket����������һ��timeout�� epoll_wait�ĳ�ʱ��Ϊ0��ʱ���ʾ���Ϸ��أ�Ϊ-1��ʱ���ʾһֱ����ȥ��ֱ�����¼���Χ��Ϊ������������ʱ���ʾ����ô����ʱ�䣬���һֱû���¼�����Χ��һ�����������ѭ���ǵ������̵߳Ļ���������-1���ȣ��������Ա�֤һЩЧ�ʣ�����Ǻ����߼���ͬһ���̵߳Ļ����������0����֤��ѭ����Ч�ʡ�

    epoll_wait��Χ֮��Ӧ����һ��ѭ�����������е��¼���

    �������е�epoll����ʹ������Ŀ�ܣ�
    for( ; ; )
    {
        nfds = epoll_wait(epfd,events,20,500);
        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd) //���µ�����
            {
                connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen); //accept�������
                ev.data.fd=connfd;
                ev.events=EPOLLIN|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev); //���µ�fd��ӵ�epoll�ļ���������
            }
            else if( events[i].events&EPOLLIN ) //���յ����ݣ���socket
            {
                n = read(sockfd, line, MAXLINE)) < 0    //��
                ev.data.ptr = md;     //mdΪ�Զ������ͣ��������
                ev.events=EPOLLOUT|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);//�޸ı�ʶ�����ȴ���һ��ѭ��ʱ�������ݣ��첽����ľ���
            }
            else if(events[i].events&EPOLLOUT) //�����ݴ����ͣ�дsocket
            {
                struct myepoll_data* md = (myepoll_data*)events[i].data.ptr;    //ȡ����
                sockfd = md->fd;
                send( sockfd, md->ptr, strlen((char*)md->ptr), 0 );        //��������
                ev.data.fd=sockfd;
                ev.events=EPOLLIN|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev); //�޸ı�ʶ�����ȴ���һ��ѭ��ʱ��������
            }
            else
            {
                //�����Ĵ���
            }
        }
    }
*/
int CTcpServer::Epoll()
{
    #ifndef _WIN32
    //�������ڴ���accept��epollר�õ��ļ�������
    int nEpollFd = epoll_create(5);

    if(nEpollFd < 0)
    {
        LOGY_ERROR("epoll_create() failed!!!!!");
    }

    struct epoll_event ev;

    ev.events = EPOLLIN | EPOLLET;

    ev.data.fd = m_nListenSock;

    //ע��epoll�¼�
    epoll_ctl(nEpollFd, EPOLL_CTL_ADD, m_nListenSock, &ev);

    //����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�
    struct epoll_event events[MAX_POLL_SIZE] = { 0 };

    while(true)
    {
        int nReady = epoll_wait(nEpollFd, events, MAX_POLL_SIZE, 5);

        for(int i = 0; i < nReady; i++)
        {
            //�¼�⵽һ��SOCKET�û����ӵ��˰󶨵�SOCKET�˿ڣ������µ����ӡ�
            if(events[i].data.fd == m_nListenSock)
            {
                sockaddr_in addrRemote;
                int nAddrLen = sizeof(addrRemote);
                #ifdef _WIN32
                SOCKET nNewFd = accept(m_nListenSock, (sockaddr*)&addrRemote, &nAddrLen);
                #else
                SOCKET nNewFd = accept(m_nListenSock, (sockaddr*)&addrRemote, (socklen_t*)&nAddrLen);
                #endif // _WIN32

                if(nNewFd < 0)
                {
                    LOGY_ERROR("nNewFd<0");
                    continue;
                }

                LOGY_DEBUG("Clietn %s:%d connected\n", inet_ntoa(addrRemote.sin_addr), ntohs(addrRemote.sin_port));

                //�������ڶ��������ļ�������
                ev.data.fd = nNewFd;
                //��������ע��Ķ������¼�
                ev.events = EPOLLIN | EPOLLET;
                //ev.events=EPOLLIN;
                //ע��ev
                epoll_ctl(nEpollFd, EPOLL_CTL_ADD, nNewFd, &ev);
            }
            //������Ѿ����ӵ��û��������յ����ݣ���ô���ж��롣
            else if(events[i].events & EPOLLIN)
            {
                int nClientfd = events[i].data.fd;

                if((nClientfd) < 0)
                {
                    continue;
                }

                char buffer[1024];
                memset(buffer, 0, 1024);
                int nRecev = recv(nClientfd, buffer, 1024, 0);

                if(nRecev > 0)
                {
                    LOGY_DEBUG("Received Client Msg:%s\n", buffer);
                    send(nClientfd, buffer, strlen(buffer), 0);
                }
                else if(nRecev == 0)
                {
                    ev.events = EPOLLIN;
                    ev.data.fd = nClientfd;

                    epoll_ctl(nEpollFd, EPOLL_CTL_DEL, nClientfd, &ev);
                    closesocket(nClientfd);
                }
            }
        }
    }

    #endif // !_WIN32

    return Y_Ret_Ok;
}

int CTcpServer::GetListenFd()
{
    return m_nListenSock;
}