// C++.cpp: 定义应用程序的入口点。
//
#include "public.h"

//< 定义安全释放宏
#define SAFE_DELETE(p)          if(p) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p)    if(p) { delete [] (p); (p) = nullptr; }

using namespace std;

#define ul unsigned long

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

int main(int argc, char* argv[])
{
    //测试avapi
    #if 1
    int a = sizeof(char*);
    printf("char* size = %d\n", a);
    a = sizeof(void*);
    printf("void* size = %d\n", a);
    a = sizeof(long*);
    printf("long* size = %d\n", a);
    a = sizeof(uint64_t*);
    printf("uint64_t* size = %d\n", a);
    a = sizeof(VIDEO_DATA);
    printf("VIDEO_DATA size = %d\n", a);

    #endif
    getchar();
    return 0;
}
