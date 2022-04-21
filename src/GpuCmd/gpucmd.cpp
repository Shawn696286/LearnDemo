#include "gpucmd.h"
#include <libloaderapi.h>
#include <errhandlingapi.h>
#include <WinBase.h>
#include <sstream>
/* GpuMon core function */
void (*pfnDrv_GetGpuDriver)(int DriverType, GPUDRIVER* pDriver);

/* Handle to the actual GpuMon core */
HMODULE hGpuMonDll = nullptr;

/* Driver handle instance*/
GPUDRIVER driver[Drv_MAX];
//std::unordered_map<GPUDRIVER> driver;
CGpuCmd::CGpuCmd()
{
}

CGpuCmd::~CGpuCmd()
{
}

bool CGpuCmd::InitializeGpuMon()
{
    LOGY_DEBUG("Begin...");
    LOGY_DEBUG("Loading dynamic library \"%s\"...", GPUMON_DLL);

    /* Start by loading the appropriate DLL*/
    hGpuMonDll = LoadLibraryA(GPUMON_DLL);

    if(!hGpuMonDll)
    {
        LOGY_ERROR("ERROR: Could not open %s %s", GPUMON_DLL, GetLastErrorAsString().c_str());

        return false;
    }

    LOGY_DEBUG("Querying procedure address: Drv_GetGpuDriver...");

    /* Get the primary function that returns our driver retreival function */
    pfnDrv_GetGpuDriver = (void (*)(int, GPUDRIVER*)) GetProcAddress(hGpuMonDll, "Drv_GetGpuDriver");

    if(!pfnDrv_GetGpuDriver)
    {
        LOGY_ERROR("ERROR: Could not locate Drv_GetGpuDriver() within module %s %s", GPUMON_DLL,
                   GetLastErrorAsString().c_str());

        return false;
    }

    LOGY_DEBUG("Success");

    return true;
}


std::string CGpuCmd::GetLastErrorAsString()
{
    #if defined(_WIN32)
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();

    if(errorMessageID == 0)
    {
        return std::string();    //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                 FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string msg(messageBuffer, size);
    std::stringstream ss;

    ss << "\nGetLastError(0x" << errorMessageID << "): " << msg << std::endl;

    std::string message = ss.str();

    //Free the buffer.
    LocalFree(messageBuffer);
    #else   // macOS and Linux
    //std::string message( strerror( errno ) );
    std::stringstream ss;
    int e = errno;

    ss << "\nerrno(" << e << "): " << strerror(e) << std::endl;

    std::string message = ss.str();

    char* dlerr = dlerror();

    if(dlerr)
    {
        message.append("\ndlerror(): ");
        message.append(dlerr);
        message.append("\n");
    }

    #endif

    return message;
}

bool CGpuCmd::InitializeDriverHook(int DriverType, int Adapter, GPUDRIVER* driver)
{
    LOGY_DEBUG("Begin...");

    /* Sanity check */
    if(!driver)
    {
        LOGY_ERROR("Invalid driver structure pointer!");
        return false;
    }

    LOGY_DEBUG("Initializing driver structure...");

    /* Get the driver and attempt to initialize it */
    pfnDrv_GetGpuDriver(DriverType, driver);

    LOGY_DEBUG("Initializing driver hooks (driver type: %d, adapter #: %d)", DriverType, Adapter);

    if(!driver->Initialize())
    {
        LOGY_ERROR("Could not initialize driver hooks, hardware not present or internal API failure.");
        return false;
    }

    LOGY_DEBUG("Success");

    return true;
}
