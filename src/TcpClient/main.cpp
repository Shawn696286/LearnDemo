// C++.cpp: 定义应用程序的入口点。
//
#include <sstream>
#include "tcp_client.h"
#include <list>
#include <stdio.h>
using namespace std;

static int MAX_CONNECT_SIZE = 2000;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        MAX_CONNECT_SIZE = atoi(argv[1]);
    }

    std::list<shared_ptr<CTcpClient>> listClient;
    int nNo = 1;
    string strDstIp = "192.168.1.7";
    int nDstPort = 12346;

    while(nNo++ < MAX_CONNECT_SIZE)
    {
        auto pClient = make_shared<CTcpClient>();

        if(Y_Ret_Ok != pClient->InitClient(strDstIp.c_str(), nDstPort))
        {
            LOGY_DEBUG("connect server failed.ip = %s,port = %d", strDstIp.c_str(), nDstPort);
            continue;
        }

        LOGY_DEBUG("connect server success.ip = %s,port = %d,conut = %d", strDstIp.c_str(), nDstPort, nNo);

        pClient->Send("qwertyuiop");

    }

    while(true)
    {
        sleep(200);
    }

    return 0;
}
