#include "irender.h"
#include "csws.h"
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
IRender::IRender()
{
    m_pSws = new CSws;
}

IRender::~IRender()
{
    if(m_pSws)
    {
        delete m_pSws;
        m_pSws = nullptr;
    }
}


void IRender::YuvToRgb(AVFrame* pFrame, char* pBufOut, int nOutW, int nOutH)
{
    if(pBufOut)
    {
        m_pSws->YuvToRGB(pFrame, pBufOut, nOutW, nOutH);
    }

}

void IRender::FreeFrame(AVFrame* pFrame)
{
    if(pFrame)
    {
        av_frame_free(&pFrame);
    }
}