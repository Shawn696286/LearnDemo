#include "utily.h"
#include <chrono>
uint64_t CUtilY::TimeGetCurrentMilli()
{
    // ��ȡ��ǰʱ���
    std::chrono::system_clock::time_point time_point_now = std::chrono::system_clock::now();
    // ��1970-01-01 00:00:00����ǰʱ����ʱ��
    std::chrono::system_clock::duration duration_since_epoch = time_point_now.time_since_epoch();
    // ��ʱ��ת��Ϊ΢����
    time_t microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();
    return microseconds_since_epoch / 1000;
}

std::string CUtilY::TimeFormat(uint64_t u64Time, ETimeFormat eFormat)
{
    time_t seconds_since_epoch = u64Time / 1000;    // ��ʱ��ת��Ϊ����
    std::tm* current_time = std::localtime(&seconds_since_epoch);       // ��ȡ��ǰʱ�䣨��ȷ���룩
    time_t tm_millisec = u64Time % 1000;        // ��ǰʱ��ĺ�����
    char pBuf[128] = { 0 };
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