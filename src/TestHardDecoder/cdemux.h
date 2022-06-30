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

    //< ���ļ�
    int Open(std::string strFilepath);

    //< ��һ֡����
    AVPacket* Read();

    //< ��һ֡��Ƶ����
    AVPacket* ReadVideo();

    //< ��ȡ��Ƶ���� ���ؿռ���Ҫ���� avcodec_parameters_free
    AVCodecParameters* CopyVPara();

    //< ��ȡ��Ƶ���� ���ؿռ���Ҫ���� avcodec_parameters_free
    AVCodecParameters* CopyAPara();

    //< ��ȡ��Ƶ���
    int GetWidth();

    //< ��ȡ��Ƶ�߶�
    int GetHeight();

    //< �ر�
    void Close();
private:
    //< ���װ������
    AVFormatContext* m_pFmtCtx;

    //< ��Ƶ����
    int m_nVStreamIndex = 0;

    //< ��Ƶ����
    int m_nAStreamIndex = 0;
};

