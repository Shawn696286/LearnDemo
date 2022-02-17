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
    int nCmdType = atoi(strCmdType.c_str());

    switch(nCmdType)
    {
        case Mode_Type_simple_factory:
            test_simple_factory_mode();
            break;

        case Mode_Type_factory:
            test_factory_mode();
            break;

        case Mode_Type_abstract_factory:
            test_abstract_factory_mode();
            break;

        case Mode_Type_strategy_mode:
            test_strategy_mode();
            break;

        case Mode_Type_strategy_by_funcction:
            test_strategy_by_funcction_mode();
            break;

        case Mode_Type_adapter_comb:
            test_adapter_comb_mode();
            break;

        case Mode_Type_adapter_derive:
            test_adapter_derive_mode();
            break;

        case Mode_Type_singleton_lazy_notsafe:
            test_singleton_lazy_notsafe_mode();
            break;

        case Mode_Type_singleton_lazy_safe:
            test_singleton_lazy_safe_mode();
            break;

        case Mode_Type_singleton_lazy_reference_nosafe:
            test_singleton_lazy_reference_nosafe_mode();
            break;

        case Mode_Type_singleton_hungry_safe:
            test_singleton_hungry_safe_mode();
            break;

        case Mode_Type_prototype:
            test_prototype_mode();
            break;

        case Mode_Type_template:
            test_template_mode();
            break;

        case Mode_Type_builder:
            test_builder_mode();
            break;

        case Mode_Type_facade:
            test_facade_mode();
            break;

        case Mode_Type_composite:
            test_composite_mode();
            break;

        case Mode_Type_agency:
            test_agency_mode();
            break;

        case Mode_Type_flyweight:
            test_flyweight_mode();
            break;

        case Mode_Type_bridge:
            test_bridge_mode();
            break;

        case Mode_Type_decorative:
            test_decorative_mode();
            break;

        case Mode_Type_memo:
            test_memo_mode();
            break;

        case Mode_Type_mediator:
            test_mediator_mode();
            break;

        case Mode_Type_chain_of_responsibility_mode:
            test_chain_of_responsibility_mode();
            break;

        case Mode_Type_observer:
            test_observer_mode();
            break;

        default:
            std::cout << "param error!\n";
            break;
    }

    return 0;
}
