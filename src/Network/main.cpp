// C++.cpp: 定义应用程序的入口点。
//
#include <sstream>
#include "tcp_client.h"
#include "tcp_server.h"
#include "tcp_reactor.h"
using namespace std;

int main()
{
    #if 0
    CTcpClient oClient;
    oClient.InitClient("127.0.0.1", 12345);
    oClient.Send("qwertyuiop");
    #elif 0
    CTcpServer oServer;
    oServer.InitServer(12346);
    oServer.Select();
    #else
    CTcpServer oServer;
    CTcpReactor oReactor;
    oServer.InitServer(12346);
    //oServer.Epoll();
    oReactor.InitReactor(oServer.GetListenFd());
    oReactor.Worker();
    #endif

    return 0;
}
