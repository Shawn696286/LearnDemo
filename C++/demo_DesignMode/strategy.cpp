#include "strategy.h"

void AdcHurt::Blood()
{
    cout << "Adc hurt,Blood loss" << endl;
}

void ApcHurt::Blood()
{
    cout << "Apc hurt,Blood loss" << endl;
}

Soldier::Soldier(Hurt* pHurt)
{
    m_pHurt = pHurt;
}

void Soldier::Attack()
{
    m_pHurt->Blood();
}

Mage::Mage(HurtType eType)
{
    switch(eType)
    {
        case Hurt_Type_Adc:
            m_pHurt = new AdcHurt;
            break;

        case Hurt_Type_Apc:
            m_pHurt = new ApcHurt;
            break;

        default:
            break;
    }
}

Mage::~Mage()
{
    delete m_pHurt;
    m_pHurt = nullptr;
    cout << "~Mage()" << endl;
}

void Mage::Attack()
{
    m_pHurt->Blood();
}

