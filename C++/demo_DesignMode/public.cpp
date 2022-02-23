#include "public.h"
#include "simple_factory.h"
#include "factory.h"
#include "abstract_factory.h"
#include "strategy.h"
#include "strategy_by_founction.h"
#include "adapter_comb.h"
#include "adapter_derive.h"
#include "singleton_lazy_nosafe.h"
#include "singleton_lazy_safe.h"
#include "singleton_lazy_reference_nosafe.h"
#include "singleton_hungry_safe.h"
#include "prototype.h"
#include "template_mode.h"
#include "builder.h"
#include "facade.h"
#include "composite.h"
#include "agency.h"
#include "flyweight.h"
#include "bridge.h"
#include "decorative.h"
#include "memo.h"
#include "mediator.h"


map<Mode_Type, FuncTest> g_mapFuncTest;

void test_init()
{
    g_mapFuncTest[Mode_Type_simple_factory] = test_simple_factory_mode;
    g_mapFuncTest[Mode_Type_factory] = test_factory_mode;
    g_mapFuncTest[Mode_Type_abstract_factory] = test_abstract_factory_mode;
    g_mapFuncTest[Mode_Type_strategy_mode] = test_strategy_mode;
    g_mapFuncTest[Mode_Type_strategy_by_funcction] = test_strategy_by_funcction_mode;
    g_mapFuncTest[Mode_Type_adapter_comb] = test_adapter_comb_mode;
    g_mapFuncTest[Mode_Type_adapter_derive] = test_adapter_derive_mode;
    g_mapFuncTest[Mode_Type_singleton_lazy_notsafe] = test_singleton_lazy_notsafe_mode;
    g_mapFuncTest[Mode_Type_singleton_lazy_safe] = test_singleton_lazy_safe_mode;
    g_mapFuncTest[Mode_Type_singleton_lazy_reference_nosafe] = test_singleton_lazy_reference_nosafe_mode;
    g_mapFuncTest[Mode_Type_singleton_hungry_safe] = test_singleton_hungry_safe_mode;
    g_mapFuncTest[Mode_Type_prototype] = test_prototype_mode;
    g_mapFuncTest[Mode_Type_template] = test_template_mode;
    g_mapFuncTest[Mode_Type_builder] = test_builder_mode;
    g_mapFuncTest[Mode_Type_facade] = test_facade_mode;
    g_mapFuncTest[Mode_Type_composite] = test_composite_mode;
    g_mapFuncTest[Mode_Type_agency] = test_agency_mode;
    g_mapFuncTest[Mode_Type_flyweight] = test_flyweight_mode;
    g_mapFuncTest[Mode_Type_bridge] = test_bridge_mode;
    g_mapFuncTest[Mode_Type_decorative] = test_decorative_mode;
    g_mapFuncTest[Mode_Type_memo] = test_memo_mode;
    g_mapFuncTest[Mode_Type_mediator] = test_mediator_mode;
    g_mapFuncTest[Mode_Type_chain_of_responsibility_mode] = test_chain_of_responsibility_mode;
    g_mapFuncTest[Mode_Type_observer] = test_observer_mode;
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
    cout << "test_singleton_lazy_safe_mode:" << endl;
    printf("obj:%p,obj:%p\n", SingletonEx::GetInstance(), SingletonEx::GetInstance());
}

void test_singleton_lazy_reference_nosafe_mode()
{
    cout << "test_singleton_lazy_reference_nosafe_mode:" << endl;
    printf("obj:%p,obj:%p\n", &SingletonEx2::GetInstance(), &SingletonEx2::GetInstance());
}

void test_singleton_hungry_safe_mode()
{
    cout << "test_singleton_hungry_safe_mode:" << endl;
    printf("obj:%p,obj:%p\n", SingletonHungry::GetInstance(), SingletonHungry::GetInstance());
}

void test_prototype_mode()
{
    cout << "test_prototype_mode:" << endl;
    IClone* s1 = new CSheep(1, "aaa");
    s1->Show();
    IClone* s2 = s1->Clone();
    s2->Show();

    delete s1;
    s1 = nullptr;
    delete s2;
    s2 = nullptr;
}

void test_template_mode()
{
    cout << "test_template_mode:" << endl;
    CComputerB* c1 = new CComputerB;
    c1->Product();

    delete c1;
    c1 = nullptr;
}

void test_builder_mode()
{
    cout << "test_builder_mode:" << endl;
    IOrderBuilder* pBuilder = new CMeatOrderBuilder;
    CDirector* pDiretor = new CDirector(pBuilder);
    pDiretor->Construct();
    COrder* pOrder = pBuilder->GetOrder();
    pOrder->Food();
    pOrder->Drink();

    delete pBuilder;
    pBuilder = nullptr;

    delete pDiretor;
    pDiretor = nullptr;
}

void test_facade_mode()
{
    cout << "test_facade_mode:" << endl;
    CComputer oComputer;
    oComputer.Start();
    oComputer.Shutdown();
}

void test_composite_mode()
{
    cout << "test_composite_mode:" << endl;
    auto headRoot = make_shared<CHeadCompany>("Head Root Company");

    auto childRoot1 = make_shared<CHeadCompany>("Child Company A");
    auto r1 = make_shared<CResearchCompany>("Research Company A");
    auto s1 = make_shared<CSalesCompany>("Sales Company A");
    auto s2 = make_shared<CSalesCompany>("Sales Company B");
    auto f1 = make_shared<CFinanceCompany>("FinanceCompany A");

    childRoot1->Add(r1);
    childRoot1->Add(s1);
    childRoot1->Add(s2);
    childRoot1->Add(f1);

    auto childRoot2 = make_shared<CHeadCompany>("Child Company B");
    auto r2 = make_shared<CResearchCompany>("Research Company B");
    auto s3 = make_shared<CSalesCompany>("Sales Company C");
    auto s4 = make_shared<CSalesCompany>("Sales Company D");
    auto f2 = make_shared<CFinanceCompany>("FinanceCompany B");

    childRoot2->Add(r2);
    childRoot2->Add(s3);
    childRoot2->Add(s4);
    childRoot2->Add(f2);

    headRoot->Add(childRoot1);
    headRoot->Add(childRoot2);
    headRoot->Display(1);

    cout << "\n***************\n" << endl;

    childRoot1->Remove("Sales Company B");
    headRoot->Display(1);

    cout << "\n***************\n" << endl;
}

void test_agency_mode()
{
    cout << "test_agency_mode:" << endl;
    CGril oGril("meilisa");
    CManProxy oProxy = CManProxy(oGril);
    oProxy.Profess();
}

void test_flyweight_mode()
{
    cout << "test_flyweight_mode:" << endl;
    CTrusteeship oTs;
    oTs.Hosting("zhangsan", "computer");
    oTs.Hosting("lisi", "phone");
    oTs.Hosting("wangwu", "watch");

    oTs.Display();

    oTs.Hosting("zhangsan", "TT");
    oTs.Hosting("lisi", "TT");
    oTs.Hosting("wangwu", "TT");

    oTs.Display();
}

void test_bridge_mode()
{
    cout << "test_bridge_mode:" << endl;
    CGameeApp oGaneApp;
    CTranslateApp oTranApp;
    CXiaoMi oXiaoMi;
    CHuaWei oHuaWei;

    oXiaoMi.AppRun(&oGaneApp);
    oXiaoMi.AppRun(&oTranApp);
    oHuaWei.AppRun(&oGaneApp);
    oHuaWei.AppRun(&oTranApp);
}

void test_decorative_mode()
{
    cout << "test_decorative_mode:" << endl;
    CCar oCar;
    CDecorateLED oLedCar(&oCar);
    CDecoratePC oPcCar(&oCar);
    CDecorateEPB oEpbCar(&oCar);

    oLedCar.Configuration();
    oPcCar.Configuration();
    oEpbCar.Configuration();
}

void test_memo_mode()
{
    cout << "test_memo_mode:" << endl;
    SGameValue oV1 = { 0, "Ak", "3K" };
    CGame oGame(oV1);//初始值
    oGame.AddGrade();
    oGame.ShowValue();
    cout << "------------------------------" << endl;
    CCaretake oCare;
    oCare.Save(oGame.SaveValue());//保存当前值
    oGame.AddGrade();//修改当前值
    oGame.ReplaceArm("M16");
    oGame.ReplaceCorps("123");
    oGame.ShowValue();
    cout << "------------------------------" << endl;
    oGame.Load(oCare.Load());//恢复存档
    oGame.ShowValue();
}

void test_mediator_mode()
{
    cout << "test_mediator_mode:" << endl;
    CHouseMediator oHMediato;
    CBuyer oBuyer(&oHMediato);
    CSeller oSeller(&oHMediato);

    oHMediato.SetBuyer(&oBuyer);
    oHMediato.SetSeller(&oSeller);

    oBuyer.SendMessage("Sell not to sell?");
    oSeller.SendMessage("Of course selling?");
}

void test_chain_of_responsibility_mode()
{
    cout << "test_chain_of_responsibility_mode:" << endl;

}

void test_observer_mode()
{
    cout << "test_observer_mode:" << endl;
}