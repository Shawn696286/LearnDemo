#include "tcp_reactor.h"
CTcpReactor::CTcpReactor()
{
    m_bRunning = false;
}

CTcpReactor::~CTcpReactor()
{
}

int CTcpReactor::InitReactor(int nListenFd)
{
    //生成用于处理accept的epoll专用的文件描述符
    m_nEpollFd = epoll_create(5);

    if(m_nEpollFd < 0)
    {
        LOGY_ERROR("epoll_create() failed!!!!!,m_nEpollFd = %d", m_nEpollFd);
    }

    m_nListenFd = nListenFd;
    #ifdef USE_MULTI_CB
    SetEventCallback(m_nListenFd, &CTcpReactor::accept_callback, Accept_Event, NULL);
    #else
    SetEventCallback(m_nListenFd, &CTcpReactor::events_callback, Accept_Event, NULL);
    #endif // USE_MULTI_CB

    m_bRunning = true;
    return Y_Ret_Ok;
}

int CTcpReactor::SetEventCallback(int nFd, event_callback pCb, EEventType nEvent, void* arg)
{
    int nRet = Y_Ret_Ok;
    struct epoll_event oEv = { 0 };
    std::shared_ptr<SEventItem> pEventItem = nullptr;
    {
        std::lock_guard<std::mutex> oGuard(m_oLockMapEvent);
        auto iter = m_mapEvent.find(nFd);

        if(m_mapEvent.end() != iter)
        {
            pEventItem = iter->second;
        }
        else
        {
            pEventItem = std::make_shared<SEventItem>();
            m_mapEvent[nFd] = pEventItem;
        }
    }

    pEventItem->nFd = nFd;
    pEventItem->arg = arg;
    #ifdef USE_MULTI_CB

    switch(nEvent)
    {
        case Read_Event:
            oEv.events = EPOLLIN;
            pEventItem->readcb = pCb;
            break;

        case Write_Event:
            oEv.events = EPOLLOUT;
            pEventItem->writecb = pCb;
            break;

        case Accept_Event:
            oEv.events = EPOLLIN;
            pEventItem->acceptcb = pCb;
            break;

        default:
            break;
    }

    #else
    pEventItem->eventcb = pCb;

    switch(nEvent)
    {
        case Read_Event:
            oEv.events = EPOLLIN;
            break;

        case Write_Event:
            oEv.events = EPOLLOUT;
            break;

        case Accept_Event:
            oEv.events = EPOLLIN;
            break;

        default:
            break;
    }

    #endif // USE_MULTI_CB

    oEv.data.ptr = pEventItem.get();

    if(Nom_Event == pEventItem->eEvent)
    {
        nRet = epoll_ctl(m_nEpollFd, EPOLL_CTL_ADD, pEventItem->nFd, &oEv);

        if(nRet < 0)
        {
            LOGY_ERROR("epoll_ctl EPOLL_CTL_ADD failed, %d", errno);
            nRet = Y_Ret_Error;
        }

        pEventItem->eEvent = Accept_Event;
    }
    else
    {
        nRet = epoll_ctl(m_nEpollFd, EPOLL_CTL_MOD, pEventItem->nFd, &oEv);

        if(nRet < 0)
        {
            LOGY_ERROR("epoll_ctl EPOLL_CTL_MOD failed, %d", errno);
            nRet = Y_Ret_Error;
        }

        pEventItem->eEvent = Accept_Event;
    }

    return nRet;
}

int CTcpReactor::DelEventCallback(int nFd, event_callback pCb, EEventType nEvent, void* arg)
{
    int nRet = Y_Ret_Ok;

    struct epoll_event ev = { 0 };
    ev.data.ptr = arg;

    epoll_ctl(m_nEpollFd, EPOLL_CTL_DEL, nFd, &ev);
    {
        std::lock_guard<std::mutex> oGuard(m_oLockMapEvent);
        m_mapEvent.erase(nFd);
    }
    return nRet;
}

void CTcpReactor::Worker()
{
    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
    struct epoll_event events[MAX_POLL_SIZE] = { 0 };

    while(m_bRunning)
    {
        int nReady = epoll_wait(m_nEpollFd, events, MAX_POLL_SIZE, 5);

        if(nReady == -1)
        {
            continue;
        }

        for(int i = 0; i < nReady; i++)
        {
            SEventItem* item = (SEventItem*)events[i].data.ptr;
            int connfd = item->nFd;
            #ifdef USE_MULTI_CB

            if(connfd == m_nListenFd)     //
            {
                (this->*(item->acceptcb))(m_nListenFd, 0, NULL);
            }
            else
            {
                if(events[i].events & EPOLLIN)     //
                {
                    (this->*(item->readcb))(connfd, 0, NULL);
                }

                if(events[i].events & EPOLLOUT)
                {
                    (this->*(item->writecb))(connfd, 0, NULL);
                }
            }

            #else

            if(connfd == m_nListenFd)     //
            {
                (this->*(item->eventcb))(m_nListenFd, Accept_Event, NULL);
            }
            else
            {
                if(events[i].events & EPOLLIN)     //
                {
                    (this->*(item->eventcb))(connfd, Read_Event, NULL);
                }

                if(events[i].events & EPOLLOUT)
                {
                    (this->*(item->eventcb))(connfd, Write_Event, NULL);
                }
            }

            #endif // USE_MULTI_CB

        }
    }
}

//< 可读回调函数
int CTcpReactor::read_callback(int nFd, int event, void* arg)
{
    std::shared_ptr<SEventItem> pEventItem = nullptr;
    {
        std::lock_guard<std::mutex> oGuard(m_oLockMapEvent);
        auto iter = m_mapEvent.find(nFd);

        if(m_mapEvent.end() == iter)
        {
            return Y_Ret_Error;
        }

        pEventItem = iter->second;
    }
    #if 0//ET
    #else//LT
    int nRet = recv(nFd, pEventItem->pRBuffer, MAX_BUF_SIZE, 0);

    if(nRet == 0)
    {
        DelEventCallback(nFd, NULL, Nom_Event, NULL);
        closesocket(nFd);
    }
    else
    {
        memset(pEventItem->pSBuffer, 0, MAX_BUF_SIZE);
        memcpy(pEventItem->pSBuffer, pEventItem->pRBuffer, nRet);
        pEventItem->nSLen = nRet;

        LOGY_DEBUG("readcb:%s\n", pEventItem->pRBuffer);
        #ifdef USE_MULTI_CB
        SetEventCallback(nFd, &CTcpReactor::write_callback, Write_Event, NULL);
        #else
        SetEventCallback(nFd, &CTcpReactor::events_callback, Write_Event, NULL);
        #endif // USE_MULTI_CB
    }

    #endif
    return Y_Ret_Ok;
}

//< 可写回调函数
int CTcpReactor::write_callback(int nFd, int event, void* arg)
{
    std::shared_ptr<SEventItem> pEventItem = nullptr;
    {
        std::lock_guard<std::mutex> oGuard(m_oLockMapEvent);
        auto iter = m_mapEvent.find(nFd);

        if(m_mapEvent.end() == iter)
        {
            return Y_Ret_Error;
        }

        pEventItem = iter->second;
    }

    int ret = send(nFd, pEventItem->pSBuffer, pEventItem->nSLen, 0);

    if(ret < pEventItem->nSLen)
    {
        #ifdef USE_MULTI_CB
        SetEventCallback(nFd, &CTcpReactor::write_callback, Write_Event, NULL);
        #else
        SetEventCallback(nFd, &CTcpReactor::events_callback, Write_Event, NULL);
        #endif // USE_MULTI_CB
    }
    else
    {
        #ifdef USE_MULTI_CB
        SetEventCallback(nFd, &CTcpReactor::read_callback, Read_Event, NULL);
        #else
        SetEventCallback(nFd, &CTcpReactor::events_callback, Read_Event, NULL);
        #endif // USE_MULTI_CB
    }

    return Y_Ret_Ok;
}

//< accept回调函数
int CTcpReactor::accept_callback(int nFd, int event, void* arg)
{
    sockaddr_in addrRemote;
    int nAddrLen = sizeof(addrRemote);
    #ifdef _WIN32
    SOCKET nNewFd = accept(m_nListenFd, (sockaddr*)&addrRemote, &nAddrLen);
    #else
    SOCKET nNewFd = accept(m_nListenFd, (sockaddr*)&addrRemote, (socklen_t*)&nAddrLen);
    #endif // _WIN32

    if(nNewFd < 0)
    {
        LOGY_ERROR("nNewFd<0");
        return Y_Ret_Error;
    }

    LOGY_DEBUG("Clietn %s:%d connected\n", inet_ntoa(addrRemote.sin_addr), ntohs(addrRemote.sin_port));

    #ifdef USE_MULTI_CB
    SetEventCallback(nNewFd, &CTcpReactor::read_callback, Read_Event, NULL);
    #else
    SetEventCallback(nNewFd, &CTcpReactor::events_callback, Read_Event, NULL);
    #endif // USE_MULTI_CB
    return Y_Ret_Ok;
}

//< event回调函数
int CTcpReactor::events_callback(int nFd, int event, void* arg)
{
    if(event == Accept_Event)
    {
        accept_callback(nFd, event, arg);
    }
    else if(event == Read_Event)
    {
        read_callback(nFd, event, arg);
    }
    else if(event == Write_Event)
    {
        write_callback(nFd, event, arg);
    }

    return Y_Ret_Ok;
}
