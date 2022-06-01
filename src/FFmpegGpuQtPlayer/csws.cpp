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
                (m_pSwsCtx,//传NULL会新创建
                 pFrame->width, pFrame->height,//输入的宽高
                 (AVPixelFormat)pFrame->format,//输入格式 YUV420p
                 outwidth, outheight,//输出的宽高
                 AV_PIX_FMT_BGRA,//输出的格式RGBA
                 SWS_BICUBIC,//尺寸变化的算法
                 0, 0, 0
                );

    if(!m_pSwsCtx)
    {
        LOGY_ERROR("像素格式尺寸转换上下文创建或获取失败！");
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
