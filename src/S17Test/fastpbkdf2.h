#pragma once
#include "public_inc.h"
#include <stdio.h>
#include<openssl/evp.h>

void test_fastpbkdf2()
{
    printf("test_fastpbkdf2 start\n");
    std::string strMsg = "Streamax_sdgghk";
    std::string strSalt = "sdkkjhfg";
    int nCount = 10000;
    char strOut[128] = { 0 };


    int success = PKCS5_PBKDF2_HMAC(strMsg.c_str(), strMsg.length(), (unsigned char*)strSalt.c_str(), strSalt.length(),
                                    nCount, EVP_sha1(), 16, (unsigned char*)strOut);



    int nOutlen = strlen(strOut);
    printf("fastpbkdf2 out = %s", CString::EncodeBase64(strOut).c_str());

    printf("\ntest_fastpbkdf2 end\n");
}