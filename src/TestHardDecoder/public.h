#pragma once
#ifdef _WIN32
    #include "windows.h"
#endif

#include <map>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdint.h>

#ifndef _WIN32
    #include <unistd.h>
#endif // _WIN32

#include "logyapi.h"
#include "utily.h"
#include "yretcode.h"

//< 定义安全释放宏
#define SAFE_DELETE(p)          if(p) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p)    if(p) { delete [] (p); (p) = nullptr; }