#include "composite.h"

ICompany::ICompany(const string& strName)
{
    m_strName = strName;
}

ICompany::~ICompany()
{
    cout << "~ICompany()" << endl;
}

const string& ICompany::Name()
{
    return m_strName;
}

CHeadCompany::CHeadCompany(const string& strName)
    : ICompany(strName)
{

}

CHeadCompany::~CHeadCompany()
{
    cout << "~CHeadCompany()" << endl;
}

void CHeadCompany::Add(shared_ptr<ICompany> pCompany)
{
    m_listCompany.push_back(pCompany);
}

void CHeadCompany::Remove(const string& strName)
{
    auto iter = m_listCompany.begin();

    for(; iter != m_listCompany.end(); ++iter)
    {
        if((*iter)->Name() == strName)
        {
            m_listCompany.erase(iter);
            break;
        }
    }
}

void CHeadCompany::Display(int nDepth)
{
    for(int i = 0; i < nDepth; ++i)
    {
        cout << "-";
    }

    cout << this->Name().data() << endl;

    for(auto iter : m_listCompany)
    {
        iter->Display(nDepth + 1);
    }
}

CResearchCompany::CResearchCompany(const string& strName)
    : ICompany(strName)
{

}

CResearchCompany::~CResearchCompany()
{
    cout << "~CResearchCompany()" << endl;
}

void CResearchCompany::Add(shared_ptr<ICompany> pCompany)
{
}

void CResearchCompany::Remove(const string& strName)
{
}

void CResearchCompany::Display(int nDepth)
{
    for(int i = 0; i < nDepth; ++i)
    {
        cout << "-";
    }

    cout << this->Name().data() << endl;
}

CSalesCompany::CSalesCompany(const string& strName)
    : ICompany(strName)
{

}

CSalesCompany::~CSalesCompany()
{
    cout << "~CSalesCompany()" << endl;
}

void CSalesCompany::Add(shared_ptr<ICompany> pCompany)
{
}

void CSalesCompany::Remove(const string& strName)
{
}

void CSalesCompany::Display(int nDepth)
{
    for(int i = 0; i < nDepth; ++i)
    {
        cout << "-";
    }

    cout << this->Name().data() << endl;
}

CFinanceCompany::CFinanceCompany(const string& strName)
    : ICompany(strName)
{

}

CFinanceCompany::~CFinanceCompany()
{
    cout << "~CFinanceCompany()" << endl;
}

void CFinanceCompany::Add(shared_ptr<ICompany> pCompany)
{
}

void CFinanceCompany::Remove(const string& strName)
{
}

void CFinanceCompany::Display(int nDepth)
{
    for(int i = 0; i < nDepth; ++i)
    {
        cout << "-";
    }

    cout << this->Name().data() << endl;
}
