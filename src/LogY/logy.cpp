#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "logy.h"
static FILE* g_pFile = nullptr;
static time_t g_loacl_time;
static std::string g_strLogfilePath = "./main.log";
Logy* Logy::m_pSelf = new Logy;
static const int LEN_LOG_STR = 4096;
static const int LEN_TIME_STR = 128;


Logy* Logy::GetInstance()
{
    return m_pSelf;
}

Logy::Logy()
{
}

Logy::~Logy()
{
}

void Logy::logy(const char* func, const char* file, const int line,
                const char* type, const char* format, ...)
{
    if(!g_pFile)
    {
        // ����־�ļ�
        g_pFile = fopen(g_strLogfilePath.c_str(), "a+");

        if(nullptr == g_pFile)
        {
            printf("Logy init failed,fopen failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }

    std::string strLog;
    char t_log_str[LEN_LOG_STR] = { 0 };

    // ��־���ݸ�ʽת��
    va_list ap;
    va_start(ap, format);
    vsnprintf(t_log_str, LEN_LOG_STR, format, ap);
    va_end(ap);
    strLog = t_log_str;

    // д�뵽��־�ļ���
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

void Logy::logy(const char* func, const char* file, const int line, const char* type, const std::string& strLog)
{
    if(!g_pFile)
    {
        // ����־�ļ�
        g_pFile = fopen(g_strLogfilePath.c_str(), "a+");

        if(nullptr == g_pFile)
        {
            printf("Logy init failed,fopen failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }

    // д�뵽��־�ļ���
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

void Logy::SetLogfilePath(const std::string& strLogfilePath)
{
    g_strLogfilePath = strLogfilePath;
}

std::string Logy::GetLocalTime()
{
    // ��ȡ��ǰʱ���
    std::chrono::system_clock::time_point time_point_now = std::chrono::system_clock::now();
    // ��1970-01-01 00:00:00����ǰʱ����ʱ��
    std::chrono::system_clock::duration duration_since_epoch = time_point_now.time_since_epoch();
    // ��ʱ��ת��Ϊ΢����
    time_t microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();
    time_t seconds_since_epoch = microseconds_since_epoch / 1000000;    // ��ʱ��ת��Ϊ����
    std::tm* current_time = localtime(&seconds_since_epoch);        // ��ȡ��ǰʱ�䣨��ȷ���룩
    //time_t tm_microsec = microseconds_since_epoch % 1000;                 // ��ǰʱ���΢����
    time_t tm_millisec = microseconds_since_epoch / 1000 % 1000;        // ��ǰʱ��ĺ�����
    char pBuf[LEN_TIME_STR] = { 0 };
    sprintf(pBuf, "%d-%02d-%02d %02d:%02d:%02d.%03d",
            (int)current_time->tm_year + 1900,
            (int)current_time->tm_mon + 1,
            (int)current_time->tm_mday,
            (int)current_time->tm_hour,
            (int)current_time->tm_min,
            (int)current_time->tm_sec,
            (int)tm_millisec
           );
    return move(std::string(pBuf));
}
