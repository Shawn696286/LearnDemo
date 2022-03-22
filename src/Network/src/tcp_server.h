#pragma once
#include "netbase.h"
// IO��·���ã��¼�����+��������ʵ��һ���߳���ɶԶ��fd�ļ�غ���Ӧ������CPU������
// epoll�ŵ�:
//      1.select��Ҫÿ�ε���selectʱ����fd��epoll_ctl����һ�Σ�epoll_wait�Ͳ���Ҫ�ظ�����
//      2.����Ҫ��select����fd����飬�����Ļᱻ�������list������list��ɴ���
//      3.û������������ƣ�������ļ���Ŀ��أ�cat /proc/sys/fs/file-max�����ڴ����
// epollʵ�����:
//      1.epoll_ctl,��fd��eventʹ��RB tree���棬��дO(logN)��
//      2.һ����event���ں˸�����ӵ�rdlist����
//      3.epoll_wait��������Ƿ����¼��������д���

// Ref
//      https://www.cnblogs.com/lojunren/p/3856290.html
//      http://blog.chinaunix.net/uid-28541347-id-4273856.html

class CTcpServer : public CNetBase
{
public:
    //< ��ʼ��tcp������
    int InitServer(int nPort);

    //< tcp������select
    int Select();

    //< tcp������epoll
    int Epoll();

    //< ��ȡListenFd
    int GetListenFd();
private:
    //< ����sock
    SOCKET m_nListenSock;

};
