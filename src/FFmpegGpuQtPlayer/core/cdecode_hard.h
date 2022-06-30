#pragma once
#include "idecode.h"
//#define USE_TEST_DEMO
struct AVBufferRef;
class CDecodeHard: public IDecode
{
public:
    CDecodeHard();
    ~CDecodeHard();

    //打开解码器,不管成功与否并释放para空间
    int Open(AVCodecParameters* pParam) override;

    //发送到解码线程,不管成功与否并释放pkt空间（对象和媒体内容
    int Send(AVPacket* pPacket, bool bNeedFree) override;

    //获取解码后数据，一次send可能需要Recv，最后获取缓冲中的数据Send NULL 再Recv多次
    //每次复制一份，有调用者释放 av_frame_free
    AVFrame* Recv() override;

    void Close()override;

    #ifdef USE_TEST_DEMO
    //< 测试
    void Test(std::string srcPath);
    AVFrame* Test(AVPacket* pPacket);
    AVFrame* decode(AVCodecContext* ctx, AVPacket* packet);
    #endif // USE_TEST_DEMO
private:
    AVBufferRef* hw_device_ctx = NULL;
};

