#pragma once
#include <string>
#ifndef UTIL_Y_API
    #define UTIL_Y_API
#endif

enum ETimeFormat
{
    Time_Format_Default,   //默认，yyyy-MM-dd hh:mm:ss.aaa
};

class UTIL_Y_API CUtilY
{
public:
    /***********************************************************************************
        功能：获取当前时间戳（从1970-01-01 00:00:00到当前时间点的时长），单位毫秒
        @param :
        @return： uint64_t                               时间戳，单位毫秒
    ************************************************************************************/
    static uint64_t TimeGetCurrentMilli();

    /***********************************************************************************
        功能：时间戳格式化，
        @param :uint64_t u64Time                        时间戳（从1970-01-01 00:00:00到当前时间点的时长）,单位毫秒
                ETimeFormat eFormat                     格式化格式
        @return： std::string                            时间字符串
    ************************************************************************************/
    static std::string TimeFormat(uint64_t u64Time, ETimeFormat eFormat = Time_Format_Default);
};