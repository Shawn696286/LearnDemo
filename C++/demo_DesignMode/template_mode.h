#pragma once
/*
    ����������Ϊ�������������Ĺ��̶���һ���ģ�ֻ��һЩװ����������ܲ�ͬ���ѡ�
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