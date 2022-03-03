#include "facade.h"
void CHost::Start()
{
    cout << "Host start" << endl;
}
void CHost::Shutdown()
{
    cout << "Host shutdown" << endl;
}

void CLcdDisplay::Start()
{
    cout << "LcdDisplay start" << endl;
}
void CLcdDisplay::Shutdown()
{
    cout << "LcdDisplay shutdown" << endl;
}
void CPeripheral::Start()
{
    cout << "Peripheral start" << endl;
}
void CPeripheral::Shutdown()
{
    cout << "Peripheral shutdown" << endl;
}
void CComputer::Start()
{
    m_oHost.Start();
    m_oDisplay.Start();
    moPeripheral.Start();
    cout << "Computer start" << endl;
}
void CComputer::Shutdown()
{
    m_oHost.Shutdown();
    m_oDisplay.Shutdown();
    moPeripheral.Shutdown();
    cout << "Computer start" << endl;
}


