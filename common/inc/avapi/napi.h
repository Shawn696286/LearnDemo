

#ifndef   NAPI_H
#define   NAPI_H


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
///  错误码定义
#define   ER_SUCCESS           0    /// 成功
#define   ER_FAILED            1    /// 失败
#define   ER_PARAM_ERROR       2    /// 参数错误
#define   ER_PARSE_FAILED      3    /// 解析JSON失败
#define   ER_BUF_NOT_ENOUGH    4    /// 缓冲不够
#define   ER_TIME_OUT          5    /// 超时
#define   ER_DEV_OFFLINE       6    /// 设备不在线
#define   ER_DEV_CODE          7    /// 设备返回错误码在pulDevCode
#define   ER_CREATE_SOCKET     8    /// 创建socket失败
#define   ER_RW_FILE           9    /// 读写文件失败
#define   ER_USER             10    /// 用户名或密码错误
#define   ER_NOT_RIGHT        11    /// 没有权限
#define   ER_SVR_OFFLINE      12    /// 服务器未连接

///  消息号定义
#define   NMSG_VIDEO_STREAM    1    ///  视频流数据, nParam(1=I帧，2=P帧，3=音频帧)
#define   NMSG_JSON            2    ///  json字符串
#define   NMSG_DEV_OFFLINE     3    ///  设备下线(直连模式)
#define   NMSG_DEV_CODE        4    ///  设备返回失败，nParam为设备错误号
#define   NMSG_FILE_HEAD       5    ///  视频文件头
#define   NMSG_DISCONNECT      6    ///  网络断开
#define   NMSG_PLAY_END        7    ///  播放结束
#define   NMSG_KILL            8    ///  强制下线通知
#define   NMSG_SWITCH_STREAM   9    ///  设备切换流通知，nParam为流类型
#define   NMSG_DEV_ONLINE     10    ///  设备上线(直连模式) - 停用
#define   NMSG_BUFFERING      11    ///  正在缓冲
#define   NMSG_PLAYING        12    ///  正在播放
#define   NMSG_REG_ONLINE     13    ///  注册服务器上线
#define   NMSG_REG_OFFLINE    14    ///  注册服务器掉线
#define   NMSG_TASK_STOP      15    ///  任务结束，nParam为错误码
#define   NMSG_YUV_DATA       16    ///  解码后的YUV数据，420格式
#define   NMSG_TRANS_DATA     17    ///  透传数据
#define   NMSG_TALK_BREAK     18    ///  语音对讲中断
#define   NMSG_SEEK_START     19
#define   NMSG_AUDIO_RECORD_ERROR  20    ///  录音中断
#define   NMSG_USE            21    ///  被占用
#define   NMSG_S17_ERR        22    ///  S17错误码，nParam为错误码
#define   NMSG_MDVR_DATA      23    ///  mdvr设备数据回调
#define NMSG_FRAME_CALLBACK 24 /// 帧回调

///  回调函数定义
///  nMsg - 消息号
///  pUserData - 用户数据
///  pBuf - 数据指针
///  nLen - 数据长度
///  nParam - 参数
typedef long (_stdcall* fMsgCallback)(int nMsg, void* pUserData, char* pBuf, int nLen, int nParam);



///  功能: 发送指令
///  参数: szCommand - json字符串，定义见文档
///        pulRet - 返回结果，如句柄
///        pBuf - 输入或输出缓冲区
///        nLen - 缓冲区长度
///        pulDevCode - 返回设备错误码
unsigned long _stdcall NAPI_JsonCommand(char* szCommand, ul* pulRet, char* pBuf, int nLen, unsigned long* pulDevCode);



#endif
