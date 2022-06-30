#pragma once
#include "public.h"
struct AVCodecParameters;
struct AVCodecContext;
struct AVPacket;
struct AVFrame;
class CD3dDxva2Render;

class IDecode
{
public:
    IDecode();
    virtual~IDecode();
    virtual void Init(int nSurfaceCount);

    //�򿪽�����,���ܳɹ�����ͷ�para�ռ�
    virtual int Open(AVCodecParameters* pParam);

    virtual int Open(AVCodecParameters* pParam, CD3dDxva2Render* pDxva2Ctx, bool bNeedFrameParam = true);

    //���͵������߳�,���ܳɹ�����ͷ�pkt�ռ䣨�����ý������
    virtual int Send(AVPacket* pPacket, bool bNeedFree);

    //��ȡ��������ݣ�һ��send������ҪRecv������ȡ�����е�����Send NULL ��Recv���
    //ÿ�θ���һ�ݣ��е������ͷ� av_frame_free
    virtual AVFrame* Recv();

    //< �رս�����
    virtual void Close();

    //< ����豸֧�ֵ�Ӳ������
    void CheckHardSupport();

    //< ����豸֧�ֵ�Ӳ������
    virtual void Render(AVFrame* pFrame, bool bNeedFree);
    void Flush();

    const AVCodecContext* GetCodecCtx();
protected:
    AVCodecContext* m_pCodecCtx;
    int m_nSurfaceCount;
};

