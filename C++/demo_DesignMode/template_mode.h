#pragma once
/*
    以生产电脑为例，电脑生产的过程都是一样的，只是一些装配的器件可能不同而已。
*/
#include "public.h"
class IComputer
{
public:
    void Product();
protected:
    virtual void InstallCpu() = 0;
    virtual void InstallRam() = 0;
    virtual void InstallGraphicsCard() = 0;
};

class CComputerA: public IComputer
{
protected:
    void InstallCpu() override;
    void InstallRam() override;
    void InstallGraphicsCard() override;
};


class CComputerB : public IComputer
{
protected:
    void InstallCpu() override;
    void InstallRam() override;
    void InstallGraphicsCard() override;
};