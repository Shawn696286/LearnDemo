#include "idecode.h"

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
IDecode::IDecode()
{
    m_pCodecCtx = nullptr;
}

IDecode::~IDecode()
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
        //�ҵ�������
        AVCodec* vcodec = (AVCodec*)avcodec_find_decoder(pParam->codec_id);

        if(!vcodec)
        {
            LOGY_ERROR("can't find the codec_id = %d", pParam->codec_id);
            nRet = Ret_Y_Error;
            break;
        }

        LOGY_INFO("finded the codec_id = %d", pParam->codec_id);

        //����������������
        m_pCodecCtx = avcodec_alloc_context3(vcodec);
        //���ý����������Ĳ���
        avcodec_parameters_to_context(m_pCodecCtx, pParam);

        //���߳̽���
        m_pCodecCtx->thread_count = 8;
        //�򿪽�����������
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

int IDecode::Send(AVPacket* pPacket)
{
    if(!pPacket)
    {
        return Ret_Y_Error;
    }

    if(pPacket->size <= 0 || !pPacket->data)
    {
        av_packet_free(&pPacket);
        return Ret_Y_Error;
    }

    if(!m_pCodecCtx)
    {
        av_packet_free(&pPacket);
        return Ret_Y_Error;
    }

    int nRet = avcodec_send_packet(m_pCodecCtx, pPacket);
    av_packet_free(&pPacket);

    if(nRet != 0)
    {
        return Ret_Y_Error;
    }

    return Ret_Y_OK;
}

AVFrame* IDecode::Recv()
{
    if(!m_pCodecCtx)
    {
        return NULL;
    }

    AVFrame* pFrame = av_frame_alloc();
    int ret = avcodec_receive_frame(m_pCodecCtx, pFrame);

    if(ret != 0)
    {
        av_frame_free(&pFrame);
        return NULL;
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