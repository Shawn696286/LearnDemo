#pragma once
#include "public.h"
enum ETestType
{
    Test_Type_Nom = 0,
    Test_Type_Thread_Join = 1,
    Test_Type_Thread_Wait,
    Test_Type_Max,
};


//void(CTest::*)()
class CTest
{
public:
    CTest();
    void Worker();

    void test_thread_join();

    void test_thread_wait();
private:
    std::map <std::string, void(CTest::*)()> m_mapStrAndFun;//类成员函数指针
};
