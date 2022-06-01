#include "hard_decoder.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/pixfmt.h>
#include <libavutil/error.h>
}
using namespace::std;

enum AVPixelFormat hw_device_pixel;
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")

HardEnDecoder::HardEnDecoder()
{
    auto pStrinfo = av_version_info();
    int a = 0;
}
enum AVPixelFormat hw_get_format(AVCodecContext* ctx, const enum AVPixelFormat* fmts)
{
    const enum AVPixelFormat* p;

    for(p = fmts; *p != AV_PIX_FMT_NONE; p++)
    {
        if(*p == hw_device_pixel)
        {
            return *p;
        }
    }

    return AV_PIX_FMT_NONE;
}

static void decode(AVCodecContext* ctx, AVPacket* packet)
{
    AVFrame* hw_frame = av_frame_alloc();
    static AVFrame* sw_Frame = av_frame_alloc();
    AVFrame* tmp_frame = NULL;
    int ret = 0;
    static int sum = 0;

    if((ret = avcodec_send_packet(ctx, packet)) < 0)
    {
        LOGY_DEBUG("avcodec_send_packet");
        return;
    }

    while(true)
    {
        ret = avcodec_receive_frame(ctx, hw_frame);

        if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            LOGY_DEBUG("need more packet");
            av_frame_free(&hw_frame);
            return;
        }
        else if(ret < 0)
        {
            return;
        }

        #if USE_HARD_DEVICE

        if(hw_frame->format == hw_device_pixel)
        {
            // 如果采用的硬件加速剂，则调用avcodec_receive_frame()函数后，解码后的数据还在GPU中，所以需要通过此函数
            // 将GPU中的数据转移到CPU中来
            //if((ret = av_hwframe_transfer_data(sw_Frame, hw_frame, 0)) < 0)
            //{
            //    LOGY_DEBUG("av_hwframe_transfer_data fail %d", ret);
            //    return;
            //}

            LOGY_DEBUG("这里2222 解码成功 %d", sum);
            tmp_frame = sw_Frame;
        }
        else
        {
            LOGY_DEBUG("这里1111 解码成功 %d", sum);
            tmp_frame = hw_frame;
        }

        #else

        LOGY_DEBUG("这里3333 解码成功 %d", sum);
        #endif
        sum++;
    }

}

void HardEnDecoder::doDecode()
{
    #if 1
    string curFile(__FILE__);
    unsigned long pos = curFile.find("1-video_encode_decode");

    if(pos == string::npos)
    {
        LOGY_DEBUG("file not found");
        return;
    }

    string srcDic = curFile.substr(0, pos) + "filesources/";
    string srcPath = "D:/workspace/resource/ZeddIgniteWorlds.mp4";//srcDic + "test_1280x720_3.mp4";

    AVCodecContext* decoder_Ctx = NULL;
    AVFormatContext* in_fmtCtx = NULL;
    int video_stream_index = -1;
    AVCodec* decoder = NULL;
    int ret = 0;
    enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    enum AVHWDeviceType print_type = AV_HWDEVICE_TYPE_NONE;
    AVBufferRef* hw_device_ctx = NULL;

    type = av_hwdevice_find_type_by_name("dxva2");

    // 遍历出设备支持的硬件类型；对于MAC来说就是AV_HWDEVICE_TYPE_VIDEOTOOLBOX
    while((print_type = av_hwdevice_iterate_types(print_type)) != AV_HWDEVICE_TYPE_NONE)
    {
        LOGY_DEBUG("suport devices %s", av_hwdevice_get_type_name(print_type));
    }

    if((ret = avformat_open_input(&in_fmtCtx, srcPath.c_str(), NULL, NULL)) < 0)
    {
        LOGY_DEBUG("avformat_open_input fail %d", ret);
        return;
    }

    if((ret = avformat_find_stream_info(in_fmtCtx, NULL)) < 0)
    {
        LOGY_DEBUG("avformat_find_stream_info fail %d", ret);
        return;
    }

    // 最后一个参数目前未定义，填写0 即可
    // 找到指定流类型的流信息，并且初始化codec(如果codec没有值)
    if((ret = av_find_best_stream(in_fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, (const AVCodec**)&decoder, 0)) < 0)
    {
        LOGY_DEBUG("av_find_best_stream fail %d", ret);
        return;
    }

    video_stream_index = ret;

    // 根据解码器获取支持此解码方式的硬件加速计
    /** 所有支持的硬件解码器保存在AVCodec的hw_configs变量中。对于硬件编码器来说又是单独的AVCodec
    */
    for(int i = 0;; i++)
    {
        const AVCodecHWConfig* hwcodec = avcodec_get_hw_config(decoder, i);

        if(hwcodec == NULL)
        {
            break;
        }

        // 可能一个解码器对应着多个硬件加速方式，所以这里将其挑选出来
        if(hwcodec->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX && hwcodec->device_type == type)
        {
            hw_device_pixel = hwcodec->pix_fmt;
        }
    }

    if((decoder_Ctx = avcodec_alloc_context3(decoder)) == NULL)
    {
        LOGY_DEBUG("avcodec_alloc_context3 fail");
        return;
    }

    AVStream* video_stream = in_fmtCtx->streams[video_stream_index];

    // 给解码器赋值解码相关参数
    if(avcodec_parameters_to_context(decoder_Ctx, video_stream->codecpar) < 0)
    {
        LOGY_DEBUG("avcodec_parameters_to_context fail");
        return;
    }

    #if USE_HARD_DEVICE
    // 配置获取硬件加速器像素格式的函数；该函数实际上就是将AVCodec中AVHWCodecConfig中的pix_fmt返回
    decoder_Ctx->get_format = hw_get_format;

    // 创建硬件加速器的缓冲区
    int nRet = av_hwdevice_ctx_create(&hw_device_ctx, type, NULL, NULL, 0);

    if(nRet < 0)
    {
        char pBufError[4096] = { 0 };

        if(0 != av_strerror(nRet, pBufError, 4096))
        {
            LOGY_DEBUG("av_strerror fail");
        }

        LOGY_DEBUG("av_hwdevice_ctx_create fail,ret = %d,errStr = %s", nRet, pBufError);
        return;
    }

    /** 如果使用软解码则默认有一个软解码的缓冲区(获取AVFrame的)，而硬解码则需要额外创建硬件解码的缓冲区
        这个缓冲区变量为hw_frames_ctx，不手动创建，则在调用avcodec_send_packet()函数内部自动创建一个
        但是必须手动赋值硬件解码缓冲区引用hw_device_ctx(它是一个AVBufferRef变量)
    */
    // 即hw_device_ctx有值则使用硬件解码
    decoder_Ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx);
    #endif

    // 初始化并打开解码器上下文
    if(avcodec_open2(decoder_Ctx, decoder, NULL) < 0)
    {
        LOGY_DEBUG("avcodec_open2 fail");
        return;
    }


    /** 记录耗时
        1、使用硬件解码四次，耗时如下：10.65 s,10.66s,10.75s,10.68s
        2、使用软件解码四次，耗时如下：8.21s,8.02s,10.33s,8.00s
        结论：对于MAC来说，软件解码耗时比硬件少，但是时间波动大？
    */
    auto u64TimeStart = CUtilY::TimeGetCurrentMilli();
    AVPacket* packet = av_packet_alloc();

    while(av_read_frame(in_fmtCtx, packet) >= 0)
    {

        if(video_stream_index == packet->stream_index)
        {

            // 开始解码
            decode(decoder_Ctx, packet);
        }

        av_packet_unref(packet);
    }

    decode(decoder_Ctx, NULL);

    auto u64TimeEnd = CUtilY::TimeGetCurrentMilli();
    LOGY_DEBUG("解码耗时 %llu ms", u64TimeEnd - u64TimeStart);

    avformat_close_input(&in_fmtCtx);
    avcodec_free_context(&decoder_Ctx);
    av_buffer_unref(&hw_device_ctx);
    #endif

}