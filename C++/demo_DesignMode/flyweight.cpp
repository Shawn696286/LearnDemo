#include "flyweight.h"
CConsumer::CConsumer(const string& strName)
{
    m_strUser = strName;
}

CConsumer::~CConsumer()
{
    cout << "~CConsumer" << endl;
}

void CConsumer::SetArticle(const string& strArticle)
{
    m_strArticle = strArticle;
}

const string& CConsumer::Article()
{
    return m_strArticle;
}

CTrusteeship::~CTrusteeship()
{
    m_mapUserAndConsumer.clear();
}

void CTrusteeship::Hosting(const string& strUser, const string& strArticle)
{
    if(m_mapUserAndConsumer.count(strUser))
    {
        cout << "A customer named " << strUser << " already exists" << endl;
        auto pConsumer = m_mapUserAndConsumer.at(strUser);
        pConsumer->SetArticle(strArticle);
    }
    else
    {
        auto pConsumer = make_shared<CConsumer>(strUser);
        pConsumer->SetArticle(strArticle);
        m_mapUserAndConsumer.insert(pair<string, shared_ptr<CConsumer>>(strUser, pConsumer));
    }
}

void CTrusteeship::Display()
{
    for(auto iter : m_mapUserAndConsumer)
    {
        cout << iter.first << ":" << iter.second->Article() << endl;
    }
}



