#pragma once
#include "public_inc.h"
#include <openssl/aes.h>

#include <openssl/evp.h>

#include <openssl/rand.h>

#include <openssl/ssl.h>

#include <string>

#include <sstream>

#include <vector>

#include <iostream>

using namespace std;



#if 1

// 32 bytes, Key

static  unsigned char gcm_key[32] = { 0 };



static  unsigned char gcm_iv[] = "sdihfosihg";



// Additional Authenticated Data(AAD): it is not encrypted, and is typically passed to the recipient in plaintext along with the ciphertext

static const unsigned char gcm_aad[] =   // 16 bytes

{

    0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b, 0xdb, 0x37, 0x0c, 0x43,

    0x7f, 0xec, 0x78, 0xde

};

#else

static const unsigned char gcm_key[] =   // 32 bytes, Key

{

    0xee, 0xbc, 0x1f, 0x57, 0x48, 0x7f, 0x51, 0x92, 0x1c, 0x04, 0x65, 0x66,

    0x5f, 0x8a, 0xe6, 0xd1, 0x65, 0x8b, 0xb2, 0x6d, 0xe6, 0xf8, 0xa0, 0x69,

    0xa3, 0x52, 0x02, 0x93, 0xa5, 0x72, 0x07, 0x8f

};



static const unsigned char gcm_iv[] =   // 12 bytes, IV(Initialisation Vector)

{

    0x99, 0xaa, 0x3e, 0x68, 0xed, 0x81, 0x73, 0xa0, 0xee, 0xd0, 0x66, 0x84

};



// Additional Authenticated Data(AAD): it is not encrypted, and is typically passed to the recipient in plaintext along with the ciphertext

static const unsigned char gcm_aad[] =   // 16 bytes

{

    0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b, 0xdb, 0x37, 0x0c, 0x43,

    0x7f, 0xec, 0x78, 0xde

};

#endif



class CTestOpenssl

{

public:

    CTestOpenssl()

    {



    }



    ~CTestOpenssl()

    {



    }



    std::unique_ptr<unsigned char[]> aes_gcm_encrypt(const char* plaintext, int& length, unsigned char* tag)

    {

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

        // Set cipher type and mode

        EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);

        // Set IV length if default 96 bits is not appropriate
        int nIvLen = strlen((char*)gcm_iv);
        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, nIvLen, nullptr);


        // Initialise key and IV

        EVP_EncryptInit_ex(ctx, nullptr, nullptr, gcm_key, gcm_iv);

        // Zero or more calls to specify any AAD

        int outlen;

        //EVP_EncryptUpdate(ctx, nullptr, &outlen, gcm_aad, sizeof(gcm_aad));

        unsigned char outbuf[1024] = { 0 };

        //set padding
        //EVP_CIPHER_CTX_set_padding(ctx, EVP_CIPH_NO_PADDING);
        // Encrypt plaintext

        EVP_EncryptUpdate(ctx, outbuf, &outlen, (const unsigned char*)plaintext, strlen(plaintext));

        length = outlen;

        std::unique_ptr<unsigned char[]> ciphertext(new unsigned char[length]);

        memcpy(ciphertext.get(), outbuf, length);

        // Finalise: note get no output for GCM

        EVP_EncryptFinal_ex(ctx, outbuf, &outlen);

        // Get tag

        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, outbuf);

        memcpy(tag, outbuf, 16);

        // Clean up

        EVP_CIPHER_CTX_free(ctx);

        return ciphertext;

    }



    std::unique_ptr<unsigned char[]> aes_gcm_decrypt(const unsigned char* ciphertext, int& length, const unsigned char* tag)

    {

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

        // Select cipher

        EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);

        // Set IV length, omit for 96 bits

        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, strlen((char*)gcm_iv), nullptr);

        // Specify key and IV

        EVP_DecryptInit_ex(ctx, nullptr, nullptr, gcm_key, gcm_iv);

        int outlen;

        // Zero or more calls to specify any AAD

        // EVP_DecryptUpdate(ctx, nullptr, &outlen, gcm_aad, sizeof(gcm_aad));

        unsigned char outbuf[1024] = { 0 };

        // Decrypt plaintext

        EVP_DecryptUpdate(ctx, outbuf, &outlen, ciphertext, length);

        // Output decrypted block

        length = outlen;

        std::unique_ptr<unsigned char[]> plaintext(new unsigned char[length]);

        memcpy(plaintext.get(), outbuf, length);

        // Set expected tag value

        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, (void*)tag);

        // Finalise: note get no output for GCM

        int rv = EVP_DecryptFinal_ex(ctx, outbuf, &outlen);

        // Print out return value. If this is not successful authentication failed and plaintext is not trustworthy.

        fprintf(stdout, "Tag Verify %s\n", rv > 0 ? "Successful!" : "Failed!");

        EVP_CIPHER_CTX_free(ctx);

        return plaintext;

    }





    int RunTest()

    {

        /*  reference:

            https://github.com/openssl/openssl/blob/master/demos/evp/aesgcm.c

            https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption

        */

        fprintf(stdout, "Start AES GCM 256 Encrypt:\n");

        const char* plaintext = "1234567890ABCDEFG!@#$%^&*()_+[]{};':,.<>/?|";

        fprintf(stdout, "src plaintext: %s, length: %d\n", plaintext, strlen(plaintext));

        int length = 0;

        std::unique_ptr<unsigned char[]> tag(new unsigned char[16]);

        std::unique_ptr<unsigned char[]> ciphertext = aes_gcm_encrypt(plaintext, length, tag.get());

        fprintf(stdout, "length: %d, ciphertext: ", length);


        std::string sss((char*)ciphertext.get());
        std::string strOutput = CString::EncodeBase64(sss);

        fprintf(stdout, "base64: %s\n", strOutput.c_str());



        for(int i = 0; i < length; ++i)

        {

            fprintf(stdout, "%02x ", ciphertext.get()[i]);

        }



        fprintf(stdout, "\nTag: ");



        for(int i = 0; i < 16; ++i)

        {

            fprintf(stdout, "%02x ", tag.get()[i]);

        }



        fprintf(stdout, "\n");



        fprintf(stdout, "\nStart AES GCM 256 Decrypt:\n");

        std::unique_ptr<unsigned char[]> result = aes_gcm_decrypt(ciphertext.get(), length, tag.get());

        fprintf(stdout, "length: %d, decrypted plaintext: ", length);



        for(int i = 0; i < length; ++i)

        {

            fprintf(stdout, "%c", result.get()[i]);

        }



        fprintf(stdout, "\n");



        if(strncmp(plaintext, (const char*)result.get(), length) == 0)

        {

            fprintf(stdout, "decrypt success\n");

            return 0;

        }

        else

        {

            fprintf(stderr, "decrypt fail\n");

            return -1;

        }



    }



};

int test_aes_gcm_256()
{
    char* key = "3ih4ih6";
    int len = strlen(key);
    memcpy((char*)gcm_key, key, len);
    CTestOpenssl oT;
    oT.RunTest();

    char* str = "pAlG1ibyCRxwWE/l86lLc8Ii75caCySHMXb6KQ60PI+fumxQSHAWX1+GPx7jLTm5BqRLnYaRefhoKg8=";
    auto strDecode = CString::DecodeBase64(str);
    auto strMsg = strDecode.substr(0, strDecode.length() - 16);
    //CTestOpenssl oT;
    int length = strMsg.length();
    auto strTag = strDecode.substr(strDecode.length() - 16, 16);


    std::unique_ptr<unsigned char[]> result = oT.aes_gcm_decrypt((unsigned char*)strMsg.c_str(), length,
            (unsigned char*)strTag.c_str());

    fprintf(stdout, "length: %d, decrypted plaintext: ", length);

    for(int i = 0; i < length; ++i)

    {

        fprintf(stdout, "%c", result.get()[i]);

    }

    fprintf(stdout, "\n");

    return 0;
}

