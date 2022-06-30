// C++.cpp: 定义应用程序的入口点。
//
#include "public.h"
#include "librmfs5.0/api_rmfs_nxm.h"
#include "rmfs4.0/api_rmfs.h"
#include "Poco/Timer.h"
#include "Poco/Thread.h"

#include "Poco\File.h"
#include "Poco\FileStream.h"
#include "Poco\Process.h"
#include "Poco\RegularExpression.h"
#include "Poco\DateTime.h"
#include "Poco\DateTimeFormatter.h"
#include "Poco\DateTimeParser.h"
#include "Poco\Net\HTTPSClientSession.h"
#include "Poco\Net\HTTPRequest.h"
#include "Poco\Net\HTTPResponse.h"
#include "Poco\Net\InvalidCertificateHandler.h"
#include "Poco\Net\AcceptCertificateHandler.h"
#include "Poco\URI.h"
#include "Poco\Net\SSLManager.h"
#include "Poco\JSON\Object.h"
#include "Poco\JSON\Parser.h"
#include "Poco\String.h"
#include "Poco\Net\KeyConsoleHandler.h"
#include "Poco\Net\ConsoleCertificateHandler.h"
#include "Poco\SharedPtr.h"
#include "avapi/avapi.h"

//< 定义安全释放宏
#define SAFE_DELETE(p)          if(p) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p)    if(p) { delete [] (p); (p) = nullptr; }

using namespace std;
using namespace Poco;
using namespace Poco::Net;
using namespace std;
using Poco::Timer;
using Poco::TimerCallback;

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
struct MyStruct
{
    char a : 2;
    char b : 6;
};

union UTest
{
    MyStruct c;
    char d;
};
class TimerExample
{
public:
    void onTimer(Poco::Timer& timer)
    {
        std::cout << "onTimer called." << std::endl;
    }
};

int main(int argc, char* argv[])
{
    //测试rmfs
    #if 0
    api_rmfs_init(0);
    api_rmfs_uinit();

    api_rmfs_set_debug_level(0);
    api_rmfs_get_stream_date_info_num(0, 0, 0xffffffff);
    n9m_fs_record_date_info_t* list = NULL;
    api_rmfs_get_stream_date_info(0, 0, 0xffffffff, list, 0);

    api_rmfs_nxm_init();
    api_rmfs_nxm_uinit();
    api_rmfs_nxm_rebuild_rely(0, nullptr);
    api_rmfs_nxm_set_debug_level(0);
    api_rmfs_nxm_get_stream_date_info_num(0, 0, 0xffffffff);
    rmfs_nxm_record_date_info_t* list2 = NULL;
    api_rmfs_nxm_get_stream_date_info(0, 0x07, 0xffffffff, list2, 0);

    #endif

    //测试poco timer
    #if 0
    TimerExample te;
    Timer timer(250, 500); // fire after 250ms, repeat every 500ms
    timer.start(TimerCallback<TimerExample>(te, &TimerExample::onTimer));
    Poco::Thread::sleep(5000);
    timer.stop();
    #endif

    //测试poco tls
    #if 0
    string postString = "your json data";

    SharedPtr<InvalidCertificateHandler> ptrCert = new ConsoleCertificateHandler(true);
    Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, true,
                                          "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    SSLManager::instance().initializeClient(0, ptrCert, ptrContext);
    string url = "your url";
    URI uri(url);
    HTTPSClientSession client(uri.getHost(), uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
    request.setContentType("application/json");
    std::string reqBody(postString);
    request.setContentLength(reqBody.length());

    //client.sendRequest(request) << reqBody;
    //HTTPResponse response;
    //istream& is = client.receiveResponse(response);

    //if(response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
    //{
    //    char* pData = new char[response.getContentLength()];
    //    is.read(pData, response.getContentLength());
    //    std::string srcString(pData, response.getContentLength());
    //    cout << srcString << endl;
    //}

    #endif

    //测试avapi
    #if 0
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
    NAV_IsPause(0);

    const int _BUF_SZIE = 30;
    const int _READ_BUF_LEN = 2400000;
    VIDEO_DATA oT1[_BUF_SZIE];
    char* oT2[_BUF_SZIE];

    //for(int i = 0; i < _BUF_SZIE; ++i)
    //{
    //    oT2[i] = new char[_READ_BUF_LEN + 1000];
    //}

    //for(size_t j = 0; j < 1000; j++)
    //{
    //    int n = 1;

    //    for(int i = 0; i < _BUF_SZIE; ++i)
    //    {
    //        oT1[i].w = 2 * n;
    //        oT1[i].h = 4 * n;
    //        memcpy(oT2[i], &oT1[i], sizeof(oT1[i]));
    //        printf("----p = %p,w = %d,i = %d\n", oT2[i], ((VIDEO_DATA*)oT2[i])->w, i);
    //    }

    //    for(int i = _BUF_SZIE - 1; i >= 0; --i)
    //    {
    //        VIDEO_DATA* pT = (VIDEO_DATA*)oT2[i];
    //        printf("----p = %p,w = %d,i = %d\n", oT2[i], ((VIDEO_DATA*)oT2[i])->w, i);
    //    }
    //}

    #endif

    //< 测试位域大小端位
    #if 1
    UTest aa;
    aa.c.a = 0;
    aa.c.b = 1;
    char d = aa.d;
    #endif
    getchar();
    return 0;
}
