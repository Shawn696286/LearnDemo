#include "cd3dx_spirte_render.h"
#include "public.h"
IDirect3D9* CD3dxSpirteRender::m_pD3D9Handle = nullptr;
CD3dxSpirteRender::CD3dxSpirteRender()
{
}

CD3dxSpirteRender::~CD3dxSpirteRender()
{
}

int CD3dxSpirteRender::Init(HWND hWnd, int nWidth, int nHeight)
{
    HRESULT res = 0;
    D3DDISPLAYMODE disp_mode;
    D3DPRESENT_PARAMETERS present_params;
    D3DFORMAT format = (D3DFORMAT)MAKEFOURCC('Y', 'U', 'Y', '2');

    if(m_pD3D9Handle == nullptr)
    {
        m_pD3D9Handle = Direct3DCreate9(D3D_SDK_VERSION);
    }

    if(m_pD3D9Handle == nullptr)
    {
        LOGY_ERROR("Direct3DCreate9 failed.");
        return Ret_Y_Error;
    }

    if(FAILED(m_pD3D9Handle->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp_mode)))
    {
        LOGY_ERROR("IDirect3D9_GetAdapterDisplayMode failed.");
        return Ret_Y_Error;
    }

    if(FAILED(m_pD3D9Handle->CheckDeviceFormatConversion(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, format, disp_mode.Format)))
    {
        LOGY_ERROR("IDirect3D9_CheckDeviceFormatConversion failed.");
        return Ret_Y_Error;
    }


    memset(&present_params, 0, sizeof(present_params));
    present_params.Windowed = true;
    present_params.hDeviceWindow = hWnd;
    present_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present_params.Flags = D3DPRESENTFLAG_VIDEO;
    present_params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    present_params.BackBufferFormat = disp_mode.Format;
    present_params.BackBufferCount = 1;
    present_params.BackBufferWidth = nWidth;
    present_params.BackBufferHeight = nHeight;
    res = m_pD3D9Handle->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &present_params, &m_pD3DDevice9);

    if(FAILED(res))
    {
        LOGY_ERROR("IDirect3D9_CreateDevice failed. wnd = 0x%x, 0x%x", hWnd, res);
        return Ret_Y_Error;
    }

    if(FAILED(D3DXCreateSprite(m_pD3DDevice9, &m_pD3DSprite)))
    {
        return Ret_Y_Error;
    }

    return Ret_Y_OK;
}

void CD3dxSpirteRender::Repaint(AVFrame* pFrame)
{

}

