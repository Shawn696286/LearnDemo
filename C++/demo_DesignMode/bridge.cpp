#include "bridge.h"
void CGameeApp::Run()
{
    cout << "GameApp Running" << endl;
}

void CTranslateApp::Run()
{
    cout << "TranslateApp Running" << endl;
}

void CXiaoMi::AppRun(IApp* pApp)
{
    cout << "XiaoMi:";
    pApp->Run();
}

void CHuaWei::AppRun(IApp* pApp)
{
    cout << "HuaWei:";
    pApp->Run();
}
