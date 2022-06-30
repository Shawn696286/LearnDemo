#pragma once
#include <string>
#ifndef UTIL_Y_API
    #define UTIL_Y_API
#endif

enum ETimeFormat
{
    Time_Format_Default,   //Ĭ�ϣ�yyyy-MM-dd hh:mm:ss.aaa
};

class UTIL_Y_API CUtilY
{
public:
    /***********************************************************************************
        ���ܣ���ȡ��ǰʱ�������1970-01-01 00:00:00����ǰʱ����ʱ��������λ����
        @param :
        @return�� uint64_t                               ʱ�������λ����
    ************************************************************************************/
    static uint64_t TimeGetCurrentMilli();

    /***********************************************************************************
        ���ܣ�ʱ�����ʽ����
        @param :uint64_t u64Time                        ʱ�������1970-01-01 00:00:00����ǰʱ����ʱ����,��λ����
                ETimeFormat eFormat                     ��ʽ����ʽ
        @return�� std::string                            ʱ���ַ���
    ************************************************************************************/
    static std::string TimeFormat(uint64_t u64Time, ETimeFormat eFormat = Time_Format_Default);
};