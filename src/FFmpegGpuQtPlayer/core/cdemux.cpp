#include "cdemux.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/pixfmt.h>
#include <libavutil/error.h>
}

#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#ifdef USE_TEST_DEMO
    AVCodec* g_decoder = NULL;
    AVFormatContext* g_pFmtCtx = NULL;
    int g_nVStreamIndex = 0;
#endif // USE_TEST_DEMO
CDemux::CDemux()
{
    m_pFmtCtx = nullptr;
}

CDemux::~CDemux()
{
}

int CDemux::Open(std::string strFilepath)
{
    int nRet = avformat_open_input(&m_pFmtCtx, strFilepath.c_str(), NULL, NULL);

    if(nRet < 0)
    {
        LOGY_DEBUG("avformat_open_input fail %d", nRet);
        return Ret_Y_Error;
    }

    //获取流信息
    nRet = avformat_find_stream_info(m_pFmtCtx, NULL);

    if(nRet < 0)
    {
        LOGY_DEBUG("avformat_find_stream_info fail %d", nRet);
        return Ret_Y_Error;
    }

    //获取视频流

    #ifdef USE_TEST_DEMO
    m_nVStreamIndex = av_find_best_stream(m_pFmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, (const AVCodec**)&g_decoder, 0);
    g_nVStreamIndex = m_nVStreamIndex;
    g_pFmtCtx = m_pFmtCtx;
    #else
    m_nVStreamIndex = av_find_best_stream(m_pFmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    #endif // USE_TEST_DEMO

    //获取音频流
    m_nAStreamIndex = av_find_best_stream(m_pFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    //打印视频流详细信息
    av_dump_format(m_pFmtCtx, 0, strFilepath.c_str(), 0);

    return Ret_Y_OK;
}

AVPacket* CDemux::Read()
{
    if(!m_pFmtCtx)
    {
        return NULL;
    }

    AVPacket* pPacket = av_packet_alloc();

    //读取一帧，并分配空间
    int ret = av_read_frame(m_pFmtCtx, pPacket);

    if(ret != 0)
    {
        av_packet_free(&pPacket);
        return NULL;
    }

    return pPacket;
}

AVPacket* CDemux::ReadVideo()
{
    if(!m_pFmtCtx)
    {
        return NULL;
    }

    AVPacket* pPacket = NULL;

    for(int i = 0; i < 40; ++i)
    {
        pPacket = Read();

        if(!pPacket)
        {
            break;
        }

        if(pPacket->stream_index == m_nVStreamIndex)
        {
            break;
        }

        av_packet_free(&pPacket);
    }

    return pPacket;
}

AVCodecParameters* CDemux::CopyVPara()
{
    if(!m_pFmtCtx)
    {
        return NULL;
    }

    AVCodecParameters* pa = avcodec_parameters_alloc();
    avcodec_parameters_copy(pa, m_pFmtCtx->streams[m_nVStreamIndex]->codecpar);
    return pa;
}

AVCodecParameters* CDemux::CopyAPara()
{
    if(!m_pFmtCtx)
    {
        return NULL;
    }

    AVCodecParameters* pa = avcodec_parameters_alloc();
    avcodec_parameters_copy(pa, m_pFmtCtx->streams[m_nAStreamIndex]->codecpar);
    return pa;
}

int CDemux::GetWidth()
{
    if(!m_pFmtCtx)
    {
        return NULL;
    }

    return m_pFmtCtx->streams[m_nVStreamIndex]->codecpar->width;
}

int CDemux::GetHeight()
{
    if(!m_pFmtCtx)
    {
        return NULL;
    }

    return m_pFmtCtx->streams[m_nVStreamIndex]->codecpar->height;
}

void CDemux::Close()
{
    if(m_pFmtCtx)
    {
        avformat_close_input(&m_pFmtCtx);
        m_pFmtCtx = nullptr;
    }
}