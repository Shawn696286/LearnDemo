#pragma once

#include <openssl/bio.h>

static int base64_encode(const char* str, int str_len, char* encode, int encode_len)
{
    BIO* bmem, * b64;
    BUF_MEM* bptr;
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, str, str_len); //encode
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    if(bptr->length > encode_len)
    {
        //DPRINTF("encode_len too small\n");
        return -1;
    }

    encode_len = bptr->length;
    memcpy(encode, bptr->data, bptr->length - 1);
    //  write(1,encode,bptr->length);
    BIO_free_all(b64);
    return encode_len;

}

static int base64_decode(const char* str, int str_len, char* decode, int decode_buffer_len)
{
    if(str_len > decode_buffer_len)
    {
        return -1;
    }

    int len = 0;
    BIO* b64, * bmem;
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf(str, str_len);
    bmem = BIO_push(b64, bmem);
    len = BIO_read(bmem, decode, str_len);
    decode[len] = 0;
    BIO_free_all(bmem);
    return 0;

}
std::string EncodeBase64(const std::string& strInput)
{
    char* pBuf = new char[1024 * 1024];
    memset(pBuf, 0, 1024 * 1024);
    base64_encode(strInput.c_str(), strInput.length(), pBuf, 1024 * 1024);
    std::string strOutput = pBuf;
    delete []pBuf;
    return strOutput;
}

std::string DecodeBase64(const std::string& strInput)
{
    string strInput2 = strInput + "\n";

    char* pBuf = new char[1024 * 1024];
    memset(pBuf, 0, 1024 * 1024);
    base64_decode(strInput2.c_str(), strInput2.length(), pBuf, 1024 * 1024);
    std::string strOutput = pBuf;
    delete[]pBuf;
    return strOutput;
}

void test_base64()
{
    std::string str = "qwertyuiop";
    std::string strOut;
    strOut = EncodeBase64(str);
    printf("my en %s\n", strOut.c_str());

    printf("my de %s\n", DecodeBase64(strOut).c_str());

    strOut = CString::EncodeBase64(str);
    printf("ba en %s\n", strOut.c_str());

    printf("ba de %s\n", CString::DecodeBase64(strOut).c_str());


}