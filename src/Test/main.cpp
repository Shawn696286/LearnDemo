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
    getchar();
    return 0;
}
