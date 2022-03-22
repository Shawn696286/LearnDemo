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
#include <functional>

#include "../common/common_def.h"
#include "../../common/inc/logyapi.h"

//< 缓存大小
const int MAX_BUF_SIZE = 1024;

//< 接收缓存大小
const int MAX_RECV_BUF = 1024 * 10;

//< epoll 最大事件数
const int MAX_POLL_SIZE = 1024;