#include "cdecode_dxva2.h"
#include "cd3d_dxva2_render.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/pixfmt.h>
#include <libavutil/error.h>
#include <libavcodec/dxva2.h>
#include "libavutil/avassert.h"
}
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")

/*  define all the GUIDs used directly here,
    to avoid problems with inconsistent dxva2api.h versions in mingw-w64 and different MSVC version */
#include <initguid.h>
DEFINE_GUID(IID_IDirectXVideoDecoderService, 0xfc51a551, 0xd5e7, 0x11d9, 0xaf, 0x55, 0x00, 0x05, 0x4e, 0x43, 0xff,
            0x02);

DEFINE_GUID(DXVA2_ModeMPEG2_VLD, 0xee27417f, 0x5e28, 0x4e65, 0xbe, 0xea, 0x1d, 0x26, 0xb5, 0x08, 0xad, 0xc9);
DEFINE_GUID(DXVA2_ModeMPEG2and1_VLD, 0x86695f12, 0x340e, 0x4f04, 0x9f, 0xd3, 0x92, 0x53, 0xdd, 0x32, 0x74, 0x60);
DEFINE_GUID(DXVA2_ModeH264_E, 0x1b81be68, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(DXVA2_ModeH264_F, 0x1b81be69, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(DXVADDI_Intel_ModeH264_E, 0x604F8E68, 0x4951, 0x4C54, 0x88, 0xFE, 0xAB, 0xD2, 0x5C, 0x15, 0xB3, 0xD6);
DEFINE_GUID(DXVA2_ModeVC1_D, 0x1b81beA3, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(DXVA2_ModeVC1_D2010, 0x1b81beA4, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(DXVA2_ModeHEVC_VLD_Main, 0x5b11d51b, 0x2f4c, 0x4452, 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0);
DEFINE_GUID(DXVA2_ModeHEVC_VLD_Main10, 0x107af0e0, 0xef1a, 0x4d19, 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13);
DEFINE_GUID(DXVA2_ModeVP9_VLD_Profile0, 0x463707f8, 0xa1d0, 0x4585, 0x87, 0x6d, 0x83, 0xaa, 0x6d, 0x60, 0xb8, 0x9e);
DEFINE_GUID(DXVA2_NoEncrypt, 0x1b81beD0, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(GUID_NULL, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

//< surface最小数量
static const int AVAPI_MIN_SURFACE_COUNT = 16;

//< surface最大数量
static const int AVAPI_MAX_SURFACE_COUNT = 50;

struct dxva2_mode
{
    const GUID* guid;
    enum AVCodecID codec;
};

static const dxva2_mode dxva2_modes[] =
{
    /* MPEG-2 */
    { &DXVA2_ModeMPEG2_VLD, AV_CODEC_ID_MPEG2VIDEO },
    { &DXVA2_ModeMPEG2and1_VLD, AV_CODEC_ID_MPEG2VIDEO },

    /* H.264 */
    { &DXVA2_ModeH264_F, AV_CODEC_ID_H264 },
    { &DXVA2_ModeH264_E, AV_CODEC_ID_H264 },
    /* Intel specific H.264 mode */
    { &DXVADDI_Intel_ModeH264_E, AV_CODEC_ID_H264 },

    /* VC-1 / WMV3 */
    { &DXVA2_ModeVC1_D2010, AV_CODEC_ID_VC1 },
    { &DXVA2_ModeVC1_D2010, AV_CODEC_ID_WMV3 },
    { &DXVA2_ModeVC1_D, AV_CODEC_ID_VC1 },
    { &DXVA2_ModeVC1_D, AV_CODEC_ID_WMV3 },

    /* HEVC/H.265 */
    { &DXVA2_ModeHEVC_VLD_Main, AV_CODEC_ID_HEVC },
    { &DXVA2_ModeHEVC_VLD_Main10, AV_CODEC_ID_HEVC },

    /* VP8/9 */
    { &DXVA2_ModeVP9_VLD_Profile0, AV_CODEC_ID_VP9 },

    { NULL, AV_CODEC_ID_NONE },
};

struct SD3dFormat
{
    const char* pstrName;
    D3DFORMAT    oFformat;
    AVPixelFormat  eCodecFormat;
};

/* XXX Prefered format must come first */
static const SD3dFormat g_arrD3dFormats[] =
{
    { "YV12", (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), AV_PIX_FMT_YUV420P },
    { "NV12", (D3DFORMAT)MAKEFOURCC('N', 'V', '1', '2'), AV_PIX_FMT_NV12 },

    { NULL, (D3DFORMAT)0, AV_PIX_FMT_NONE }
};

static void calculate_display_rect(RECT* rect,
                                   int scr_xleft, int scr_ytop, int scr_width, int scr_height,
                                   int pic_width, int pic_height, AVRational pic_sar)
{
    float aspect_ratio;
    int width, height, x, y;

    if(pic_sar.num == 0)
    {
        aspect_ratio = 0;
    }
    else
    {
        aspect_ratio = av_q2d(pic_sar);
    }

    if(aspect_ratio <= 0.0)
    {
        aspect_ratio = 1.0;
    }

    aspect_ratio *= (float)pic_width / (float)pic_height;

    /* XXX: we suppose the screen has a 1.0 pixel ratio */
    height = scr_height;
    width = lrint(height * aspect_ratio) & ~1;

    if(width > scr_width)
    {
        width = scr_width;
        height = lrint(width / aspect_ratio) & ~1;
    }

    x = (scr_width - width) / 2;
    y = (scr_height - height) / 2;
    rect->left = scr_xleft + x;
    rect->top = scr_ytop + y;
    rect->right = rect->left + FFMAX(width, 1);
    rect->bottom = rect->top + FFMAX(height, 1);
}

int CDecodeDxva2::dxva2_retrieve_data(AVCodecContext* s, AVFrame* frame)
{
    LPDIRECT3DSURFACE9 surface = (LPDIRECT3DSURFACE9)frame->data[3];
    CD3dDxva2Render* pD3DDxva2Render = (CD3dDxva2Render*)s->opaque;
    DXVA2Context* pDxva2Ctx = pD3DDxva2Render->m_pDxva2Ctx;

    RECT rect = { 0 };

    pDxva2Ctx->pD3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    pDxva2Ctx->pD3d9Device->BeginScene();

    //if(m_pBackBuffer)
    //{
    //    m_pBackBuffer->Release();
    //    m_pBackBuffer = NULL;
    //}
    if(!m_pBackBuffer)
    {
        pDxva2Ctx->pD3d9Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
    }

    GetClientRect(pD3DDxva2Render->m_oD3dPresentParam.hDeviceWindow, &m_oRectViewport);

    calculate_display_rect(&rect, m_oRectViewport.left, m_oRectViewport.top, m_oRectViewport.right - m_oRectViewport.left,
                           m_oRectViewport.bottom - m_oRectViewport.top, frame->width, frame->height, frame->sample_aspect_ratio);

    RECT SourceRect = { 0, 0, ((~0 - 1) & frame->width), ((~0 - 1) & frame->height) };
    pDxva2Ctx->pD3d9Device->StretchRect(surface, &SourceRect, m_pBackBuffer, NULL, D3DTEXF_LINEAR);
    pDxva2Ctx->pD3d9Device->EndScene();
    pDxva2Ctx->pD3d9Device->Present(NULL, &rect, NULL, NULL);

    return 0;
}

static void dxva2_release_buffer(void* opaque, uint8_t* data)
{
    DXVA2SurfaceWrapper* w = (DXVA2SurfaceWrapper*)opaque;
    DXVA2Context* pDxvaCtx = w->ctx;
    int i;

    for(i = 0; i < pDxvaCtx->nSurfacesCount; i++)
    {
        if(pDxvaCtx->pSurfaces[i] == w->surface)
        {
            pDxvaCtx->pSurfaceInfos[i].used = 0;
            break;
        }
    }

    IDirect3DSurface9_Release(w->surface);
    //IDirectXVideoDecoder_Release(w->decoder);
    w->decoder->Release();

    if(w)
    {
        delete w;
    }
}

AVPixelFormat GetHwFormat(AVCodecContext* s, const AVPixelFormat* pix_fmts)
{
    CD3dDxva2Render* pD3DDxva2Render = (CD3dDxva2Render*)s->opaque;
    pD3DDxva2Render->active_hwaccel_id = HWACCEL_DXVA2;
    pD3DDxva2Render->hwaccel_pix_fmt = AV_PIX_FMT_DXVA2_VLD;
    return pD3DDxva2Render->hwaccel_pix_fmt;
}

static int dxva2_get_buffer(AVCodecContext* s, AVFrame* frame, int flags)
{
    CD3dDxva2Render* pD3DDxva2Render = (CD3dDxva2Render*)s->opaque;
    DXVA2Context* pDxva2Ctx = (DXVA2Context*)pD3DDxva2Render->m_pDxva2Ctx;
    int i, old_unused = -1;
    LPDIRECT3DSURFACE9 surface;
    DXVA2SurfaceWrapper* w = NULL;

    av_assert0(frame->format == AV_PIX_FMT_DXVA2_VLD);

    for(i = 0; i < pDxva2Ctx->nSurfacesCount; i++)
    {
        surface_info* info = &pDxva2Ctx->pSurfaceInfos[i];

        if(!info->used && (old_unused == -1 || info->age < pDxva2Ctx->pSurfaceInfos[old_unused].age))
        {
            old_unused = i;
        }
    }

    if(old_unused == -1)
    {
        LOGY_ERROR("No free DXVA2 surface!");
        return AVERROR(ENOMEM);
    }

    i = old_unused;

    surface = pDxva2Ctx->pSurfaces[i];

    w = new DXVA2SurfaceWrapper;

    if(!w)
    {
        LOGY_ERROR("new DXVA2SurfaceWrapper failed");
        return Ret_Y_Error;
    }

    memset(w, 0, sizeof(DXVA2SurfaceWrapper));
    frame->buf[0] = av_buffer_create((uint8_t*)surface, 0,
                                     dxva2_release_buffer, w,
                                     AV_BUFFER_FLAG_READONLY);

    if(!frame->buf[0])
    {
        if(w)
        {
            delete w;
        }

        return AVERROR(ENOMEM);
    }

    w->ctx = pDxva2Ctx;
    w->surface = surface;
    IDirect3DSurface9_AddRef(w->surface);
    w->decoder = pDxva2Ctx->pDecoder;
    //IDirectXVideoDecoder_AddRef(w->decoder);
    w->decoder->AddRef();

    pDxva2Ctx->pSurfaceInfos[i].used = 1;
    pDxva2Ctx->pSurfaceInfos[i].age = pDxva2Ctx->nSurfaceAge++;

    frame->data[3] = (uint8_t*)surface;

    return 0;
}


static const SD3dFormat* D3dFindFormat(D3DFORMAT format)
{
    for(unsigned i = 0; g_arrD3dFormats[i].pstrName; i++)
    {
        if(g_arrD3dFormats[i].oFformat == format)
        {
            return &g_arrD3dFormats[i];
        }
    }

    return NULL;
}
static int dxva2_get_decoder_configuration(AVCodecContext* s, const GUID* device_guid,
        const DXVA2_VideoDesc* desc, DXVA2_ConfigPictureDecode* config, DXVA2Context* pDxva2Ctx)
{
    unsigned cfg_count = 0, best_score = 0;
    DXVA2_ConfigPictureDecode* cfg_list = NULL;
    DXVA2_ConfigPictureDecode best_cfg = { { 0 } };
    HRESULT hr;

    //hr = IDirectXVideoDecoderService_GetDecoderConfigurations(ctx->decoder_service, device_guid, desc, NULL, &cfg_count, &cfg_list);
    hr = pDxva2Ctx->pDecoderService->GetDecoderConfigurations(*device_guid, desc, NULL, &cfg_count, &cfg_list);

    if(FAILED(hr))
    {
        LOGY_ERROR("Unable to retrieve decoder configurations");
        return AVERROR(EINVAL);
    }

    for(unsigned int i = 0; i < cfg_count; i++)
    {
        DXVA2_ConfigPictureDecode* cfg = &cfg_list[i];

        unsigned score;

        if(cfg->ConfigBitstreamRaw == 1)
        {
            score = 1;
        }
        else if(s->codec_id == AV_CODEC_ID_H264 && cfg->ConfigBitstreamRaw == 2)
        {
            score = 2;
        }
        else
        {
            continue;
        }

        if(IsEqualGUID(cfg->guidConfigBitstreamEncryption, DXVA2_NoEncrypt))
        {
            score += 16;
        }

        if(score > best_score)
        {
            best_score = score;
            best_cfg = *cfg;
        }
    }

    CoTaskMemFree(cfg_list);

    if(!best_score)
    {
        LOGY_ERROR("No valid decoder configuration available");
        return AVERROR(EINVAL);
    }

    *config = best_cfg;
    return 0;
}
CDecodeDxva2::CDecodeDxva2()
{
    m_pBackBuffer = nullptr;
    m_pDxva2Render = nullptr;
    m_nSurfaceCount = AVAPI_MIN_SURFACE_COUNT;
}

CDecodeDxva2::~CDecodeDxva2()
{
    if(m_pBackBuffer)
    {
        m_pBackBuffer->Release();
        m_pBackBuffer = NULL;
    }
}

void  CDecodeDxva2::Init(int nSurfaceCount)
{
    m_nSurfaceCount = nSurfaceCount < AVAPI_MIN_SURFACE_COUNT ? AVAPI_MIN_SURFACE_COUNT : nSurfaceCount;
    m_nSurfaceCount = m_nSurfaceCount > AVAPI_MAX_SURFACE_COUNT ? AVAPI_MAX_SURFACE_COUNT : m_nSurfaceCount;
}

int CDecodeDxva2::Open(AVCodecParameters* pParam, CD3dDxva2Render* pDxva2Render, bool bNeedFreeParam)
{
    int nRet = Ret_Y_Error;
    m_pDxva2Render = pDxva2Render;


    do
    {
        if(!pParam)
        {
            break;
        }

        DXVA2Context* pDxva2Ctx = pDxva2Render->m_pDxva2Ctx;

        //找到解码器
        AVCodec* pVCodec = (AVCodec*)avcodec_find_decoder(pParam->codec_id);

        if(!pVCodec)
        {
            LOGY_ERROR("can't find the codec_id = %d", pParam->codec_id);
            break;
        }

        LOGY_INFO("finded the codec_id = %d", pParam->codec_id);

        m_pCodecCtx = avcodec_alloc_context3(pVCodec);

        if(!m_pCodecCtx)
        {
            LOGY_ERROR("avcodec_alloc_context3 fail");
            break;
        }

        LOGY_INFO("avcodec_alloc_context3");

        // 给解码器赋值解码相关参数
        if(avcodec_parameters_to_context(m_pCodecCtx, pParam) < 0)
        {
            LOGY_ERROR("avcodec_parameters_to_context fail");
            break;
        }

        LOGY_INFO("avcodec_parameters_to_context");
        m_pCodecCtx->thread_count = 1;
        m_pCodecCtx->hwaccel_context = new dxva_context;

        if(!m_pCodecCtx->hwaccel_context)
        {
            LOGY_ERROR("new dxva_context fail");
            break;
        }

        LOGY_INFO("hwaccel_context");

        memset(m_pCodecCtx->hwaccel_context, 0, sizeof(dxva_context));


        GUID* pGuidList = NULL;
        unsigned int nGuidListSize = 0;
        HRESULT pHresult = pDxva2Ctx->pDecoderService->GetDecoderDeviceGuids(&nGuidListSize, &pGuidList);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to retrieve decoder device GUIDs");
            break;
        }

        LOGY_INFO("GetDecoderDeviceGuids");
        GUID oDeviceGuid = GUID_NULL;
        D3DFORMAT eTargetFormat = D3DFMT_UNKNOWN;

        for(unsigned int i = 0; dxva2_modes[i].guid; i++)
        {
            D3DFORMAT* pTargetList = NULL;
            unsigned int nTargetListSize = 0;
            const dxva2_mode* mode = &dxva2_modes[i];

            if(mode->codec != m_pCodecCtx->codec_id)
            {
                continue;
            }

            unsigned int j = 0;

            for(; j < nGuidListSize; j++)
            {
                if(IsEqualGUID(*mode->guid, pGuidList[j]))
                {
                    break;
                }
            }

            if(j == nGuidListSize)
            {
                continue;
            }

            //hr = IDirectXVideoDecoderService_GetDecoderRenderTargets(ctx->decoder_service, mode->guid, &target_count, &target_list);
            pHresult = pDxva2Ctx->pDecoderService->GetDecoderRenderTargets(*mode->guid, &nTargetListSize, &pTargetList);

            if(FAILED(pHresult))
            {
                continue;
            }

            for(unsigned j = 0; j < nTargetListSize; j++)
            {
                const D3DFORMAT f = pTargetList[j];
                const SD3dFormat* pFormat = D3dFindFormat(f);

                if(pFormat)
                {
                    LOGY_INFO("%s is supported for output\n", pFormat->pstrName);
                }
                else
                {
                    LOGY_INFO("%d is supported for output (%4.4s)\n", f, (const char*)&f);
                }
            }

            for(j = 0; j < nTargetListSize; j++)
            {
                const D3DFORMAT eFormat = pTargetList[j];

                if(eFormat == MKTAG('N', 'V', '1', '2'))
                {
                    eTargetFormat = eFormat;
                    break;
                }
            }

            CoTaskMemFree(pTargetList);

            if(eTargetFormat)
            {
                oDeviceGuid = *mode->guid;
                break;
            }
        }

        CoTaskMemFree(pGuidList);

        if(IsEqualGUID(oDeviceGuid, GUID_NULL))
        {
            LOGY_ERROR("No decoder device for codec found");
            break;
        }

        DXVA2_VideoDesc oDxva2VideoDesc = { 0 };
        oDxva2VideoDesc.SampleWidth = m_pCodecCtx->coded_width;
        oDxva2VideoDesc.SampleHeight = m_pCodecCtx->coded_height;
        oDxva2VideoDesc.Format = eTargetFormat;

        DXVA2_ConfigPictureDecode oConfigPicDecode;
        int nRet2 = dxva2_get_decoder_configuration(m_pCodecCtx, &oDeviceGuid, &oDxva2VideoDesc, &oConfigPicDecode, pDxva2Ctx);

        if(nRet2 < 0)
        {
            break;
        }

        int nSurfaceAlignment;

        /*  decoding MPEG-2 requires additional alignment on some Intel GPUs,
            but it causes issues for H.264 on certain AMD GPUs..... */
        if(m_pCodecCtx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
        {
            nSurfaceAlignment = 32;
        }
        /*  the HEVC DXVA2 spec asks for 128 pixel aligned surfaces to ensure
            all coding features have enough room to work with */
        else if(m_pCodecCtx->codec_id == AV_CODEC_ID_HEVC)
        {
            nSurfaceAlignment = 128;
        }
        else
        {
            nSurfaceAlignment = 16;
        }

        //< 创建Surface数量
        //< 在未释放AVFrame情况下，avcodec_send_packet最多调用次数，超过则会失败
        //< 倒放需要缓存一个I帧间隔，surface数量需要超过一个I帧间隔
        pDxva2Ctx->nSurfacesCount = m_nSurfaceCount;
        /* 4 base work surfaces */
        //pDxva2Ctx->nSurfacesCount = 4;

        ///* add surfaces based on number of possible refs */
        //if(m_pCodecCtx->codec_id == AV_CODEC_ID_H264 || m_pCodecCtx->codec_id == AV_CODEC_ID_HEVC)
        //{
        //    pDxva2Ctx->nSurfacesCount += 16;
        //}
        //else if(m_pCodecCtx->codec_id == AV_CODEC_ID_VP9)
        //{
        //    pDxva2Ctx->nSurfacesCount += 8;
        //}
        //else
        //{
        //    pDxva2Ctx->nSurfacesCount += 2;
        //}



        /* add extra surfaces for frame threading */
        if(m_pCodecCtx->active_thread_type & FF_THREAD_FRAME)
        {
            pDxva2Ctx->nSurfacesCount += m_pCodecCtx->thread_count;
        }

        pDxva2Ctx->pSurfaces = new LPDIRECT3DSURFACE9[pDxva2Ctx->nSurfacesCount];
        pDxva2Ctx->pSurfaceInfos = new surface_info[pDxva2Ctx->nSurfacesCount];

        if(!pDxva2Ctx->pSurfaces || !pDxva2Ctx->pSurfaceInfos)
        {
            LOGY_ERROR("Unable to allocate surface arrays");
            break;
        }

        memset(pDxva2Ctx->pSurfaces, 0, sizeof(LPDIRECT3DSURFACE9)*pDxva2Ctx->nSurfacesCount);
        memset(pDxva2Ctx->pSurfaceInfos, 0, sizeof(surface_info)*pDxva2Ctx->nSurfacesCount);

        /*  hr = IDirectXVideoDecoderService_CreateSurface(ctx->decoder_service,
            FFALIGN(s->coded_width, surface_alignment),
            FFALIGN(s->coded_height, surface_alignment),
            ctx->num_surfaces - 1,
            target_format, D3DPOOL_DEFAULT, 0,
            DXVA2_VideoDecoderRenderTarget,
            ctx->surfaces, NULL);*/
        pHresult = pDxva2Ctx->pDecoderService->CreateSurface(FFALIGN(m_pCodecCtx->width, nSurfaceAlignment),
                   FFALIGN(m_pCodecCtx->height, nSurfaceAlignment),
                   pDxva2Ctx->nSurfacesCount - 1,
                   eTargetFormat, D3DPOOL_DEFAULT, 0,
                   DXVA2_VideoDecoderRenderTarget,
                   pDxva2Ctx->pSurfaces, NULL);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to create %d video surfaces", pDxva2Ctx->nSurfacesCount);
            break;
        }

        /*  hr = IDirectXVideoDecoderService_CreateVideoDecoder(ctx->decoder_service, &device_guid,
            &desc, &config, ctx->surfaces,
            ctx->num_surfaces, &ctx->decoder);*/
        pHresult = pDxva2Ctx->pDecoderService->CreateVideoDecoder(oDeviceGuid,
                   &oDxva2VideoDesc, &oConfigPicDecode, pDxva2Ctx->pSurfaces,
                   pDxva2Ctx->nSurfacesCount, &pDxva2Ctx->pDecoder);

        if(FAILED(pHresult))
        {
            LOGY_ERROR("Failed to create DXVA2 video decoder");
            break;
        }

        pDxva2Ctx->oDecoderGuid = oDeviceGuid;
        pDxva2Ctx->oDecoderConfig = oConfigPicDecode;

        dxva_context* dxva_ctx = (dxva_context*)m_pCodecCtx->hwaccel_context;
        dxva_ctx->cfg = &pDxva2Ctx->oDecoderConfig;
        dxva_ctx->decoder = pDxva2Ctx->pDecoder;
        dxva_ctx->surface = pDxva2Ctx->pSurfaces;
        dxva_ctx->surface_count = pDxva2Ctx->nSurfacesCount;

        if(IsEqualGUID(pDxva2Ctx->oDecoderGuid, DXVADDI_Intel_ModeH264_E))
        {
            dxva_ctx->workaround |= FF_DXVA2_WORKAROUND_INTEL_CLEARVIDEO;
        }

        m_pCodecCtx->get_buffer2 = dxva2_get_buffer;
        m_pCodecCtx->get_format = GetHwFormat;
        m_pCodecCtx->thread_safe_callbacks = 1;
        m_pCodecCtx->opaque = pDxva2Render;

        nRet2 = avcodec_open2(m_pCodecCtx, pVCodec, NULL);

        if(nRet2 < 0)
        {
            printf("error %x in avcodec_open2\n", nRet);
            break;
        }

        nRet = Ret_Y_OK;
    } while(0);

    if(Ret_Y_OK != nRet)
    {
        Close();
    }

    if(bNeedFreeParam)
    {
        avcodec_parameters_free(&pParam);
    }

    return nRet;
}

void CDecodeDxva2::Close()
{
    if(m_pDxva2Render)
    {
        DXVA2Context* pDxva2Ctx = m_pDxva2Render->m_pDxva2Ctx;

        if(pDxva2Ctx)
        {
            if(pDxva2Ctx->pSurfaces)
            {
                for(int i = 0; i < pDxva2Ctx->nSurfacesCount; i++)
                {
                    if(pDxva2Ctx->pSurfaces[i])
                    {
                        IDirect3DSurface9_Release(pDxva2Ctx->pSurfaces[i]);
                    }
                }
            }

            SAFE_DELETE_ARRAY(pDxva2Ctx->pSurfaces);
            SAFE_DELETE_ARRAY(pDxva2Ctx->pSurfaceInfos);
            pDxva2Ctx->nSurfacesCount = 0;
            pDxva2Ctx->nSurfaceAge = 0;

            if(pDxva2Ctx->pDecoder)
            {
                //IDirectXVideoDecoder_Release(ctx->decoder);
                pDxva2Ctx->pDecoder->Release();
                pDxva2Ctx->pDecoder = NULL;
            }
        }
    }

    SAFE_DELETE(m_pCodecCtx->hwaccel_context);

    if(m_pCodecCtx)
    {
        avcodec_close(m_pCodecCtx);
        avcodec_free_context(&m_pCodecCtx);
        m_pCodecCtx = 0;
    }

}

void CDecodeDxva2::Render(AVFrame* pFrame, bool bNeedFree)
{
    dxva2_retrieve_data(m_pCodecCtx, pFrame);

    if(pFrame && bNeedFree)
    {
        av_frame_free(&pFrame);
        pFrame = nullptr;
    }
}
