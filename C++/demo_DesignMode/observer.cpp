#include "observer.h"
void CIntDataModel::AddView(shared_ptr<IView> pView)
{
    auto iter = find(m_listPView.begin(), m_listPView.end(), pView);

    if(iter == m_listPView.end())
    {
        m_listPView.push_front(pView);
    }
    else
    {
        cout << "View already exists" << endl;
    }
}

void CIntDataModel::RemoveView(shared_ptr<IView> pView)
{
    auto iter = find(m_listPView.begin(), m_listPView.end(), pView);

    if(iter != m_listPView.end())
    {
        m_listPView.erase(iter);
        cout << "remove view" << endl;
    }
}

void CIntDataModel::Notify()
{
    auto iter = m_listPView.begin();

    for(; iter != m_listPView.end(); ++iter)
    {
        (*iter)->Update();
    }
}

void CTableView::SetViewName(string& strName)
{
    m_strName = strName;
}

const string& CTableView::Name()
{
    return m_strName;
}

void CTableView::Update()
{
    cout << m_strName << " updata" << endl;
}


