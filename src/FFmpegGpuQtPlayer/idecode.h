#pragma once
#include "public.h"
struct AVCodecParameters;
struct AVCodecContext;
struct AVPacket;
struct AVFrame;

class IDecode
{
public:
    IDecode();
    virtual~IDecode();

    //�򿪽�����,���ܳɹ�����ͷ�para�ռ�
    virtual int Open(AVCodecParameters* pParam);

    //���͵������߳�,���ܳɹ�����ͷ�pkt�ռ䣨�����ý������
    virtual int Send(AVPacket* pPacket);

    //��ȡ��������ݣ�һ��send������ҪRecv������ȡ�����е�����Send NULL ��Recv���
    //ÿ�θ���һ�ݣ��е������ͷ� av_frame_free
    virtual AVFrame* Recv();

    virtual void Close();
private:
    AVCodecContext* m_pCodecCtx;
};

