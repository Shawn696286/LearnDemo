#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "logy.h"

static FILE* g_pFile = nullptr;
static time_t g_loacl_time;
Logy* Logy::m_pSelf = new Logy;
static const int LEN_LOG_STR = 4096;
static const int LEN_TIME_STR = 128;
static char g_log_str[LEN_LOG_STR] = { 0 };
static char g_time_str[LEN_TIME_STR] = { 0 };
static std::mutex g_oLockLogbuf;
static std::mutex g_oLockTimebuf;


Logy* Logy::GetInstance()
{
    return m_pSelf;
}

Logy::Logy()
{
    // 打开日志文件
    g_pFile = fopen("./main.log", "a");

    if(nullptr == g_pFile)
    {
        printf("Logy init failed,fopen failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }
}

Logy::~Logy()
{
}

void Logy::logy(const char* func, const char* file, const int line,
                const char* type, const char* format, ...)
{
    std::string strLog;
    {
        std::lock_guard<std::mutex> oGuard(g_oLockLogbuf);
        memset(g_log_str, 0, LEN_LOG_STR);

        // 日志内容格式转换
        va_list ap;
        va_start(ap, format);
        vsnprintf(g_log_str, LEN_LOG_STR, format, ap);
        va_end(ap);
        strLog = g_log_str;
    }

    // 写入到日志文件中
    if(g_pFile != NULL)
    {
        fprintf(g_pFile, "[%s]%s[%s@%s:%d] %s\n", type, GetLocalTime().c_str(), func,
                file, line, strLog.c_str());
        fflush(g_pFile);
    }
    else
    {
        fprintf(stderr, "[%s]%s[%s@%s:%d] %s\n", type, GetLocalTime().c_str(), func,
                file, line, strLog.c_str());
    }

    printf("[%s]%s[%s@%s:%d] %s\n", type, GetLocalTime().c_str(), func,
           file, line, strLog.c_str());
}

int Logy::WriteFile(std::string)
{
    return 0;
}

std::string Logy::GetLocalTime()
{
    std::lock_guard<std::mutex> oGuard(g_oLockTimebuf);
    memset(g_time_str, 0, LEN_TIME_STR);
    // 获取本地时间
    time(&g_loacl_time);
    strftime(g_time_str, sizeof(g_time_str), "[%Y.%m.%d %X]", localtime(&g_loacl_time));
    return g_time_str;
}



