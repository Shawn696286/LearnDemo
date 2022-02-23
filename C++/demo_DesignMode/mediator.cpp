#include "mediator.h"
void IBusinessMan::SetMediator(IMediator* pM)
{
    m_pMediator = pM;
}

void CBuyer::SendMessage(const string& strMsg)
{
    m_pMediator->Send(strMsg, this);
}

void CBuyer::GetMessage(const string& strMsg)
{
    cout << "Buyer recv:" << strMsg << endl;
}

void CSeller::SendMessage(const string& strMsg)
{
    m_pMediator->Send(strMsg, this);
}

void CSeller::GetMessage(const string& strMsg)
{
    cout << "Seller recv:" << strMsg << endl;
}

void CHouseMediator::SetBuyer(IBusinessMan* pBuyer)
{
    m_pBuyer = pBuyer;
}

void CHouseMediator::SetSeller(IBusinessMan* pSeller)
{
    m_pSeller = pSeller;
}

void CHouseMediator::Send(const string& strMsg, IBusinessMan* pMan)
{
    if(pMan == m_pBuyer)
    {
        m_pSeller->GetMessage(strMsg);
    }
    else if(pMan == m_pSeller)
    {
        m_pBuyer->GetMessage(strMsg);
    }
}



