// demo_DesignMode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//设计模式
#include <iostream>
#include "public.h"
#include "simple_factory.h"
#include "factory.h"
#include "abstract_factory.h"
#include "strategy.h"


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
    else
    {
        std::cout << "param error!\n";
    }

    return 0;
}

void test_simple_factory_mode()
{
    cout << "test_simple_factory_mode:" << endl;
    SimpleTankFactory oFactory;
    Tank* pTank56 = oFactory.CreateTank(Tank_Type_56);
    cout << pTank56->Type() << endl;
    Tank* pTank96 = oFactory.CreateTank(Tank_Type_96);
    cout << pTank96->Type() << endl;

    delete pTank56;
    pTank56 = nullptr;
    delete pTank96;
    pTank96 = nullptr;
}

void test_factory_mode()
{
    cout << "test_factory_mode:" << endl;
    Tank56Factory o56Factor;
    auto pTank56 = o56Factor.CreateTank();
    cout << pTank56->Type() << endl;

    Tank96Factory o96Factor;
    auto pTank96 = o96Factor.CreateTank();
    cout << pTank96->Type() << endl;

    delete pTank56;
    pTank56 = nullptr;

    delete pTank96;
    pTank96 = nullptr;
}

void test_abstract_factory_mode()
{
    cout << "test_abstract_factory_mode:" << endl;
    AbstractFactory* pFactory = new WhiteFactory;
    auto pCoat = pFactory->CreateCoat();
    auto pPants = pFactory->CreatePants();
    cout << pCoat->Color() << "," << pPants->Color() << endl;

    AbstractFactory* pFactory2 = new BlackFactory;
    auto pCoat2 = pFactory2->CreateCoat();
    auto pPants2 = pFactory2->CreatePants();
    cout << pCoat2->Color() << "," << pPants2->Color() << endl;

    delete pFactory;
    pFactory = nullptr;

    delete pCoat;
    pCoat = nullptr;
    delete pPants;
    pPants = nullptr;

    delete pFactory2;
    pFactory2 = nullptr;
    delete pCoat2;
    pCoat2 = nullptr;

    delete pFactory2;
    pFactory2 = nullptr;

}

void test_strategy_mode()
{
    Archer<ApcHurt>* arc = new Archer<ApcHurt>;
    arc->Attack();

    delete arc;
    arc = nullptr;
}