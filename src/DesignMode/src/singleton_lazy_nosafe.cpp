#include "singleton_lazy_nosafe.h"

Singleton* Singleton::m_pSelf = nullptr;

Singleton* Singleton::GetInstance()
{
    if(m_pSelf == nullptr)
    {
        m_pSelf = new Singleton;
    }

    return m_pSelf;
}
