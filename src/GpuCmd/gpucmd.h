#pragma once
#include <string>
#include "logyapi.h"
#include "gpu/gpumon/DriverEnum.h"

/*
    GpuMon dynamic library file to load (per platform)
*/
#ifdef _WIN32
    #if defined(_M_X64) || defined(__amd64__)
        #define GPUMON_DLL "gpumon64.dll"
    #else
        #define GPUMON_DLL "gpumon32.dll"
    #endif
#elif defined(__APPLE__)
    #if defined(__i386__) /* Mojave and earlier */
        #define GPUMON_DLL "libgpumon32.dylib"
    #else
        #define GPUMON_DLL "libgpumon64.dylib"
    #endif
#endif

/* GpuMon core function */
extern void (*pfnDrv_GetGpuDriver)(int DriverType, GPUDRIVER* pDriver);

/* Handle to the actual GpuMon core */
extern HMODULE hGpuMonDll;

/* Driver handle instance*/
extern GPUDRIVER driver[Drv_MAX];
//std::unordered_map<GPUDRIVER> driver;

class CGpuCmd
{
public:
    CGpuCmd();
    ~CGpuCmd();

    /*
        Name: InitializeGpuMon
        Desc: Initializes the GpuMon DLL for the appropriate architecture.
    */
    static bool InitializeGpuMon();

    /*
        Name: GetLastErrorAsString
        Desc: Returns the last error, in string format. Returns an empty string if there is no error.
    */
    static std::string GetLastErrorAsString();

    /*
        Name: IntializeDriverHook
        Desc: Initalizes driver hook for a specific driver vendor.
    */
    static bool InitializeDriverHook(int DriverType, int Adapter, GPUDRIVER* driver);


};