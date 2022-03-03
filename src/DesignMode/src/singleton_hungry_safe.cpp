#include "singleton_hungry_safe.h"
SingletonHungry* SingletonHungry::m_pSelf = new SingletonHungry;

SingletonHungry* SingletonHungry::GetInstance()
{
    return m_pSelf;
}
