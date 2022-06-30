#pragma once
#include "idecode.h"
//#define USE_TEST_DEMO
struct AVBufferRef;
class CDecodeHard: public IDecode
{
public:
    CDecodeHard();
    ~CDecodeHard();

    //�򿪽�����,���ܳɹ�����ͷ�para�ռ�
    int Open(AVCodecParameters* pParam) override;

    //���͵������߳�,���ܳɹ�����ͷ�pkt�ռ䣨�����ý������
    int Send(AVPacket* pPacket, bool bNeedFree) override;

    //��ȡ��������ݣ�һ��send������ҪRecv������ȡ�����е�����Send NULL ��Recv���
    //ÿ�θ���һ�ݣ��е������ͷ� av_frame_free
    AVFrame* Recv() override;

    void Close()override;

    #ifdef USE_TEST_DEMO
    //< ����
    void Test(std::string srcPath);
    AVFrame* Test(AVPacket* pPacket);
    AVFrame* decode(AVCodecContext* ctx, AVPacket* packet);
    #endif // USE_TEST_DEMO
private:
    AVBufferRef* hw_device_ctx = NULL;
};

