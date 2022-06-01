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

    //打开解码器,不管成功与否并释放para空间
    virtual int Open(AVCodecParameters* pParam);

    //发送到解码线程,不管成功与否并释放pkt空间（对象和媒体内容
    virtual int Send(AVPacket* pPacket);

    //获取解码后数据，一次send可能需要Recv，最后获取缓冲中的数据Send NULL 再Recv多次
    //每次复制一份，有调用者释放 av_frame_free
    virtual AVFrame* Recv();

    virtual void Close();
private:
    AVCodecContext* m_pCodecCtx;
};

