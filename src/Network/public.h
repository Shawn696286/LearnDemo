#pragma once
#ifdef _WIN32
    #include<WinSock2.h>
    #include<Windows.h>
    #pragma comment(lib,"ws2_32.lib")
#else
    #include<unistd.h>
    #include<arpa/inet.h>
    #define SOCKET int
    #define INVALID_SOCKET (SOCKET)(~0)
    #define SOCKET_ERROR           (-1)
    #define closesocket close
    //< epoll
    #include <sys/epoll.h>
#endif

#include <map>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <memory>
#include <string.h>

#include "../common/common_def.h"
#include "../../common/inc/logyapi.h"
