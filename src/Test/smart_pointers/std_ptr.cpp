#include "std_ptr.h"

CMyUseSharedPtr* g_pUse = nullptr;
CMySharedThis::CMySharedThis()
{
    printf("CMySharedThis()\n");
}

CMySharedThis::~CMySharedThis()
{
    printf("~CMySharedThis()\n");
}

void CMySharedThis::Init()
{
    if(!g_pUse)
    {
        g_pUse = new CMyUseSharedPtr;
    }

    auto t = shared_from_this();
    //g_pUse->SetSharedPtr(shared_from_this());
}

void CMySharedThis::UnInit()
{
    if(g_pUse)
    {
        delete g_pUse;
        g_pUse = nullptr;
    }
}
void CMySharedThis::Print(std::string strMsg)
{
    printf("CMySharedThis :msg:%s\n", strMsg.c_str());
}

CMyUseSharedPtr::CMyUseSharedPtr()
{
    printf("CMyUseSharedPtr()\n");
}

CMyUseSharedPtr::~CMyUseSharedPtr()
{
    printf("~CMyUseSharedPtr()\n");
}

void CMyUseSharedPtr::SetSharedPtr(std::shared_ptr<CMySharedThis> pPtr)
{
    m_pPtr = pPtr;
    m_pPtr->Print("this is SetSharedPtr");
}
