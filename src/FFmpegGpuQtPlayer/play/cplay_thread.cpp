#include "cplay_thread.h"
#include "cmainwin.h"
#include "cdecode_hard.h"
#include "cd3dx_spirte_render.h"
#include "cd3d_dxva2_render.h"
#include "cdecode_dxva2.h"

AVPixelFormat GetHwFormat2(AVCodecContext* s, const AVPixelFormat* pix_fmts)
{
    CD3dDxva2Render* pD3DDxva2Render = (CD3dDxva2Render*)s->opaque;
    pD3DDxva2Render->active_hwaccel_id = HWACCEL_DXVA2;
    pD3DDxva2Render->hwaccel_pix_fmt = AV_PIX_FMT_DXVA2_VLD;
    return pD3DDxva2Render->hwaccel_pix_fmt;
}
CPlayThread::CPlayThread(CMainWin* pMainWin)
{
    m_bPlay = false;
    m_pDecoder = nullptr;
    m_pMainWin = pMainWin;
}

CPlayThread::~CPlayThread()
{

}

int CPlayThread::Open(QString qstrFilename, EDecodeMode eMode)
{
    //CDecodeHard oDh;
    //oDh.Test(qstrFilename.toStdString());
    m_eMode = eMode;
    return m_oDemux.Open(qstrFilename.toStdString());
}

void CPlayThread::run()
{
    if(m_pDecoder)
    {
        return;
    }

    //m_pDecoder = new IDecode;
    //m_pDecoder = new CDecodeHard;


    auto pParam = m_oDemux.CopyVPara();

    if(!pParam)
    {
        return;
    }

    if(Mode_Hard_Hard == m_eMode)
    {
        m_pDecoder = new CDecodeDxva2;

        if(!m_pDecoder)
        {
            return;
        }

        CD3dDxva2Render oDxva2Render;
        DXVA2Context* pDxva2Ctx = oDxva2Render.m_pDxva2Ctx;
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

        m_bPlay = true;

        auto u64PreTime = CUtilY::TimeGetCurrentMilli();
        auto u64CurTime = CUtilY::TimeGetCurrentMilli();
        int nCount = 0;
        std::vector<AVPacket*> listPacket;

        while(true)
        {
            auto pPacket = m_oDemux.ReadVideo();

            if(!pPacket)
            {
                break;
            }

            listPacket.push_back(pPacket);
        }

        int nIndex = 0;

        while(m_bPlay)
        {
            if(nIndex == listPacket.size())
            {
                nIndex = 0;
            }

            auto pPacket = listPacket[nIndex++];

            if(pPacket)
            {
                if(Ret_Y_OK != m_pDecoder->Send(pPacket, false))
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
                    //m_pDecoder->Render(pFrame, false);

                    av_frame_free(&pFrame);
                    pFrame = nullptr;

                    ++nCount;
                    u64CurTime = CUtilY::TimeGetCurrentMilli();

                    if(u64CurTime - u64PreTime > 1000)
                    {
                        printf("----------------%d/s\n", nCount);
                        nCount = 0;
                        u64PreTime = u64CurTime;
                    }
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

    }
    else if(Mode_Hard_Soft == m_eMode)
    {
        m_pDecoder = new CDecodeHard;

        if(!m_pDecoder)
        {
            return;
        }

        m_pDecoder->Open(pParam);

        m_bPlay = true;

        CDecodeHard oDh;
        CD3dxSpirteRender oD3dSpritRender;

        while(m_bPlay)
        {
            auto pPacket = m_oDemux.ReadVideo();

            if(pPacket)
            {
                #ifdef USE_TEST_DEMO
                auto pf = oDh.Test(pPacket);

                if(!pf)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }

                m_pMainWin->Repaint(pf);
                #else

                if(Ret_Y_OK != m_pDecoder->Send(pPacket, true))
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
                    m_pMainWin->Repaint(pFrame);
                }

                #endif // USE_TEST_DEMO
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }
    }

    if(m_pDecoder)
    {
        delete m_pDecoder;
    }
}

void CPlayThread::Stop()
{
    m_bPlay = false;
}