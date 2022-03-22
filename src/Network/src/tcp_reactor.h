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

    //< ��ʼ��Reactor
    int InitReactor(int nListenFd);

    //< reactor��������
    void Worker();
private:
    //< �����¼��ص�����
    int SetEventCallback(int nFd, event_callback pCb, EEventType nEvent, void* arg);

    //< ɾ���¼��ص�����
    int DelEventCallback(int nFd, event_callback pCb, EEventType nEvent, void* arg);

    //< �ɶ��ص�����
    int read_callback(int nFd, int event, void* arg);

    //< ��д�ص�����
    int write_callback(int nFd, int event, void* arg);

    //< accept�ص�����
    int accept_callback(int nFd, int event, void* arg);

    //< event�ص�����
    int events_callback(int nFd, int event, void* arg);
private:
    //< epoll_fd
    int m_nEpollFd;

    //< listen_fd
    int m_nListenFd;

    //< ������������״̬��ʶ
    bool m_bRunning;

    //< �¼������
    std::map<int, std::shared_ptr<SEventItem>> m_mapEvent;

    //< �¼��������
    std::mutex m_oLockMapEvent;
};
