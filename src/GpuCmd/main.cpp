// C++.cpp: 定义应用程序的入口点。
//
#include "gpucmd.h"
#include "logyapi.h"
using namespace std;

int main()
{
    LOGY_DEBUG("test logy\n");

    /*
        Start by loading the appropriate DLL
    */

    if(!CGpuCmd::InitializeGpuMon())
    {
        return -1;
    }

    #if defined(_WIN32)

    int Adapter = 0;

    /* The D3DKMT driver hook is manditory */
    if(!CGpuCmd::InitializeDriverHook(Drv_D3DKMT, Adapter, &driver[Drv_D3DKMT]))
    {
        LOGY_DEBUG("Unable to initialize D3DKMT driver hooks!");
        return -1;
    }

    int DriverType = Drv_D3DKMT;

    /* These two are purely optional */
    if(!CGpuCmd::InitializeDriverHook(Drv_NVAPI, Adapter, &driver[Drv_NVAPI]))
    {
        LOGY_DEBUG("NVAPI driver not available...");
    }

    if(!CGpuCmd::InitializeDriverHook(Drv_AMDGS, Adapter, &driver[Drv_AMDGS]))
    {
        LOGY_DEBUG("AMDGS driver not available...");
    }

    #elif defined(__APPLE__)

    /* Initialize IOKit hooks */
    if(!InitializeDriverHook(Drv_IOKIT, Adapter, &driver[Drv_IOKIT]))
    {
        GERRORP("Unable to initialize IOKit APIs!");
        return ERR_DRVFAIL;
    }

    DriverType = Drv_IOKIT;
    #endif

    while(true)
    {
        GPUSTATISTICS stats;
        int ret = driver[DriverType].GetOverallGpuLoad(Adapter, &stats);
        LOGY_DEBUG("Adapter GPU Usage: %d%%", stats.gpu_usage);
        Sleep(1000);
    }

    return 0;
}
