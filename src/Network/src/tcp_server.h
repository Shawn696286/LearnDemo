#pragma once
#include "netbase.h"
// IO多路复用，事件驱动+非阻塞，实现一个线程完成对多个fd的监控和响应，提升CPU利用率
// epoll优点:
//      1.select需要每次调用select时拷贝fd，epoll_ctl拷贝一次，epoll_wait就不需要重复拷贝
//      2.不需要像select遍历fd做检查，就绪的会被加入就绪list，遍历list完成处理
//      3.没有最大连接限制，与最大文件数目相关：cat /proc/sys/fs/file-max，与内存相关
// epoll实现相关:
//      1.epoll_ctl,将fd的event使用RB tree保存，读写O(logN)；
//      2.一旦有event，内核负责添加到rdlist链表
//      3.epoll_wait检查链表看是否有事件，并进行处理

// Ref
//      https://www.cnblogs.com/lojunren/p/3856290.html
//      http://blog.chinaunix.net/uid-28541347-id-4273856.html

class CTcpServer : public CNetBase
{
public:
    //< 初始化tcp服务器
    int InitServer(int nPort);

    //< tcp服务器select
    int Select();

    //< tcp服务器epoll
    int Epoll();

    //< 获取ListenFd
    int GetListenFd();
private:
    //< 监听sock
    SOCKET m_nListenSock;

};
