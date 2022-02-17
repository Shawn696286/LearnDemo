// demo_DesignMode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//设计模式
#include <iostream>
#include "public.h"


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "param count error!\n";
        return -1;
    }

    std::string strCmdType = argv[1];

    if("1" == strCmdType)
    {
        test_simple_factory_mode();
    }
    else if("2" == strCmdType)
    {
        test_factory_mode();
    }
    else if("3" == strCmdType)
    {
        test_abstract_factory_mode();
    }
    else if("4" == strCmdType)
    {
        test_strategy_mode();
    }
    else if("5" == strCmdType)
    {
        test_strategy_by_funcction_mode();
    }
    else if("6" == strCmdType)
    {
        test_adapter_comb_mode();
    }
    else if("7" == strCmdType)
    {
        test_adapter_derive_mode();
    }
    else
    {
        std::cout << "param error!\n";
    }

    return 0;
}
