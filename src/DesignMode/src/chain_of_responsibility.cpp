#include "chain_of_responsibility.h"
void CMonitor::HandleRequest(ERequestLevel eLevel)
{
    if(eLevel < Level_2)
    {
        cout << "Monitor handle request:" << eLevel << endl;
    }
    else
    {
        m_pLeader->HandleRequest(eLevel);
    }
}

void CCaptain::HandleRequest(ERequestLevel eLevel)
{
    if(eLevel < Level_3)
    {
        cout << "Captain handle request:" << eLevel << endl;
    }
    else
    {
        m_pLeader->HandleRequest(eLevel);
    }
}

void CGeneral::HandleRequest(ERequestLevel eLevel)
{
    cout << "General handle request:" << eLevel << endl;
}

