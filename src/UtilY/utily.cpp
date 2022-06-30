#include "utily.h"
#include <chrono>
uint64_t CUtilY::TimeGetCurrentMilli()
{
    // 获取当前时间点
    std::chrono::system_clock::time_point time_point_now = std::chrono::system_clock::now();
    // 从1970-01-01 00:00:00到当前时间点的时长
    std::chrono::system_clock::duration duration_since_epoch = time_point_now.time_since_epoch();
    // 将时长转换为微秒数
    time_t microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();
    return microseconds_since_epoch / 1000;
}

std::string CUtilY::TimeFormat(uint64_t u64Time, ETimeFormat eFormat)
{
    time_t seconds_since_epoch = u64Time / 1000;    // 将时长转换为秒数
    std::tm* current_time = std::localtime(&seconds_since_epoch);       // 获取当前时间（精确到秒）
    time_t tm_millisec = u64Time % 1000;        // 当前时间的毫秒数
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