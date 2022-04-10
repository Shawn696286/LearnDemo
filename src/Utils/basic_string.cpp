#include "basic_string.h"
#include <string.h>
//#include <openssl/aes.h>
//#include <openssl/evp.h>
//#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>

namespace y {
namespace basic {

std::string CString::EncodeBase64(const std::string& strInput)
{
    if(strInput.empty())
    {
        return "";
    }

    //base64 out at least four bytes
    int nDstLen = strInput.length() * 2 + 4;
    char* pBuf = new char[nDstLen];
    memset(pBuf, 0, nDstLen);
    int nRetLen = base64_encode(strInput.c_str(), strInput.length(), pBuf, nDstLen);

    std::string strOutput;
    SafeStrAppend(strOutput, pBuf, nRetLen);

    delete[]pBuf;
    return strOutput;
}

std::string CString::DecodeBase64(const std::string& strInput)
{
    if(strInput.empty())
    {
        return "";
    }

    //base64 out at least four bytes
    int nDstLen = strInput.length() * 2 + 4;

    char* pBuf = new char[nDstLen];
    memset(pBuf, 0, nDstLen);
    int nRetLen = base64_decode(strInput.c_str(), strInput.length(), pBuf, nDstLen);

    std::string strOutput;
    SafeStrAppend(strOutput, pBuf, nRetLen);
    delete[]pBuf;
    return strOutput;
}

int CString::base64_encode(const char* str, int str_len, char* encode, int encode_len)
{
    BIO* bmem, * b64;
    BUF_MEM* bptr;

    do
    {
        b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        bmem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bmem);
        BIO_write(b64, str, str_len); //encode
        BIO_flush(b64);
        BIO_get_mem_ptr(b64, &bptr);


        if(bptr->length > encode_len)
        {
            encode_len = -1;
            break;
        }

        encode_len = bptr->length;
        memcpy(encode, bptr->data, bptr->length);
    } while(0);

    BIO_free_all(b64);

    return encode_len;
}

int CString::base64_decode(const char* str, int str_len, char* decode, int decode_buffer_len)
{
    int len = 0;
    BIO* b64, * bmem;
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new_mem_buf(str, str_len);
    bmem = BIO_push(b64, bmem);
    len = BIO_read(bmem, decode, str_len);
    decode[len] = 0;
    BIO_free_all(bmem);
    return len;

}

void CString::SafeStrAppend(std::string& str, char* pstr, int nLen)
{
    if(nLen > 0)
    {
        str.append(pstr, nLen);
    }
}

}
}