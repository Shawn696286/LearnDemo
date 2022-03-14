#include "windows_net.h"

#ifdef _WIN32
    static int g_nServerCount = 0;
#endif

void InitNet()
{
    #ifdef _WIN32
    ++g_nServerCount;

    if(g_nServerCount == 1)
    {
        WSADATA wsaData;
        WORD w = MAKEWORD(2, 0);//�汾��
        WSAStartup(w, &wsaData); //��̬���ӿ��ʼ��
    }

    #endif
}

void UnInitNet()
{
    #ifdef _WIN32
    --g_nServerCount;

    if(g_nServerCount == 0)
    {
        WSACleanup();
    }

    #endif
}