#pragma once
#include "idecode.h"
#include <windows.h>
//#define USE_TEST_DEMO
struct AVBufferRef;
struct IDirect3DSurface9;


class CDecodeDxva2: public IDecode
{
public:
    CDecodeDxva2();
    ~CDecodeDxva2();

    void Init(int nSurfaceCount) override;
    //打开解码器,不管成功与否并释放para空间
    int Open(AVCodecParameters* pParam, CD3dDxva2Render* pDxva2Render, bool bNeedFreeParam = true) override;

    //发送到解码线程,不管成功与否并释放pkt空间（对象和媒体内容
    //int Send(AVPacket* pPacket) override;

    //获取解码后数据，一次send可能需要Recv，最后获取缓冲中的数据Send NULL 再Recv多次
    //每次复制一份，有调用者释放 av_frame_free
    //AVFrame* Recv() override;

    void Close()override;

    //< 渲染
    void Render(AVFrame* pFrame, bool bNeedFree)override;
private:
    int dxva2_retrieve_data(AVCodecContext* s, AVFrame* frame);
private:
    IDirect3DSurface9* m_pBackBuffer;

    RECT m_oRectViewport;

    CD3dDxva2Render* m_pDxva2Render;
};

