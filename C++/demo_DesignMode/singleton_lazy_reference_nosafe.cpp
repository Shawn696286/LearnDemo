#include "singleton_lazy_reference_nosafe.h"

SingletonEx2& SingletonEx2::GetInstance()
{
    static SingletonEx2 singleton;
    return singleton;
}