// C++.cpp: 定义应用程序的入口点。
//
#include "public.h"
#include "idecode.h"
#include "cdemux.h"
#include "cdecode_dxva2.h"
#include "cd3d_dxva2_render.h"

HWND m_pHwnd = NULL;
IDecode* m_pDecoder = NULL;
CDemux m_oDemux;
bool m_bPlay = false;

void main(int argc, char* argv[])
{
    //if(m_pDecoder)
    //{
    //    return ;
    //}

    //m_pDecoder = new IDecode;
    //m_pDecoder = new CDecodeHard;


    m_oDemux.Open("./ZeddIgniteWorlds.mp4");
    auto pParam = m_oDemux.CopyVPara();

    if(!pParam)
    {
        return;
    }

    m_pDecoder = new CDecodeDxva2;

    if(!m_pDecoder)
    {
        return;
    }

    CD3dDxva2Render oDxva2Render;
    DXVA2Context* pDxva2Ctx = oDxva2Render.m_pDxva2Ctx;
    //HWND hWnd = CreateWindow(TEXT("abc"), TEXT("hello,windows"), WS_OVERLAPPEDWINDOW,
    //                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    //                         NULL, NULL, nullptr, NULL); //返回窗口句柄

    int nRet = oDxva2Render.Init(m_oDemux.GetWidth(), m_oDemux.GetHeight(), m_pHwnd, "dxva2");

    if(nRet != Ret_Y_OK)
    {
        LOGY_ERROR("CD3dDxva2Render init failed");
        return;
    }

    LOGY_INFO("CD3dDxva2Render init success");

    nRet = m_pDecoder->Open(pParam, &oDxva2Render);

    if(nRet != Ret_Y_OK)
    {
        LOGY_ERROR("CDecodeDxva2 Open failed");
        return;
    }

    LOGY_INFO("decoder open success");

    //m_bPlay = true;

    while(m_bPlay)
    {
        auto pPacket = m_oDemux.ReadVideo();

        if(pPacket)
        {
            if(Ret_Y_OK != m_pDecoder->Send(pPacket))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }

            //一次send 多次recv
            while(m_bPlay)
            {
                AVFrame* pFrame = m_pDecoder->Recv();

                if(!pFrame)
                {
                    break;
                }

                //显示视频
                m_pDecoder->Render(pFrame, true);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    m_oDemux.Close();

    if(m_pDecoder)
    {
        m_pDecoder->Close();
        delete m_pDecoder;
        m_pDecoder = nullptr;
    }

    oDxva2Render.UnInit();

    if(m_pDecoder)
    {
        delete m_pDecoder;
    }

}
