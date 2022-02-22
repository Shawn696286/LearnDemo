#include "decorative.h"
void CCar::Configuration()
{
    cout << "A Car" << endl;
}

CDecorateCar::CDecorateCar(IComponent* pCar)
{
    m_pCar = pCar;
}

void CDecorateCar::Configuration()
{
    m_pCar->Configuration();
}

CDecorateLED::CDecorateLED(IComponent* pCar)
    : CDecorateCar(pCar)
{

}

void CDecorateLED::Configuration()
{
    CDecorateCar::Configuration();
    AddLED();
}

void CDecorateLED::AddLED()
{
    cout << "Install LED" << endl;
}

CDecoratePC::CDecoratePC(IComponent* pCar)
    : CDecorateCar(pCar)
{

}

void CDecoratePC::Configuration()
{
    CDecorateCar::Configuration();
    AddPC();
}

void CDecoratePC::AddPC()
{
    cout << "Install PC" << endl;
}

CDecorateEPB::CDecorateEPB(IComponent* pCar)
    : CDecorateCar(pCar)
{

}

void CDecorateEPB::Configuration()
{
    CDecorateCar::Configuration();
    AddEPB();
}

void CDecorateEPB::AddEPB()
{
    cout << "Install EPB" << endl;
}

