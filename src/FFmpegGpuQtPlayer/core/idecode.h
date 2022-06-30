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

    //打开解码器,不管成功与否并释放para空间
    virtual int Open(AVCodecParameters* pParam);

    virtual int Open(AVCodecParameters* pParam, CD3dDxva2Render* pDxva2Ctx, bool bNeedFrameParam = true);

    //发送到解码线程,不管成功与否并释放pkt空间（对象和媒体内容
    virtual int Send(AVPacket* pPacket, bool bNeedFree);

    //获取解码后数据，一次send可能需要Recv，最后获取缓冲中的数据Send NULL 再Recv多次
    //每次复制一份，有调用者释放 av_frame_free
    virtual AVFrame* Recv();

    //< 关闭解码器
    virtual void Close();

    //< 检测设备支持的硬件类型
    void CheckHardSupport();

    //< 检测设备支持的硬件类型
    virtual void Render(AVFrame* pFrame, bool bNeedFree);
    void Flush();

    const AVCodecContext* GetCodecCtx();
protected:
    AVCodecContext* m_pCodecCtx;
    int m_nSurfaceCount;
};

