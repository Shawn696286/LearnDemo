// C++.cpp: 定义应用程序的入口点。
//
#include <sstream>
#include "tcp_reactor.h"
#include "tcp_server.h"
using namespace std;

int main()
{
    logy_set_logfile_path("./tcp_severver.log");
    CTcpServer oServer;
    CTcpReactor oReactor;
    oServer.InitServer(12346);
    //oServer.Epoll();
    oReactor.InitReactor(oServer.GetListenFd());
    oReactor.Worker();

    return 0;
}
