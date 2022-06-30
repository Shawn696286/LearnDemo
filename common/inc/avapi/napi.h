

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
///  �����붨��
#define   ER_SUCCESS           0    /// �ɹ�
#define   ER_FAILED            1    /// ʧ��
#define   ER_PARAM_ERROR       2    /// ��������
#define   ER_PARSE_FAILED      3    /// ����JSONʧ��
#define   ER_BUF_NOT_ENOUGH    4    /// ���岻��
#define   ER_TIME_OUT          5    /// ��ʱ
#define   ER_DEV_OFFLINE       6    /// �豸������
#define   ER_DEV_CODE          7    /// �豸���ش�������pulDevCode
#define   ER_CREATE_SOCKET     8    /// ����socketʧ��
#define   ER_RW_FILE           9    /// ��д�ļ�ʧ��
#define   ER_USER             10    /// �û������������
#define   ER_NOT_RIGHT        11    /// û��Ȩ��
#define   ER_SVR_OFFLINE      12    /// ������δ����

///  ��Ϣ�Ŷ���
#define   NMSG_VIDEO_STREAM    1    ///  ��Ƶ������, nParam(1=I֡��2=P֡��3=��Ƶ֡)
#define   NMSG_JSON            2    ///  json�ַ���
#define   NMSG_DEV_OFFLINE     3    ///  �豸����(ֱ��ģʽ)
#define   NMSG_DEV_CODE        4    ///  �豸����ʧ�ܣ�nParamΪ�豸�����
#define   NMSG_FILE_HEAD       5    ///  ��Ƶ�ļ�ͷ
#define   NMSG_DISCONNECT      6    ///  ����Ͽ�
#define   NMSG_PLAY_END        7    ///  ���Ž���
#define   NMSG_KILL            8    ///  ǿ������֪ͨ
#define   NMSG_SWITCH_STREAM   9    ///  �豸�л���֪ͨ��nParamΪ������
#define   NMSG_DEV_ONLINE     10    ///  �豸����(ֱ��ģʽ) - ͣ��
#define   NMSG_BUFFERING      11    ///  ���ڻ���
#define   NMSG_PLAYING        12    ///  ���ڲ���
#define   NMSG_REG_ONLINE     13    ///  ע�����������
#define   NMSG_REG_OFFLINE    14    ///  ע�����������
#define   NMSG_TASK_STOP      15    ///  ���������nParamΪ������
#define   NMSG_YUV_DATA       16    ///  ������YUV���ݣ�420��ʽ
#define   NMSG_TRANS_DATA     17    ///  ͸������
#define   NMSG_TALK_BREAK     18    ///  �����Խ��ж�
#define   NMSG_SEEK_START     19
#define   NMSG_AUDIO_RECORD_ERROR  20    ///  ¼���ж�
#define   NMSG_USE            21    ///  ��ռ��
#define   NMSG_S17_ERR        22    ///  S17�����룬nParamΪ������
#define   NMSG_MDVR_DATA      23    ///  mdvr�豸���ݻص�
#define NMSG_FRAME_CALLBACK 24 /// ֡�ص�

///  �ص���������
///  nMsg - ��Ϣ��
///  pUserData - �û�����
///  pBuf - ����ָ��
///  nLen - ���ݳ���
///  nParam - ����
typedef long (_stdcall* fMsgCallback)(int nMsg, void* pUserData, char* pBuf, int nLen, int nParam);



///  ����: ����ָ��
///  ����: szCommand - json�ַ�����������ĵ�
///        pulRet - ���ؽ��������
///        pBuf - ��������������
///        nLen - ����������
///        pulDevCode - �����豸������
unsigned long _stdcall NAPI_JsonCommand(char* szCommand, ul* pulRet, char* pBuf, int nLen, unsigned long* pulDevCode);



#endif
