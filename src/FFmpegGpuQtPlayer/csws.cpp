#include "csws.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/pixfmt.h>
#include <libavutil/error.h>
#include "libswscale/swscale.h"
}

#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib,"swscale.lib")
CSws::CSws()
{
    m_pSwsCtx = nullptr;
}

CSws::~CSws()
{
}

int CSws::YuvToRGB(AVFrame* pFrame, char* out, int outwidth, int outheight)
{
    m_pSwsCtx = sws_getCachedContext
                (m_pSwsCtx,//��NULL���´���
                 pFrame->width, pFrame->height,//����Ŀ��
                 (AVPixelFormat)pFrame->format,//�����ʽ YUV420p
                 outwidth, outheight,//����Ŀ��
                 AV_PIX_FMT_BGRA,//����ĸ�ʽRGBA
                 SWS_BICUBIC,//�ߴ�仯���㷨
                 0, 0, 0
                );

    if(!m_pSwsCtx)
    {
        LOGY_ERROR("���ظ�ʽ�ߴ�ת�������Ĵ������ȡʧ�ܣ�");
        return Ret_Y_Error;
    }

    uint8_t* data[AV_NUM_DATA_POINTERS] = { 0 };
    data[0] = (uint8_t*)out;
    int lines[AV_NUM_DATA_POINTERS] = { 0 };
    lines[0] = outwidth * 4;
    int ret = sws_scale(m_pSwsCtx,//
                        pFrame->data,
                        pFrame->linesize,
                        0,
                        pFrame->height,
                        data,
                        lines
                       );

    if(ret <= 0)
    {
        return Ret_Y_Error;
    }

    //cout << "sws_scale = " << ret << endl;

    return Ret_Y_OK;
}
