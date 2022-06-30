#include "cdecode_hard.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/pixfmt.h>
#include <libavutil/error.h>
}
using namespace::std;

#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")

AVPixelFormat hw_device_pixel;
#ifdef USE_TEST_DEMO
    extern AVCodec* g_decoder;
    extern AVFormatContext* g_pFmtCtx;
    extern int g_nVStreamIndex;
#endif // USE_TEST_DEMO

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

CDecodeHard::CDecodeHard()
{
    CheckHardSupport();
}

CDecodeHard::~CDecodeHard()
{
}

int CDecodeHard::Open(AVCodecParameters* pParam)
{
    int nRet = Ret_Y_Error;

    if(!pParam)
    {
        return nRet;
    }

    enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    type = av_hwdevice_find_type_by_name("dxva2");

    do
    {
        //�ҵ�������
        AVCodec* pVCodec = (AVCodec*)avcodec_find_decoder(pParam->codec_id);

        if(!pVCodec)
        {
            LOGY_ERROR("can't find the codec_id = %d", pParam->codec_id);
            break;
        }

        LOGY_INFO("finded the codec_id = %d", pParam->codec_id);

        // ���ݽ�������ȡ֧�ִ˽��뷽ʽ��Ӳ�����ټ�
        /** ����֧�ֵ�Ӳ��������������AVCodec��hw_configs�����С�����Ӳ����������˵���ǵ�����AVCodec
        */
        //for(int i = 0;; i++)
        //{
        //    const AVCodecHWConfig* hwcodec = avcodec_get_hw_config(pVCodec, i);

        //    if(hwcodec == NULL)
        //    {
        //        break;
        //    }

        //    // ����һ����������Ӧ�Ŷ��Ӳ�����ٷ�ʽ���������ｫ����ѡ����
        //    if(hwcodec->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX && hwcodec->device_type == type)
        //    {
        //        hw_device_pixel = hwcodec->pix_fmt;
        //    }
        //}
        hw_device_pixel = AV_PIX_FMT_DXVA2_VLD;

        m_pCodecCtx = avcodec_alloc_context3(pVCodec);

        if(!m_pCodecCtx)
        {
            LOGY_ERROR("avcodec_alloc_context3 fail");
            break;
        }

        // ����������ֵ������ز���
        if(avcodec_parameters_to_context(m_pCodecCtx, pParam) < 0)
        {
            LOGY_ERROR("avcodec_parameters_to_context fail");
            break;
        }

        // ���û�ȡӲ�����������ظ�ʽ�ĺ������ú���ʵ���Ͼ��ǽ�AVCodec��AVHWCodecConfig�е�pix_fmt����
        m_pCodecCtx->get_format = hw_get_format;

        // ����Ӳ���������Ļ�����
        nRet = av_hwdevice_ctx_create(&hw_device_ctx, type, NULL, NULL, 0);

        if(nRet < 0)
        {
            char pBufError[4096] = { 0 };

            if(0 != av_strerror(nRet, pBufError, 4096))
            {
                LOGY_ERROR("av_strerror fail");
            }

            LOGY_ERROR("av_hwdevice_ctx_create fail,ret = %d,errStr = %s", nRet, pBufError);
            break;
        }

        /** ���ʹ���������Ĭ����һ�������Ļ�����(��ȡAVFrame��)����Ӳ��������Ҫ���ⴴ��Ӳ������Ļ�����
            �������������Ϊhw_frames_ctx�����ֶ����������ڵ���avcodec_send_packet()�����ڲ��Զ�����һ��
            ���Ǳ����ֶ���ֵӲ�����뻺��������hw_device_ctx(����һ��AVBufferRef����)
        */
        // ��hw_device_ctx��ֵ��ʹ��Ӳ������
        m_pCodecCtx->hw_device_ctx = av_buffer_ref(hw_device_ctx);

        // ��ʼ�����򿪽�����������
        if(avcodec_open2(m_pCodecCtx, pVCodec, NULL) < 0)
        {
            LOGY_DEBUG("avcodec_open2 fail");
            break;
        }

        nRet = Ret_Y_OK;
    } while(0);

    avcodec_parameters_free(&pParam);
    return nRet;
}

int CDecodeHard::Send(AVPacket* pPacket, bool bNeedFree)
{
    int nRet = Ret_Y_Error;

    if(!pPacket)
    {
        return nRet;
    }

    do
    {
        if(pPacket->size <= 0 || !pPacket->data)
        {
            break;
        }

        if(!m_pCodecCtx)
        {
            break;
        }

        nRet = avcodec_send_packet(m_pCodecCtx, pPacket);

        if(nRet != 0)
        {
            char pBufError[4096] = { 0 };

            if(0 != av_strerror(nRet, pBufError, 4096))
            {
                LOGY_ERROR("av_strerror fail");
            }

            LOGY_ERROR("avcodec_send_packet fail,ret = %d,errStr = %s", nRet, pBufError);
            break;
        }

        nRet = Ret_Y_OK;
    } while(0);

    if(bNeedFree)
    {
        av_packet_free(&pPacket);
    }

    return nRet;
}

AVFrame* CDecodeHard::Recv()
{
    if(!m_pCodecCtx)
    {
        return nullptr;
    }

    AVFrame* pFrame = av_frame_alloc();
    int ret = avcodec_receive_frame(m_pCodecCtx, pFrame);

    if(ret != 0)
    {
        av_frame_free(&pFrame);
        return nullptr;
    }

    if(pFrame->format == hw_device_pixel)
    {
        //������õ�Ӳ�����ټ��������avcodec_receive_frame()�����󣬽��������ݻ���GPU�У�������Ҫͨ���˺���
        //��GPU�е�����ת�Ƶ�CPU����

        AVFrame* pFrameSW = av_frame_alloc();

        if((ret = av_hwframe_transfer_data(pFrameSW, pFrame, 0)) < 0)
        {
            LOGY_DEBUG("av_hwframe_transfer_data fail %d", ret);
            av_frame_free(&pFrame);
            av_frame_free(&pFrameSW);
            return nullptr;
        }

        av_frame_free(&pFrame);
        return pFrameSW;
    }

    return pFrame;
}

void CDecodeHard::Close()
{

}
#ifdef USE_TEST_DEMO

#define USE_HARD_DEVICE 1

AVFrame* CDecodeHard::decode(AVCodecContext* ctx, AVPacket* packet)
{
    int ret = 0;
    static int sum = 0;

    if((ret = avcodec_send_packet(ctx, packet)) < 0)
    {
        LOGY_DEBUG("avcodec_send_packet");
        return  nullptr;
    }

    AVFrame* hw_frame = av_frame_alloc();
    AVFrame* sw_Frame = av_frame_alloc();
    AVFrame* tmp_frame = NULL;

    while(true)
    {
        ret = avcodec_receive_frame(ctx, hw_frame);

        if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            LOGY_DEBUG("need more packet");
            av_frame_free(&hw_frame);
            av_frame_free(&sw_Frame);
            return nullptr;
        }
        else if(ret < 0)
        {
            av_frame_free(&hw_frame);
            av_frame_free(&sw_Frame);
            return nullptr;
        }

        #if USE_HARD_DEVICE

        if(hw_frame->format == hw_device_pixel)
        {
            //������õ�Ӳ�����ټ��������avcodec_receive_frame()�����󣬽��������ݻ���GPU�У�������Ҫͨ���˺���
            //��GPU�е�����ת�Ƶ�CPU����
            if((ret = av_hwframe_transfer_data(sw_Frame, hw_frame, 0)) < 0)
            {
                LOGY_DEBUG("av_hwframe_transfer_data fail %d", ret);
                av_frame_free(&hw_frame);
                av_frame_free(&sw_Frame);
                return nullptr;
            }

            LOGY_DEBUG("����2222 ����ɹ� %d", sum);
            tmp_frame = sw_Frame;
            av_frame_free(&hw_frame);
            return tmp_frame;
        }
        else
        {
            LOGY_DEBUG("����1111 ����ɹ� %d", sum);
            tmp_frame = hw_frame;
            av_frame_free(&hw_frame);
            return tmp_frame;
        }

        #else

        LOGY_DEBUG("����3333 ����ɹ� %d", sum);
        #endif
        sum++;
    }

}
void CDecodeHard::Test(std::string srcPath)
{
    //string srcPath = "D:/workspace/resource/ZeddIgniteWorlds.mp4";//srcDic + "test_1280x720_3.mp4";

    AVCodecContext* decoder_Ctx = NULL;
    AVFormatContext* in_fmtCtx = NULL;
    int video_stream_index = -1;
    AVCodec* decoder = NULL;
    int ret = 0;
    enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    enum AVHWDeviceType print_type = AV_HWDEVICE_TYPE_NONE;
    AVBufferRef* hw_device_ctx = NULL;

    type = av_hwdevice_find_type_by_name("dxva2");

    // �������豸֧�ֵ�Ӳ�����ͣ�����MAC��˵����AV_HWDEVICE_TYPE_VIDEOTOOLBOX
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

    // ���һ������Ŀǰδ���壬��д0 ����
    // �ҵ�ָ�������͵�����Ϣ�����ҳ�ʼ��codec(���codecû��ֵ)
    if((ret = av_find_best_stream(in_fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, (const AVCodec**)&decoder, 0)) < 0)
    {
        LOGY_DEBUG("av_find_best_stream fail %d", ret);
        return;
    }

    video_stream_index = ret;

    // ���ݽ�������ȡ֧�ִ˽��뷽ʽ��Ӳ�����ټ�
    /** ����֧�ֵ�Ӳ��������������AVCodec��hw_configs�����С�����Ӳ����������˵���ǵ�����AVCodec
    */
    for(int i = 0;; i++)
    {
        const AVCodecHWConfig* hwcodec = avcodec_get_hw_config(decoder, i);

        if(hwcodec == NULL)
        {
            break;
        }

        // ����һ����������Ӧ�Ŷ��Ӳ�����ٷ�ʽ���������ｫ����ѡ����
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

    // ����������ֵ������ز���
    if(avcodec_parameters_to_context(decoder_Ctx, video_stream->codecpar) < 0)
    {
        LOGY_DEBUG("avcodec_parameters_to_context fail");
        return;
    }

    #if USE_HARD_DEVICE
    // ���û�ȡӲ�����������ظ�ʽ�ĺ������ú���ʵ���Ͼ��ǽ�AVCodec��AVHWCodecConfig�е�pix_fmt����
    decoder_Ctx->get_format = hw_get_format;

    // ����Ӳ���������Ļ�����
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

    /** ���ʹ���������Ĭ����һ�������Ļ�����(��ȡAVFrame��)����Ӳ��������Ҫ���ⴴ��Ӳ������Ļ�����
        �������������Ϊhw_frames_ctx�����ֶ����������ڵ���avcodec_send_packet()�����ڲ��Զ�����һ��
        ���Ǳ����ֶ���ֵӲ�����뻺��������hw_device_ctx(����һ��AVBufferRef����)
    */
    // ��hw_device_ctx��ֵ��ʹ��Ӳ������
    decoder_Ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx);
    #endif

    // ��ʼ�����򿪽�����������
    if(avcodec_open2(decoder_Ctx, decoder, NULL) < 0)
    {
        LOGY_DEBUG("avcodec_open2 fail");
        return;
    }


    /** ��¼��ʱ
        1��ʹ��Ӳ�������ĴΣ���ʱ���£�10.65 s,10.66s,10.75s,10.68s
        2��ʹ����������ĴΣ���ʱ���£�8.21s,8.02s,10.33s,8.00s
        ���ۣ�����MAC��˵����������ʱ��Ӳ���٣�����ʱ�䲨����
    */
    auto u64TimeStart = CUtilY::TimeGetCurrentMilli();
    AVPacket* packet = av_packet_alloc();

    while(av_read_frame(in_fmtCtx, packet) >= 0)
    {

        if(video_stream_index == packet->stream_index)
        {

            // ��ʼ����
            decode(decoder_Ctx, packet);
        }

        av_packet_unref(packet);
    }

    decode(decoder_Ctx, NULL);

    auto u64TimeEnd = CUtilY::TimeGetCurrentMilli();
    LOGY_DEBUG("�����ʱ %llu ms", u64TimeEnd - u64TimeStart);

    avformat_close_input(&in_fmtCtx);
    avcodec_free_context(&decoder_Ctx);
    av_buffer_unref(&hw_device_ctx);
}

AVFrame* CDecodeHard::Test(AVPacket* pPacket)
{
    static bool bFirst = true;

    static AVCodecContext* decoder_Ctx = NULL;
    static  int video_stream_index = -1;
    static AVCodec* decoder = NULL;
    static int ret = 0;
    static enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    static enum AVHWDeviceType print_type = AV_HWDEVICE_TYPE_NONE;
    static AVBufferRef* hw_device_ctx = NULL;

    if(bFirst)
    {
        bFirst = false;
        type = av_hwdevice_find_type_by_name("dxva2");

        // �������豸֧�ֵ�Ӳ�����ͣ�����MAC��˵����AV_HWDEVICE_TYPE_VIDEOTOOLBOX
        while((print_type = av_hwdevice_iterate_types(print_type)) != AV_HWDEVICE_TYPE_NONE)
        {
            LOGY_DEBUG("suport devices %s", av_hwdevice_get_type_name(print_type));
        }

        decoder = g_decoder;
        video_stream_index = ret;

        // ���ݽ�������ȡ֧�ִ˽��뷽ʽ��Ӳ�����ټ�
        /** ����֧�ֵ�Ӳ��������������AVCodec��hw_configs�����С�����Ӳ����������˵���ǵ�����AVCodec
        */
        for(int i = 0;; i++)
        {
            const AVCodecHWConfig* hwcodec = avcodec_get_hw_config(decoder, i);

            if(hwcodec == NULL)
            {
                break;
            }

            // ����һ����������Ӧ�Ŷ��Ӳ�����ٷ�ʽ���������ｫ����ѡ����
            if(hwcodec->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX && hwcodec->device_type == type)
            {
                hw_device_pixel = hwcodec->pix_fmt;
            }
        }

        if((decoder_Ctx = avcodec_alloc_context3(decoder)) == NULL)
        {
            LOGY_DEBUG("avcodec_alloc_context3 fail");
            return nullptr;
        }


        // ����������ֵ������ز���
        if(avcodec_parameters_to_context(decoder_Ctx, g_pFmtCtx->streams[g_nVStreamIndex]->codecpar) < 0)
        {
            LOGY_DEBUG("avcodec_parameters_to_context fail");
            return nullptr;
        }

        #if USE_HARD_DEVICE
        // ���û�ȡӲ�����������ظ�ʽ�ĺ������ú���ʵ���Ͼ��ǽ�AVCodec��AVHWCodecConfig�е�pix_fmt����
        decoder_Ctx->get_format = hw_get_format;

        // ����Ӳ���������Ļ�����
        int nRet = av_hwdevice_ctx_create(&hw_device_ctx, type, NULL, NULL, 0);

        if(nRet < 0)
        {
            char pBufError[4096] = { 0 };

            if(0 != av_strerror(nRet, pBufError, 4096))
            {
                LOGY_DEBUG("av_strerror fail");
            }

            LOGY_DEBUG("av_hwdevice_ctx_create fail,ret = %d,errStr = %s", nRet, pBufError);
            return nullptr;
        }

        /** ���ʹ���������Ĭ����һ�������Ļ�����(��ȡAVFrame��)����Ӳ��������Ҫ���ⴴ��Ӳ������Ļ�����
            �������������Ϊhw_frames_ctx�����ֶ����������ڵ���avcodec_send_packet()�����ڲ��Զ�����һ��
            ���Ǳ����ֶ���ֵӲ�����뻺��������hw_device_ctx(����һ��AVBufferRef����)
        */
        // ��hw_device_ctx��ֵ��ʹ��Ӳ������
        decoder_Ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx);
        #endif

        // ��ʼ�����򿪽�����������
        if(avcodec_open2(decoder_Ctx, decoder, NULL) < 0)
        {
            LOGY_DEBUG("avcodec_open2 fail");
            return nullptr;
        }

    }

    /** ��¼��ʱ
        1��ʹ��Ӳ�������ĴΣ���ʱ���£�10.65 s,10.66s,10.75s,10.68s
        2��ʹ����������ĴΣ���ʱ���£�8.21s,8.02s,10.33s,8.00s
        ���ۣ�����MAC��˵����������ʱ��Ӳ���٣�����ʱ�䲨����
    */

    auto u64TimeStart = CUtilY::TimeGetCurrentMilli();
    AVPacket* packet = pPacket;// av_packet_alloc();
    AVFrame* pf = nullptr;
    //while(av_read_frame(in_fmtCtx, packet) >= 0)
    {

        if(video_stream_index == packet->stream_index)
        {

            // ��ʼ����
            pf = decode(decoder_Ctx, packet);
        }

        av_packet_unref(packet);
        return pf;
    }

    //decode(decoder_Ctx, NULL);

    //auto u64TimeEnd = CUtilY::TimeGetCurrentMilli();
    //LOGY_DEBUG("�����ʱ %llu ms", u64TimeEnd - u64TimeStart);

    //avcodec_free_context(&decoder_Ctx);
    //av_buffer_unref(&hw_device_ctx);

}
#endif // USE_TEST_DEMO