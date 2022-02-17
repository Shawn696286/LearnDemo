#include "public.h"
#include "simple_factory.h"
#include "factory.h"
#include "abstract_factory.h"
#include "strategy.h"
#include "strategy_by_founction.h"
#include "adapter_comb.h"
#include "adapter_derive.h"
#include "singleton_lazy_nosafe.h"

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
    cout << "test_strategy_mode:" << endl;
    Archer<ApcHurt>* arc = new Archer<ApcHurt>;
    arc->Attack();

    delete arc;
    arc = nullptr;
}

void test_strategy_by_funcction_mode()
{
    cout << "test_strategy_by_funcction_mode:" << endl;
    SoldierEx* soldier = new SoldierEx(AdcHurtEx);
    soldier->Attack();
    delete soldier;
    soldier = nullptr;
}

void test_adapter_comb_mode()
{
    cout << "test_adapter_comb_mode:" << endl;
    cout << "queue:" << endl;
    Queue oQueue;
    oQueue.Push(1);
    oQueue.Push(2);
    oQueue.Push(3);
    oQueue.Pop();
    oQueue.Pop();
    oQueue.Pop();

    cout << "stack:" << endl;
    Stack oStack;
    oStack.Push(1);
    oStack.Push(2);
    oStack.Push(3);
    oStack.Pop();
    oStack.Pop();
    oStack.Pop();
}

void test_adapter_derive_mode()
{
    cout << "test_adapter_derive_mode:" << endl;
    cout << "queue:" << endl;
    QueueEx oQueue;
    oQueue.Push(1);
    oQueue.Push(2);
    oQueue.Push(3);
    oQueue.Pop();
    oQueue.Pop();
    oQueue.Pop();

    cout << "stack:" << endl;
    StackEx oStack;
    oStack.Push(1);
    oStack.Push(2);
    oStack.Push(3);
    oStack.Pop();
    oStack.Pop();
    oStack.Pop();
}
void test_singleton_lazy_notsafe_mode()
{
    cout << "test_singleton_lazy_notsafe_mode:" << endl;
    printf("obj:%p,obj:%p\n", Singleton::GetInstance(), Singleton::GetInstance());
}

void test_singleton_lazy_safe_mode()
{

}

void test_singleton_lazy_reference_nosafe_mode()
{

}

void test_singleton_hungry_safe_mode()
{

}

void test_prototype_mode()
{

}

void test_template_mode()
{

}

void test_builder_mode()
{

}

void test_facade_mode()
{

}

void test_composite_mode()
{

}

void test_agency_mode()
{

}

void test_flyweight_mode()
{

}

void test_bridge_mode()
{

}

void test_decorative_mode()
{

}

void test_memo_mode()
{

}

void test_mediator_mode()
{

}

void test_chain_of_responsibility_mode()
{

}

void test_observer_mode()
{

}