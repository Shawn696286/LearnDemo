// C++.cpp: 定义应用程序的入口点。
//

#include "public_inc.h"
#include "aes-gcm-256.h"
#include "fastpbkdf2.h"
#include "base64.h"
int main(int argc, char* argv[])
{
    char str[10];// = { 0 };
    //memset(str, 0, 10);
    //memcpy(str, "1234", strlen("1234"));
    //memcpy(str + strlen("1234"), "abcd", strlen("abcd"));

    //test_aes_gcm_256();
    test_base64();
    //test_fastpbkdf2();
    //auto strHash = CString::DecodeBase64("+A9f11WYYBNHw/XWJBpjWw==");
    return 0;
}
