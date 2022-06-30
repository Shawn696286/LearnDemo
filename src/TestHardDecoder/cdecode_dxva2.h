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
    //�򿪽�����,���ܳɹ�����ͷ�para�ռ�
    int Open(AVCodecParameters* pParam, CD3dDxva2Render* pDxva2Render, bool bNeedFreeParam = true) override;

    //���͵������߳�,���ܳɹ�����ͷ�pkt�ռ䣨�����ý������
    //int Send(AVPacket* pPacket) override;

    //��ȡ��������ݣ�һ��send������ҪRecv������ȡ�����е�����Send NULL ��Recv���
    //ÿ�θ���һ�ݣ��е������ͷ� av_frame_free
    //AVFrame* Recv() override;

    void Close()override;

    //< ��Ⱦ
    void Render(AVFrame* pFrame, bool bNeedFree)override;
private:
    int dxva2_retrieve_data(AVCodecContext* s, AVFrame* frame);
private:
    IDirect3DSurface9* m_pBackBuffer;

    RECT m_oRectViewport;

    CD3dDxva2Render* m_pDxva2Render;
};

