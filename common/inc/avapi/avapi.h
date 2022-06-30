

#ifndef   AVAPI_H
#define   AVAPI_H

typedef struct SecretKeyParam
{
    int key_type;
    char* key_id;
    int key_id_size;
    char* key_data;
    int* key_data_size;
}* SecretKeyParamPtr;

#ifndef AVAPI_DATA_TYPE_DEF
    #define AVAPI_DATA_TYPE_DEF
    #define   rt_int32   int
    #define   rt_uint32  unsigned int
    #define   rt_int64   long long
    #define   rt_uint64  unsigned long long
    #ifndef _WIN64
        #define   ul  unsigned long
    #else
        #define   ul  uint64_t
    #endif
    #define   ull unsigned long long

#endif
///   播放器SDK
///   返回值为unsigned long时，无特别说明均是0表成功，非0为错误码

///  回调函数定义
///  nMsg - 消息号
///  pUserData - 用户数据
///  pBuf - 数据指针
///  nLen - 数据长度
///  nParam - 参数
typedef long (_stdcall* fMsgCallback)(int nMsg, void* pUserData, char* pBuf, int nLen, int nParam);
typedef void (_stdcall* fOSDCallBack)(void* pUserData, ul hdc, int x, int y);
typedef int (_stdcall* fAudioCallBack)(void* pUserData, char* pBuf, int nLen);
typedef void (_stdcall* OnRequestKeyCallBack)(SecretKeyParamPtr, void*);

///  new api
ul _stdcall NAV_Create(int nType, ul hWnd[], int nCount, fMsgCallback fCallback, void* pUserData);
ul _stdcall NAV_InputStream(ul hPlay, int nIndex, char* pBuf, int nLen, ul* pulRemain);
ul _stdcall NAV_CapturePicture(ul hPlay, int nIndex, char* szFileName);
ul _stdcall NAV_Zoom(ul hPlay, int nIndex, int nCommand, int* pRect, ul hWnd);
ul _stdcall NAV_PlayFile(char* szFileName, ul hWnd, fMsgCallback fCallback, void* pUserData);
ul _stdcall NAV_SetVolume(int nVal);
ul _stdcall NAV_PlayFrame(ul hPlay, int nVal);
ul _stdcall NAV_Seek(ul hPlay, int nSec);
ul _stdcall NAV_SetSpeed(ul hPlay, int nVal);
ul _stdcall NAV_SetSound(ul hPlay, int nIndex, bool bOpen);
ul _stdcall NAV_Close(ul hPlay);
ul _stdcall NAV_Pause(ul hPlay, bool bPause);
ul _stdcall NAV_JsonCommand(char* szCommand, ul* pulRet, char* pBuf, int nLen);
ul _stdcall NAV_RegisterOSDCallBack(ul hPlay, int nIndex, fOSDCallBack fCallBack,
                                    void* pUserData);
ul _stdcall NAV_GetBufSize(ul hPlay, int nIndex, ul* pulTotal,
                           ul* pulRemain);
ul _stdcall NAV_ResetBuffer(ul hPlay);
ul _stdcall NAV_PauseEx(ul hPlay, bool bPause);
ul _stdcall NAV_SetParam(ul hPlay, int nType, int nParam);
ul _stdcall NAV_DecoderFrame(ul hPlay, char* pBuf, int nLen);
ul _stdcall NAV_AudioRecordStop();
ul _stdcall NAV_AudioRecordStart(void* pUserData, fAudioCallBack pCallBack, int nEncoder);
ul _stdcall NAV_GetInfo(ul hPlay, int nType, int nIndex, int nIn, int* pnOut);
ul _stdcall NAV_RegisterSecretKeyCallback(ul hPlay, OnRequestKeyCallBack callback,
        void* userdata);
bool _stdcall NAV_IsPause(ul hPlay);





#endif

