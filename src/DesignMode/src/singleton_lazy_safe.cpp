#include "singleton_lazy_safe.h"
mutex g_oMtx;
SingletonEx* SingletonEx::m_pSelf = nullptr;

SingletonEx* SingletonEx::GetInstance()
{
    if(nullptr == m_pSelf)
    {
        g_oMtx.lock();

        if(nullptr == m_pSelf)
        {
            m_pSelf = new SingletonEx;
        }

        g_oMtx.unlock();
    }

    return m_pSelf;
}
