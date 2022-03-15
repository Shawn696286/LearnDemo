#pragma once

#ifdef _WIN32
    #include<WinSock2.h>
    #include<Windows.h>
    #pragma comment(lib,"ws2_32.lib")
#endif


#include <map>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <memory>



#include "../common/common_def.h"
