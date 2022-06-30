#include "idecode.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/pixfmt.h>
#include <libavutil/error.h>
#include <libavutil/channel_layout.h>
}

#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
IDecode::IDecode()
{
    m_pCodecCtx = nullptr;
    m_nSurfaceCount = 0;
    av_get_channel_layout_nb_channels(1);
}

IDecode::~IDecode()
{
}

void IDecode::Init(int nSurfaceCount)
{
}

int IDecode::Open(AVCodecParameters* pParam)
{
    int nRet = Ret_Y_OK;

    if(!pParam)
    {
        return Ret_Y_Error;
    }

    do
    {
        //找到解码器
        AVCodec* vcodec = (AVCodec*)avcodec_find_decoder(pParam->codec_id);

        if(!vcodec)
        {
            LOGY_ERROR("can't find the codec_id = %d", pParam->codec_id);
            nRet = Ret_Y_Error;
            break;
        }

        LOGY_INFO("finded the codec_id = %d", pParam->codec_id);

        //创建解码器上下文
        m_pCodecCtx = avcodec_alloc_context3(vcodec);
        //配置解码器上下文参数
        avcodec_parameters_to_context(m_pCodecCtx, pParam);

        //八线程解码
        m_pCodecCtx->thread_count = 8;
        //打开解码器上下文
        nRet = avcodec_open2(m_pCodecCtx, 0, 0);

        if(nRet != 0)
        {
            avcodec_free_context(&m_pCodecCtx);
            char buf[1024] = { 0 };
            av_strerror(nRet, buf, sizeof(buf));
            LOGY_ERROR("videoStream avcodec_open2 failed!errinfo = %s", buf);
            nRet = Ret_Y_Error;
            break;
        }

        LOGY_INFO("videoStream avcodec_open2 success!");
        nRet = Ret_Y_OK;
    } while(0);

    avcodec_parameters_free(&pParam);
    return nRet;
}

int IDecode::Open(AVCodecParameters* pParam, CD3dDxva2Render* pDxva2Render, bool bNeedFrameParam)
{
    return Ret_Y_Error;
}

int IDecode::Send(AVPacket* pPacket)
{
    int nRet = Ret_Y_Error;

    if(!pPacket)
    {
        return nRet;
    }

    do
    {
        if(pPacket->size <= 0 || !pPacket->data)
        {
            break;
        }

        if(!m_pCodecCtx)
        {
            break;
        }

        int nRet2 = avcodec_send_packet(m_pCodecCtx, pPacket);

        if(nRet2 != 0)
        {
            char pBufError[1024] = { 0 };

            if(0 != av_strerror(nRet2, pBufError, 1024))
            {
                LOGY_ERROR("av_strerror fail");
            }

            LOGY_ERROR("avcodec_send_packet failed!errinfo = %s", pBufError);
            break;
        }

        nRet = Ret_Y_OK;
    } while(0);


    av_packet_free(&pPacket);
    return nRet;
}

AVFrame* IDecode::Recv()
{
    if(!m_pCodecCtx)
    {
        return NULL;
    }

    int nRetryCount = 3;

    AVFrame* pFrame = av_frame_alloc();

    while(true)
    {
        int ret = avcodec_receive_frame(m_pCodecCtx, pFrame);

        if(ret != 0)
        {
            if(nRetryCount > 0)
            {
                LOGY_INFO("not recv frame durring decoding.retryCount = %d", nRetryCount);
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
            else
            {
                LOGY_ERROR("not recv frame durring failed!!");
                av_frame_free(&pFrame);
                return NULL;
            }
        }
        else
        {
            break;
        }

        nRetryCount--;
    }

    return pFrame;
}

void IDecode::Close()
{
    if(m_pCodecCtx)
    {
        avcodec_close(m_pCodecCtx);
        avcodec_free_context(&m_pCodecCtx);
    }
}

void IDecode::CheckHardSupport()
{
    enum AVHWDeviceType print_type = AV_HWDEVICE_TYPE_NONE;

    // 遍历出设备支持的硬件类型；对于MAC来说就是AV_HWDEVICE_TYPE_VIDEOTOOLBOX
    while((print_type = av_hwdevice_iterate_types(print_type)) != AV_HWDEVICE_TYPE_NONE)
    {
        LOGY_DEBUG("suport devices %s", av_hwdevice_get_type_name(print_type));
    }
}

void IDecode::Render(AVFrame* pFrame, bool bNeedFree)
{

}

void IDecode::Flush()
{
    if(m_pCodecCtx)
    {
        avcodec_flush_buffers(m_pCodecCtx);
    }
}

const AVCodecContext* IDecode::GetCodecCtx()
{
    return m_pCodecCtx;
}