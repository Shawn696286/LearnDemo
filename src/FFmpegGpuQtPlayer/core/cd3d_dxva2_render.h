#pragma once
#include "public.h"
#include "d3dx9.h"
#include <dxva2api.h>
struct AVFrame;
struct surface_info
{
    int used;
    uint64_t age;
};
struct DXVA2Context
{
    HANDLE  pDeviceHandle;

    IDirect3D9* pD3d9;
    IDirect3DDevice9* pD3d9Device;
    IDirect3DDeviceManager9* pD3d9Devmgr;
    IDirectXVideoDecoderService* pDecoderService;
    IDirectXVideoDecoder* pDecoder;

    GUID                        oDecoderGuid;
    DXVA2_ConfigPictureDecode   oDecoderConfig;

    LPDIRECT3DSURFACE9* pSurfaces;
    surface_info* pSurfaceInfos;
    uint32_t                    nSurfacesCount;
    uint64_t                    nSurfaceAge;

    AVFrame* pTmpFrame;
};

typedef struct DXVA2SurfaceWrapper
{
    DXVA2Context* ctx;
    LPDIRECT3DSURFACE9   surface;
    IDirectXVideoDecoder* decoder;
} DXVA2SurfaceWrapper;

#ifndef _HWAccelID
#define _HWAccelID

enum HWAccelID
{
    HWACCEL_NONE = 0,
    HWACCEL_AUTO,
    HWACCEL_VDPAU,
    HWACCEL_DXVA2,
    HWACCEL_VDA,
    HWACCEL_VIDEOTOOLBOX,
    HWACCEL_QSV,
};
#endif // !_HWAccelID
class CD3dDxva2Render
{
public:
    int Init(int nWidth, int nHeight, HWND pHwnd, std::string strHwaccelDevice = "dxva2");

    void UnInit();

    int ScreenShot(std::string strFilename);

    DXVA2Context* m_pDxva2Ctx = nullptr;

    enum HWAccelID active_hwaccel_id;
    enum AVPixelFormat hwaccel_pix_fmt;
    D3DPRESENT_PARAMETERS m_oD3dPresentParam = { 0 };

private:
    //static IDirect3D9* m_pD3D9Handle;        // Direct3D9 Handle

};