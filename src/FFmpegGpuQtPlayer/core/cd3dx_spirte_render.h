#pragma once
#include "irender.h"
#include "d3dx9.h"
class CD3dxSpirteRender: public IRender
{
public:
    CD3dxSpirteRender();
    ~CD3dxSpirteRender();
    int Init(HWND hWnd, int nWidth, int nHeight);
    void Repaint(AVFrame* pFrame) override;
private:
    static IDirect3D9* m_pD3D9Handle;        // Direct3D9 Handle
    IDirect3DDevice9* m_pD3DDevice9;
    LPD3DXSPRITE m_pD3DSprite;
};

