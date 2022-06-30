#include "cd3d_dxva2_render.h"
#include "public.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

#pragma comment(lib, "avcodec.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxva2.lib")
class CDecorateD3D
{
public:
    ~CDecorateD3D()
    {
        if(m_pD3D9Handle)
        {
            m_pD3D9Handle->Release();
            m_pD3D9Handle = nullptr;
        }
    }
    IDirect3D9* m_pD3D9Handle = nullptr;
};

static CDecorateD3D g_oDecorateD3D;

int CD3dDxva2Render::Init(int nWidth, int nHeight, HWND pHwnd, std::string strHwaccelDevice)
{
    int nRet = Ret_Y_Error;

    do
    {
        m_pDxva2Ctx = new DXVA2Context;

        if(!m_pDxva2Ctx)
        {
            LOGY_ERROR("new DXVA2Context failed.");
            break;
        }

        memset(m_pDxva2Ctx, 0, sizeof(DXVA2Context));
        m_pDxva2Ctx->pDeviceHandle = INVALID_HANDLE_VALUE;

        if(g_oDecorateD3D.m_pD3D9Handle == nullptr)
        {
            g_oDecorateD3D.m_pD3D9Handle = Direct3DCreate9(D3D_SDK_VERSION);
        }

        if(g_oDecorateD3D.m_pD3D9Handle == nullptr)
        {
            LOGY_ERROR("Direct3DCreate9 failed.");
            break;
        }

        m_pDxva2Ctx->pD3d9 = g_oDecorateD3D.m_pD3D9Handle;
        unsigned int nAdapter = D3DADAPTER_DEFAULT;

        if(!strHwaccelDevice.empty())
        {
            nAdapter = atoi(strHwaccelDevice.c_str());
            LOGY_INFO("Using HWAccel device %d", nAdapter);
        }

        D3DDISPLAYMODE oD3ddm;
        IDirect3D9_GetAdapterDisplayMode(m_pDxva2Ctx->pD3d9, nAdapter, &oD3ddm);
        m_oD3dPresentParam.BackBufferWidth = nWidth;
        m_oD3dPresentParam.BackBufferHeight = nHeight;
        m_oD3dPresentParam.Windowed = TRUE;
        m_oD3dPresentParam.BackBufferCount = 0;
        m_oD3dPresentParam.hDeviceWindow = pHwnd;
        m_oD3dPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
        m_oD3dPresentParam.BackBufferFormat = oD3ddm.Format;
        m_oD3dPresentParam.EnableAutoDepthStencil = FALSE;
        m_oD3dPresentParam.Flags = D3DPRESENTFLAG_VIDEO;
        m_oD3dPresentParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        m_oD3dPresentParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

        D3DCAPS9 caps;
        DWORD BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
        HRESULT pHresult = m_pDxva2Ctx->pD3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

        if(SUCCEEDED(pHresult))
        {
            if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
            {
                BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE;
            }
            else
            {
                BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE;
            }
        }

        pHresult = IDirect3D9_CreateDevice(m_pDxva2Ctx->pD3d9, nAdapter, D3DDEVTYPE_HAL, pHwnd, BehaviorFlags,
                                           &m_oD3dPresentParam, &m_pDxva2Ctx->pD3d9Device);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to create Direct3D device");
            break;
        }

        unsigned int nResetToken = 0;
        pHresult = DXVA2CreateDirect3DDeviceManager9(&nResetToken, &m_pDxva2Ctx->pD3d9Devmgr);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to create Direct3D device manager");
            break;
        }

        //hr = IDirect3DDeviceManager9_ResetDevice(ctx->d3d9devmgr, ctx->d3d9device, resetToken);
        pHresult = m_pDxva2Ctx->pD3d9Devmgr->ResetDevice(m_pDxva2Ctx->pD3d9Device, nResetToken);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to bind Direct3D device to device manager");
            break;
        }

        //hr = IDirect3DDeviceManager9_OpenDeviceHandle(ctx->d3d9devmgr, &ctx->deviceHandle);
        pHresult = m_pDxva2Ctx->pD3d9Devmgr->OpenDeviceHandle(&m_pDxva2Ctx->pDeviceHandle);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to open device handle");
            break;
        }

        //hr = IDirect3DDeviceManager9_GetVideoService(ctx->d3d9devmgr, ctx->deviceHandle, &IID_IDirectXVideoDecoderService, (void **)&ctx->decoder_service);
        pHresult = m_pDxva2Ctx->pD3d9Devmgr->GetVideoService(m_pDxva2Ctx->pDeviceHandle, IID_IDirectXVideoDecoderService,
                   (void**)&m_pDxva2Ctx->pDecoderService);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to create IDirectXVideoDecoderService");
            break;
        }

        m_pDxva2Ctx->pTmpFrame = av_frame_alloc();

        if(!m_pDxva2Ctx->pTmpFrame)
        {
            LOGY_ERROR("Failed to av_frame_alloc");
            break;
        }

        nRet = Ret_Y_OK;

    } while(0);

    if(Ret_Y_OK != nRet)
    {
        UnInit();
    }

    return nRet;
}

void CD3dDxva2Render::UnInit()
{
    if(m_pDxva2Ctx)
    {

        if(m_pDxva2Ctx->pD3d9Devmgr && m_pDxva2Ctx->pDeviceHandle != INVALID_HANDLE_VALUE)
            //IDirect3DDeviceManager9_CloseDeviceHandle(ctx->d3d9devmgr, ctx->deviceHandle);
        {
            m_pDxva2Ctx->pD3d9Devmgr->CloseDeviceHandle(m_pDxva2Ctx->pDeviceHandle);
        }

        if(m_pDxva2Ctx->pD3d9Devmgr)
        {
            m_pDxva2Ctx->pD3d9Devmgr->Release();
            m_pDxva2Ctx->pD3d9Devmgr = nullptr;
        }

        if(m_pDxva2Ctx->pDecoderService)
        {
            m_pDxva2Ctx->pDecoderService->Release();
            m_pDxva2Ctx->pDecoderService = nullptr;
        }

        if(m_pDxva2Ctx->pD3d9Device)
        {
            m_pDxva2Ctx->pD3d9Device->Release();
            m_pDxva2Ctx->pD3d9Device = nullptr;
        }

        if(m_pDxva2Ctx->pTmpFrame)
        {
            av_frame_free(&m_pDxva2Ctx->pTmpFrame);
            m_pDxva2Ctx->pTmpFrame = nullptr;
        }

        delete m_pDxva2Ctx;
        m_pDxva2Ctx = nullptr;
    }
}

int CD3dDxva2Render::ScreenShot(std::string strFilename)
{
    IDirect3DSurface9* tmp = NULL;
    IDirect3DSurface9* back = NULL;

    if(!m_pDxva2Ctx->pD3d9Device)
    {
        LOGY_INFO("m_pDxva2Ctx->pD3d9Device is null.");
        return Ret_Y_Error;
    }

    //生成固定颜色模式的离屏表面（Width和 Height为屏幕或窗口的宽高）
    if(m_pDxva2Ctx->pD3d9Device->CreateOffscreenPlainSurface(m_oD3dPresentParam.BackBufferWidth,
            m_oD3dPresentParam.BackBufferHeight, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &tmp, NULL))
    {
        LOGY_INFO("CreateOffscreenPlainSurface failed.");
        return Ret_Y_Error;
    }

    // 获得BackBuffer的D3D Surface
    if(m_pDxva2Ctx->pD3d9Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back))
    {
        LOGY_INFO("GetBackBuffer failed.");
        return Ret_Y_Error;
    }

    // Copy一下，，需要时转换颜色格式
    if(D3DXLoadSurfaceFromSurface(tmp, NULL, NULL, back, NULL, NULL, D3DX_FILTER_NONE, 0))
    {
        LOGY_INFO("D3DXLoadSurfaceFromSurface failed.");
        return Ret_Y_Error;
    }

    // 保存成PNG格式
    if(D3DXSaveSurfaceToFile(strFilename.c_str(), D3DXIFF_PNG, tmp, NULL, NULL))
    {
        LOGY_INFO("D3DXSaveSurfaceToFile failed.");
        return Ret_Y_Error;
    }

    // 释放Surface，防止内存泄漏
    if(tmp)
    {
        tmp->Release();
        tmp = nullptr;
    }

    if(back)
    {
        back->Release();
        back = nullptr;
    }

    return Ret_Y_OK;
}