#pragma once
/*
    关键代码：客户与系统之间加一个外观层，外观层处理系统的调用关系、依赖关系等。
    以下实例以电脑的启动过程为例，客户端只关心电脑开机的、关机的过程，并不需要了解电脑内部子系统的启动过程。
*/
#include "public.h"
//抽象控件类，提供接口
class IControl
{
public:
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
};

//子控件，主机
class CHost: public IControl
{
public:
    void Start() override;
    void Shutdown() override;
};

//子控件，显示器
class CLcdDisplay: public  IControl
{
public:
    void Start() override;
    void Shutdown() override;
};

//子控件，外部设备
class CPeripheral: public IControl
{
public:
    void Start() override;
    void Shutdown() override;
};

class CComputer
{
public:
    void Start();
    void Shutdown();
private:
    CHost m_oHost;
    CLcdDisplay m_oDisplay;
    CPeripheral moPeripheral;
};
