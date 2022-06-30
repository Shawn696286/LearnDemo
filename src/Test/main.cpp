// C++.cpp: 定义应用程序的入口点。
//
#include "test.h"
#include <sstream>
#include <iomanip>
#include<string.h>
#include "logyapi.h"
#include <thread>
#include <vector>
#include <memory>
#include <malloc.h>
#include <stdint.h>
#ifndef _WIN32
    #include <unistd.h>
#endif // _WIN32
using namespace std;
struct MY_TIME
{
    int nYear;
    int nMonth;
    int nDay;
    int nHour;
    int nMinute;
    int nSecond;
};
#define ul int
struct VIDEO_DATA
{
    char* ai_buf[256];
    char* pFrame;
    char* buf;
    ul         ullPts;
    ul         ullRealPts;
    int        nTotalLen;
    int        nFrameLen;
    int        nSec;
    int        nSampleRate;
    MY_TIME    time;
    unsigned short        nFrameRate;
    unsigned short        ai_count;
    unsigned short        stride;
    unsigned short        w;
    unsigned short        h;
    unsigned char        aes_type;
    unsigned char        nVideoFormat;
    unsigned char        bEncrypt = { 0 };
    unsigned char        nYUVFormat;
    unsigned char        nRotate;
    unsigned char        bIFrame;
    unsigned char        bVideo;
    unsigned char        bHaveTime;
    unsigned char        nChannel;
    char        nAudioFormat;
    std::string encrypt_key_id;
};

struct SRtpHeader
{
    uint8_t version: 2;      /*协议版本*/
    uint8_t padding: 1;       /*P*/
    uint8_t extension: 1;     /*X*/
    uint8_t csrc_count: 4;    /*CSRC个数*/
    uint8_t marker: 1;        /*一帧是否结束*/
    uint8_t payloadtype: 7;   /*载荷的数据类型*/
    uint16_t seq;               /*序列号，第几个*/
    uint32_t timestamp;         /*时间戳，第一个 */
    uint32_t ssrc;              /*同步信源(SSRC)标识符*/
};
struct RTP_Header
{
    unsigned __int16 csrc_count : 4;
    unsigned __int16 extension : 1;
    unsigned __int16 padding : 1;
    unsigned __int16 version : 2;
    unsigned __int16 payloadtype : 7;
    unsigned __int16 marker : 1;

    unsigned __int16 seq;
    unsigned __int32 timestamp;
    unsigned __int32 ssrc;
};

struct RTP_Header2
{
    uint16_t csrc_count : 4;
    uint16_t extension : 1;
    uint16_t padding : 1;
    uint16_t version : 2;
    uint16_t payloadtype : 7;
    uint16_t marker : 1;

    uint16_t seq;
    uint32_t timestamp;
    uint32_t ssrc;
};
struct MyStruct
{
    uint16_t payloadtype : 7;
    uint16_t marker : 1;

};
//< 定义安全释放宏
#define SAFE_DELETE(p)          if(p) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p)    if(p) { delete [] (p); (p) = nullptr; }
int main(int argc, char* argv[])
{
    bool b1 = false;
    bool b2 = true;
    int n1 = b1;
    int n2 = b2;
    int n3 = 0;
    //制作5g视频文件
    #if 0
    LOGY_DEBUG("test logy\n");
    //CTest t;
    //t.Worker();
    FILE* rfp = fopen("./1.264", "rb+");

    if(!rfp)
    {
        perror("打开文件1.264失败啦");
        return 0;
    }

    FILE* wfp = fopen("./5g.264", "wb+");

    if(!wfp)
    {
        perror("打开文件5g.h264失败啦");
        return 0;
    }

    int nMaxBufSize = 10240;
    char* buf = new char[nMaxBufSize];
    memset(buf, 0, nMaxBufSize);
    int nCount = 0;
    int nMAxCount = 5000;
    float nTotalSize = 5.2;
    int64_t nCurSize = 0;

    while(true)
    {
        int nRet = fread(buf, 1, nMaxBufSize, rfp);

        if(nRet > 0)
        {
            fwrite(buf, 1, nRet, wfp);
            nCurSize += nRet;
        }

        if(nRet < nMaxBufSize)
        {
            fseek(rfp, 0, SEEK_SET);
            nCount++;

            if(nCount % 500 == 0)
            {
                printf("nCount = %d,curSize = %f\n", nCount, nCurSize / (float)(1024 * 1024 * 1024));
            }

            if(nCurSize / (float)(1024 * 1024 * 1024) > nTotalSize)
            {
                break;
            }
        }
    }

    fclose(rfp);
    fclose(wfp);
    #endif

    //测试字符串剪辑
    #if 0
    std::string strPath =
                    "/10001/device/79dc6867aaab44ba84e7c1a0f560216d/2022/4/22/1_7908209197056.mp4?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20220422T101732Z&X-Amz-SignedHeaders=host&X-Amz-Expires=86399&X-Amz-Credential=AKIAURAJCTK66RBYHAOX%2F20220422%2Feu-west-3%2Fs3%2Faws4_request&X-Amz-Signature=d99d61c9b20547f62733b28e655f58bb2b1c4ea93f58b677b9ef694627d49ac5";
    auto nTempPos = strPath.find('?');

    if(std::string::npos != nTempPos)
    {
        strPath = strPath.substr(0, nTempPos);
    }

    #endif

    //测试多线程new delete内存泄漏
    #if 0

    if(1)
    {
        static int s_nMaxRead = 4 * 1024 * 1024;
        int nThreadCount = 0;

        for(int j = 0; j < 5; j++)
        {
            nThreadCount = 20;
            //if(j < 25)
            //{
            //    nThreadCount = 2 * j + 1;
            //}
            //else
            //{
            //    nThreadCount = 2 * (50 - j) + 1;
            //}

            printf("========================== cur count = %d,nThreadCount=%d\n", j, nThreadCount);

            for(int i = 0; i < nThreadCount; i++)
            {
                std::thread oThread([&](int n)
                {

                    uint8_t* pBuf = new uint8_t[s_nMaxRead];
                    memset(pBuf, 0, s_nMaxRead);
                    printf("============================================123456   i =%d,%p\n", i, pBuf);
                    //int nRead = fread(pBuf, 1, s_nMaxRead, fp);
                    SAFE_DELETE_ARRAY(pBuf);

                    printf("malloc_trim\n");
                    malloc_trim(0);
                    //std::shared_ptr<char> chars(new char[s_nMaxRead]);
                    //memset(chars.get(), 0, s_nMaxRead);

                    //int nMemSize = s_nMaxRead * sizeof(uint8_t);
                    //uint8_t* pBuf = (uint8_t*)malloc(nMemSize);
                    //memset(pBuf, 0, s_nMaxRead);
                    //free(pBuf);
                }
                , i);


                oThread.detach();
            }

            sleep(1);

        }

    }
    else
    {
        int nCount = 1;

        if(argc == 2)
        {
            nCount = atoi(argv[1]);
        }

        nCount = nCount < 1 ? 1 : nCount;
        {
            for(int i = 0; i < nCount; i++)
            {

                printf("============================================123456   i =%d\n", i);
                int s_nMaxRead = 4 * 1024 * 1024;
                uint8_t* pBuf = new uint8_t[s_nMaxRead];
                memset(pBuf, 0, s_nMaxRead);
                //int nRead = fread(pBuf, 1, s_nMaxRead, fp);
                printf("============================================123456   i =%d,%p\n", i, pBuf);
                SAFE_DELETE_ARRAY(pBuf);

                pBuf = new uint8_t[s_nMaxRead];
                memset(pBuf, 0, s_nMaxRead);
                //int nRead = fread(pBuf, 1, s_nMaxRead, fp);
                printf("============================================123456   i =%d,%p\n", i, pBuf);
                SAFE_DELETE_ARRAY(pBuf);

                //std::shared_ptr<char> chars(new char[s_nMaxRead]);
                //memset(chars.get(), 0, s_nMaxRead);

                //uint8_t* pBuf = (uint8_t*)malloc(s_nMaxRead * sizeof(uint8_t));
                //memset(pBuf, 0, s_nMaxRead);
                //free(pBuf);

                //void* pBuf = (void*)malloc(s_nMaxRead * sizeof(char));
                //memset(pBuf, 0, s_nMaxRead);
                //free(pBuf);
            }

        }
    }

    #endif

    //测试rtp头解析
    #if 0
    uint8_t pRtpHeader[] = { 0x80, 0x88, 0x0, 0x4, 0x0, 0x0, 0x1, 0x53, 0x2, 0xab, 0xe6, 0xc4, 0xd4, 0x56, 0x5a, 0x54, 0x44, 0xd1 };
    SRtpHeader* psRtpHeader = (SRtpHeader*)pRtpHeader;
    RTP_Header* psRtpHeader2 = (RTP_Header*)pRtpHeader;
    RTP_Header2* psRtpHeader3 = (RTP_Header2*)pRtpHeader;

    uint8_t nPayLoadType = 0x88;
    uint8_t nnn = nPayLoadType & 0x7f;
    uint8_t nPayLoadType2 = 0x60;
    uint8_t nnn2 = nPayLoadType2 & 0x7f;
    uint8_t nPayLoadType3 = 0xe0;
    uint8_t nnn3 = nPayLoadType3 & 0x7f;
    MyStruct* pp = (MyStruct*)&nPayLoadType;
    MyStruct* pp2 = (MyStruct*)&nPayLoadType2;
    MyStruct* pp3 = (MyStruct*)&nPayLoadType3;
    uint8_t nw = nPayLoadType << 1 >> 1;
    uint8_t nw2 = nPayLoadType2 << 1 >> 1;
    uint8_t nw3 = nPayLoadType3 << 1 >> 1;

    SRtpHeader oRtpHeadr;
    oRtpHeadr.version = (pRtpHeader[0] & 0xc0) >> 6;
    oRtpHeadr.padding = (pRtpHeader[0] & 0x20) >> 5;
    oRtpHeadr.extension = (pRtpHeader[0] & 0x10) >> 4;
    oRtpHeadr.csrc_count = pRtpHeader[0] & 0xf;
    oRtpHeadr.marker = (pRtpHeader[1] & 0x80) >> 7;
    oRtpHeadr.payloadtype = pRtpHeader[1] & 0x7f;
    oRtpHeadr.seq = pRtpHeader[2] << 1 * 8 | pRtpHeader[3];
    oRtpHeadr.timestamp = pRtpHeader[4] << 3 * 8 | pRtpHeader[5] << 2 * 8 |
                          pRtpHeader[6] << 1 * 8 | pRtpHeader[7] ;
    oRtpHeadr.ssrc = pRtpHeader[8] << 3 * 8 | pRtpHeader[9] << 2 * 8 |
                     pRtpHeader[10] << 1 * 8 | pRtpHeader[11];

    uint8_t* str1 = (uint8_t*)"123456";
    std::vector<uint8_t> vec;
    vec.resize(strlen((char*)str1) * 2);
    memcpy(&vec[0], str1, strlen((char*)str1));
    #endif

    //测试vector
    #if 1
    std::vector<int> vceInt;
    vceInt.reserve(4);
    vceInt.push_back(1);
    vceInt.push_back(2);
    vceInt.push_back(3);
    vceInt.push_back(4);
    vceInt.push_back(5);
    vceInt.push_back(6);
    vceInt.pop_back();
    vceInt.pop_back();
    vceInt.pop_back();
    #endif
    getchar();
    return 0;
}
