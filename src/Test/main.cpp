// C++.cpp: 定义应用程序的入口点。
//
#include <sstream>
#include <iomanip>
#include "logyapi.h"
#include "basic_string.h"
#include <openssl/ssl.h>
using namespace std;
using namespace y::basic;

int main()
{
    LOGY_DEBUG("test logy\n");
    auto strOut = CString::EncodeBase64("dj9ddjkl");
    LOGY_DEBUG("base64 encode out = %s", strOut.c_str());
    strOut = CString::DecodeBase64(strOut);
    LOGY_DEBUG("base64 decode out = %s", strOut.c_str());
    return 0;
}
