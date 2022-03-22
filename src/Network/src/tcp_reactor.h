#pragma once
#include "../public.h"

class CTcpReactor;
typedef int (CTcpReactor::*event_callback)(int fd, int envent, void* arg);

enum EEventType
{
    Nom_Event,
    Read_Event,
    Write_Event,
    Accept_Event
};
struct SEventItem
{
    int nFd;
    EEventType eEvent;
    void* arg;
    event_callback readcb;
    event_callback writecb;
    event_callback acceptcb;
    event_callback eventcb;
    char pSBuffer[MAX_BUF_SIZE];
    int nSLen;
    char pRBuffer[MAX_BUF_SIZE];
    int nRLen;
    SEventItem()
    {
        nFd = 0;
        eEvent = Nom_Event;
        arg = nullptr;
        readcb = nullptr;
        writecb = nullptr;
        acceptcb = nullptr;
        eventcb = nullptr;
        memset(pSBuffer, 0, MAX_BUF_SIZE);
        nSLen = 0;
        memset(pRBuffer, 0, MAX_BUF_SIZE);
        nRLen = 0;
    }
};

class CTcpReactor
{
public:
    CTcpReactor();
    ~CTcpReactor();

    //< 初始化Reactor
    int InitReactor(int nListenFd);

    //< reactor工作函数
    void Worker();
private:
    //< 设置事件回调函数
    int SetEventCallback(int nFd, event_callback pCb, EEventType nEvent, void* arg);

    //< 删除事件回调函数
    int DelEventCallback(int nFd, event_callback pCb, EEventType nEvent, void* arg);

    //< 可读回调函数
    int read_callback(int nFd, int event, void* arg);

    //< 可写回调函数
    int write_callback(int nFd, int event, void* arg);

    //< accept回调函数
    int accept_callback(int nFd, int event, void* arg);

    //< event回调函数
    int events_callback(int nFd, int event, void* arg);
private:
    //< epoll_fd
    int m_nEpollFd;

    //< listen_fd
    int m_nListenFd;

    //< 工作函数工作状态标识
    bool m_bRunning;

    //< 事件对象表
    std::map<int, std::shared_ptr<SEventItem>> m_mapEvent;

    //< 事件对象表锁
    std::mutex m_oLockMapEvent;
};
