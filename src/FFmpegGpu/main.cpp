// C++.cpp: 定义应用程序的入口点。
//
#include "public.h"
#include "hard_decoder.h"

using namespace std;

//< 定义安全释放宏
#define SAFE_DELETE(p)          if(p) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p)    if(p) { delete [] (p); (p) = nullptr; }
int main(int argc, char* argv[])
{
    #if 1
    HardEnDecoder oHardDecode;
    oHardDecode.doDecode();
    #endif


    getchar();
    return 0;
}
