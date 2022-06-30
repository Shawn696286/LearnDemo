#include "tcp_server.h"

int CTcpServer::InitServer(int nPort)
{
    //创建套接字
    m_nListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_nListenSock == INVALID_SOCKET)
    {
        LOGY_DEBUG("create socket failed,port = %d\n", nPort);
        return Y_Ret_Error;
    }

    //把socket设置为非阻塞方式
    //setnonblocking(listenfd);

    //绑定IP和端口
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
     size:    用于告诉kernel可能被添加的caller数量，内核估计需要开辟的空间
              2.6.8被忽略，kernel会自动开辟需要的空间。但必须大于0（兼容）。
     return:  epoll相关句柄，一组连接的管理只需要一个
    创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。需要注意的是，当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。
    2.int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    epoll的事件注册函数，它不同与select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。第一个参数是epoll_create()的返回值，第二个参数表示动作，用三个宏来表示：
    EPOLL_CTL_ADD：注册新的fd到epfd中；
    EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
    EPOLL_CTL_DEL：从epfd中删除一个fd；
    第三个参数是需要监听的fd，第四个参数是告诉内核需要监听什么事
    events可以是以下几个宏的集合：
    EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
    EPOLLOUT：表示对应的文件描述符可以写；
    EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
    EPOLLERR：表示对应的文件描述符发生错误；
    EPOLLHUP：表示对应的文件描述符被挂断；
    EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
    EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
    3.int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
    等待事件的产生，类似于select()调用。参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，这个 maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。该函数返回需要处理的事件数目，如返回0表示已超时
    4.关于ET、LT两种工作模式：
    可以得出这样的结论:
    ET模式仅当状态发生变化的时候才获得通知,这里所谓的状态的变化并不包括缓冲区中还有未处理的数据,也就是说,如果要采用ET模式,需要一直read/write直到出错为止,很多人反映为什么采用ET模式只接收了一部分数据就再也得不到通知了,大多因为这样;而LT模式是只要有数据没有处理就会一直通知下去的.
    5.总体流程
    首先通过create_epoll(int maxfds)来创建一个epoll的句柄，其中maxfds为你epoll所支持的最大句柄数。这个函数会返回一个新的epoll句柄，之后的所有操作将通过这个句柄来进行操作。在用完之后，记得用close()来关闭这个创建出来的epoll句柄。

    之后在你的网络主循环里面，每一帧的调用epoll_wait(int epfd, epoll_event events, int max events, int timeout)来查询所有的网络接口，看哪一个可以读，哪一个可以写了。基本的语法为：
    nfds = epoll_wait(kdpfd, events, maxevents, -1);
    其中kdpfd为用epoll_create创建之后的句柄，events是一个epoll_event*的指针，当epoll_wait这个函数操作成功之后，epoll_events里面将储存所有的读写事件。max_events是当前需要监听的所有socket句柄数。最后一个timeout是 epoll_wait的超时，为0的时候表示马上返回，为-1的时候表示一直等下去，直到有事件范围，为任意正整数的时候表示等这么长的时间，如果一直没有事件，则范围。一般如果网络主循环是单独的线程的话，可以用-1来等，这样可以保证一些效率，如果是和主逻辑在同一个线程的话，则可以用0来保证主循环的效率。

    epoll_wait范围之后应该是一个循环，遍利所有的事件。

    几乎所有的epoll程序都使用下面的框架：
    for( ; ; )
    {
        nfds = epoll_wait(epfd,events,20,500);
        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd) //有新的连接
            {
                connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen); //accept这个连接
                ev.data.fd=connfd;
                ev.events=EPOLLIN|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev); //将新的fd添加到epoll的监听队列中
            }
            else if( events[i].events&EPOLLIN ) //接收到数据，读socket
            {
                n = read(sockfd, line, MAXLINE)) < 0    //读
                ev.data.ptr = md;     //md为自定义类型，添加数据
                ev.events=EPOLLOUT|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);//修改标识符，等待下一个循环时发送数据，异步处理的精髓
            }
            else if(events[i].events&EPOLLOUT) //有数据待发送，写socket
            {
                struct myepoll_data* md = (myepoll_data*)events[i].data.ptr;    //取数据
                sockfd = md->fd;
                send( sockfd, md->ptr, strlen((char*)md->ptr), 0 );        //发送数据
                ev.data.fd=sockfd;
                ev.events=EPOLLIN|EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev); //修改标识符，等待下一个循环时接收数据
            }
            else
            {
                //其他的处理
            }
        }
    }
*/
int CTcpServer::Epoll()
{
    #ifndef _WIN32
    //生成用于处理accept的epoll专用的文件描述符
    int nEpollFd = epoll_create(5);

    if(nEpollFd < 0)
    {
        LOGY_ERROR("epoll_create() failed!!!!!");
    }

    struct epoll_event ev;

    ev.events = EPOLLIN | EPOLLET;

    ev.data.fd = m_nListenSock;

    //注册epoll事件
    epoll_ctl(nEpollFd, EPOLL_CTL_ADD, m_nListenSock, &ev);

    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
    struct epoll_event events[MAX_POLL_SIZE] = { 0 };

    while(true)
    {
        int nReady = epoll_wait(nEpollFd, events, MAX_POLL_SIZE, 5);

        for(int i = 0; i < nReady; i++)
        {
            //新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
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

                //设置用于读操作的文件描述符
                ev.data.fd = nNewFd;
                //设置用于注测的读操作事件
                ev.events = EPOLLIN | EPOLLET;
                //ev.events=EPOLLIN;
                //注册ev
                epoll_ctl(nEpollFd, EPOLL_CTL_ADD, nNewFd, &ev);
            }
            //如果是已经连接的用户，并且收到数据，那么进行读入。
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