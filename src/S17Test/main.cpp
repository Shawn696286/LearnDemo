// C++.cpp: 定义应用程序的入口点。
//

#include "public_inc.h"
#include "aes-gcm-256.h"
#include "fastpbkdf2.h"
int main(int argc, char* argv[])
{
    test_fastpbkdf2();
    //auto strHash = CString::DecodeBase64("+A9f11WYYBNHw/XWJBpjWw==");
    return 0;
}
