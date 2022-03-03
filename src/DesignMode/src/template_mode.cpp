#include "template_mode.h"

void IComputer::Product()
{
    InstallCpu();
    InstallRam();
    InstallGraphicsCard();
}

void CComputerA::InstallCpu()
{
    cout << "ComputerA install Inter Core i5" << endl;
}

void CComputerA::InstallRam()
{
    cout << "ComputerA install 2G ram" << endl;
}

void CComputerA::InstallGraphicsCard()
{
    cout << "ComputerA install Gtx740 GraphicsCard" << endl;
}

void CComputerB::InstallCpu()
{
    cout << "ComputerB install Inter Core i7" << endl;
}

void CComputerB::InstallRam()
{
    cout << "ComputerB install 4G ram" << endl;
}

void CComputerB::InstallGraphicsCard()
{
    cout << "ComputerB install Gtx960 GraphicsCard" << endl;
}



