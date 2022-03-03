#include "agency.h"

CGril::CGril(const string& strName)
{
    m_strName = strName;
}


string CGril::GetName()
{
    return m_strName;
}

CYoungMan::CYoungMan(const CGril& oGril)
{
    m_oGril = oGril;
}

void CYoungMan::Profess()
{
    cout << "Young man love " << m_oGril.GetName().data() << endl;
}

CManProxy::CManProxy(const CGril& oGril)
{
    m_pMan = new CYoungMan(oGril);
}

CManProxy::~CManProxy()
{
    delete m_pMan;
    m_pMan = nullptr;
}

void CManProxy::Profess()
{
    m_pMan->Profess();
}

