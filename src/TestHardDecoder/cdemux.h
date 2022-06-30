#pragma once
#include "public.h"
struct AVPacket;
struct AVFormatContext;
struct AVCodecParameters;
struct AVStream;

class CDemux
{
public:
    CDemux();
    ~CDemux();

    //< 打开文件
    int Open(std::string strFilepath);

    //< 读一帧数据
    AVPacket* Read();

    //< 读一帧视频数据
    AVPacket* ReadVideo();

    //< 获取视频参数 返回空间需要清理 avcodec_parameters_free
    AVCodecParameters* CopyVPara();

    //< 获取音频参数 返回空间需要清理 avcodec_parameters_free
    AVCodecParameters* CopyAPara();

    //< 获取视频宽度
    int GetWidth();

    //< 获取视频高度
    int GetHeight();

    //< 关闭
    void Close();
private:
    //< 解封装上下文
    AVFormatContext* m_pFmtCtx;

    //< 视频索引
    int m_nVStreamIndex = 0;

    //< 音频索引
    int m_nAStreamIndex = 0;
};

