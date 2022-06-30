/********************************************************
    Copyright (C), 2007-2099,SZ-STREAMING Tech. Co., Ltd.
    File name:        
    Author:
        xzyang
    Date:        
    Description:
********************************************************/
#ifndef __RMFS_N9M_STRUCT_H__
#define __RMFS_N9M_STRUCT_H__
#include "rmfs_n9m_config.h"
 
typedef struct _rmfs_n9m_stream_attr_{/*������*/
    N9M_FS_UCHAR lock;/* �����ԣ�0-δ������1-�����������Ͳμ�lock_type*/
    N9M_FS_UCHAR resolution;/*�ֱ��ʣ�ȡֵ��ΧΪ:[0, 255]����ֵ���庬����Ӧ�ò����ж���ͽ���*/
    N9M_FS_UCHAR record_type;/*¼�����ͣ�ȡֵ��ΧΪ:[0, 15]����ֵ���庬����Ӧ�ò����ж���ͽ���*/
    N9M_FS_UCHAR tv_system;/*ϵͳ��ʽ��0��1�����������ϲ�Ӧ�����ж���*/
    N9M_FS_UCHAR have_audio;/*bit0:�Ƿ�����Ƶ��bit1:�Ƿ���Ƶ���� ��0��1�����������ϲ�Ӧ�����ж���*/
    N9M_FS_UCHAR DataMark;/*���ݱ�ʶ��ֵ�ĺ������ⲿ����,ȡֵ��Χ[0,1]*/
    N9M_FS_UCHAR reserve[2];
    N9M_FS_UINT lock_type;/*����ʱ��Ч, �����ͣ��������ϲ㶨�壬����bit0Ϊ�ֶ�������bit1Ϊ�Զ�����*/
    N9M_FS_ULL alarm_type;/*����¼��ʱ��Ч���������ͣ��������ϲ㶨��*/
}rmfs_n9m_stream_attr_t;


typedef struct _rmfs_n9m_create_ss_para_{/*����һ�����εĲ���*/
    /*ʱ����Ϣ����������ʱ����*/
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*[1, 12]*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    
    N9M_FS_UCHAR dst;/*0��ʾ��������ʱʱ�䣬1��ʾ������ʱʱ��*/

    /*ͨ����ʶ������һ��ͨ������ʹ��һ��ͨ���Ž��б�ʶ��Ҳ����ʹ��һ�����ƽ��б�ʶ�����߶���ͬʱ*/
    N9M_FS_UCHAR channel;/*����0��ͨ����[0, 0xfe]������ʹ��ͨ���Ž��б�ʶʱ����ֵΪ0xff*/
    N9M_FS_CHAR name[17];/*�����ַ�������Ч�ַ�Ϊ16��*/

    /*�������ͣ�ȡֵ��ΧΪ:[0, 255]����ֵ���庬����Ӧ�ò����ж���ͽ���*/
    N9M_FS_UCHAR stream_type;

    /*������ID*/
    N9M_FS_INT group_id;

    /*���������Ƿ�ΪԤ¼��0��ʾ���ǣ�1��ʾ��*/
    N9M_FS_UCHAR for_pre_record;

    /*������Ϣ*/
    rmfs_n9m_stream_attr_t attr;
}rmfs_n9m_create_ss_para_t;

typedef struct _n9m_fs_date_time_{
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*1, 12*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*0, 59*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR reserve1;
    N9M_FS_UCHAR reserve2;
}n9m_fs_date_time_t;

typedef struct _n9m_fs_date_{
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*[1, 12]*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR reserve;
}n9m_fs_date_t;

typedef struct _n9m_fs_time_{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR reserve;
}n9m_fs_time_t;

typedef struct _n9m_fs_record_date_info_
{
    n9m_fs_date_t date;
    N9M_FS_USHORT record_bitmap;
    N9M_FS_UCHAR lock;
}n9m_fs_record_date_info_t;

typedef struct _n9m_video_frame_info_{/*��Ƶ֡��Ϣ*/
    N9M_FS_UCHAR hour;
    N9M_FS_UCHAR minute;
    N9M_FS_UCHAR second;
    N9M_FS_BOOL is_i_frame;
    
    N9M_FS_UINT buffer_offset;/*���I֡�ڻ������е�λ��*/    
    N9M_FS_UINT pts_high_dword;
    N9M_FS_UINT pts_low_dword;    
}n9m_video_frame_info_t;

typedef struct _n9m_stream_segment_id_{/*����ID��Ψһ�ı�ʶһ������*/
    N9M_FS_UCHAR hdd_id;
    N9M_FS_UCHAR reserve[3];
    N9M_FS_UINT root_index;
    N9M_FS_UINT stream_segment_index;
	N9M_FS_UINT stream_segment_stamp;
}n9m_stream_segment_id_t;

typedef struct _rmfs_n9m_stream_device_info_{
    /*���ƺţ���Ч�ַ�Ϊ16��*/
    N9M_FS_CHAR vehicle_num[17];

    /*��˾���ƣ���Ч�ַ�Ϊ8��*/
    N9M_FS_CHAR company_name[9];

    N9M_FS_UCHAR reserve[2];
}rmfs_n9m_stream_device_info_t;

typedef struct _rmfs_n9m_stream_query_device_info_{
    /*�豸��Ϣ��������bit0:���ƺ�bit1:��˾����*/
    N9M_FS_UINT mask;
    /*�豸������Ϣ*/
    rmfs_n9m_stream_device_info_t device_info;
}rmfs_n9m_stream_query_device_info_t;

typedef enum _n9m_stream_query_cmd_{
    N9M_SQC_FIRST_PAGE,
    N9M_SQC_END_PAGE,
    N9M_SQC_NEXT_PAGE,
    N9M_SQC_PRE_PAGE
}n9m_stream_query_cmd_t;

typedef struct _n9m_stream_query_result_{/*���β�ѯ���*/
    N9M_FS_UCHAR start_hour;
    N9M_FS_UCHAR start_minute;
    N9M_FS_UCHAR start_second;
    N9M_FS_UCHAR end_hour;
    N9M_FS_UCHAR end_minute;
    N9M_FS_UCHAR end_second;
    N9M_FS_UCHAR channel;
    N9M_FS_UCHAR stream_type;
    N9M_FS_UCHAR record_type;
    N9M_FS_UCHAR lock;
    N9M_FS_UCHAR resolution;
    N9M_FS_UCHAR tv_system;
    N9M_FS_UCHAR have_audio;    /*bit0:have audio,bit1:only audio*/
    N9M_FS_UCHAR DataMark;
    N9M_FS_UINT lock_type;
    N9M_FS_ULL alarm_type;
    N9M_FS_ULL segment_length;
    n9m_stream_segment_id_t ssid;/*����ID*/
    rmfs_n9m_stream_query_device_info_t ssinfo;/*�����豸��Ϣ*/
}n9m_stream_query_result_t;

#define _N9M_NO_SEQUECE_ 0 /*������������򡢲�ѭ��*/
#define _N9M_SEQUECE_NO_CYCLE_ 1/*��������������С���ѭ��*/
#define _N9M_SEQUCE_CYCLE_ 2/*��������������С�ѭ��*/
#define _N9M_SEQUCE_DOWN_NO_CYCLE 3/*��������������С���ѭ��*/
#define _N9M_SEQUCE_DOWN_CYCLE 4/*��������������С�ѭ��*/
typedef struct _n9m_stream_query_{/*���β�ѯ*/
    N9M_FS_UINT group_bitmap;/*��ѯ��λͼ*/
    N9M_FS_UINT chn_bitmap;/*ͨ��λͼ��һ��BITλ����һ��ͨ��*/
    N9M_FS_UCHAR year;
    N9M_FS_UCHAR month;
    N9M_FS_UCHAR day;
    N9M_FS_UCHAR start_hour;
    N9M_FS_UCHAR start_minute;
    N9M_FS_UCHAR start_second;
    N9M_FS_UCHAR end_hour;
    N9M_FS_UCHAR end_minute;
    N9M_FS_UCHAR end_second;
    N9M_FS_UCHAR sequence_cycle;/*�Ƿ���Ҫ���򣬶��������б��ѯ������Ҫ���򣬶���ʱ��������������ȡֵΪ_N9M_NO_SEQUECE_��
                                    _N9M_SEQUECE_NO_CYCLE_��_N9M_SEQUCE_CYCLE_*/
    N9M_FS_UCHAR lock_bitmap;/*���������ͣ�����bitλ��ʾ, bit0Ϊ1ʱ��ѯδ����¼��bit1Ϊ1ʱ��ѯ����¼��*/
    N9M_FS_UCHAR record_type_bitmap;/*����¼�����ͣ�����bitλ��ʾ��bit0Ϊ1ʱ��ѯ����¼��bit1Ϊ1ʱ��ѯ����¼��*/
    N9M_FS_UINT lock_type;/*����������¼��ʱ��Ч����ʾ�����������*/
    N9M_FS_ULL alarm_type;/*����������¼��ʱ��Ч����ʾ����ı�������*/
    N9M_FS_ULL stream_type_bitmap;/*��������*/
    N9M_FS_UINT item_num_per_page;/*ÿҳ����Ŀ�ĸ���*/
    N9M_FS_UCHAR is_iframe; /*ֻ����I֡*/
    N9M_FS_UCHAR reserved[3];
}n9m_stream_query_t;

typedef struct _n9m_calendar_result_
{
    N9M_FS_USHORT record_bitmap;
    N9M_FS_UCHAR lock;
}n9m_calendar_result_t;

#define RMFS_MAX_CHN 32
#define RMFS_MAX_DAY 31
typedef struct _n9m_calendar_stream_query_{/*������ѯ*/
    /*��ѯ��λͼ*/
    N9M_FS_UINT group_bitmap;
    /*ͨ��λͼ��һ��BITλ����һ��ͨ��*/
    N9M_FS_UINT channel_bitmap;
    /*¼������λͼ*/
    N9M_FS_USHORT record_type_bitmap;
    /*��������*/
    N9M_FS_ULL stream_type_bitmap;
    /*ʱ����Ϣ*/
    N9M_FS_UCHAR year;
    N9M_FS_UCHAR month;
    N9M_FS_UCHAR reserve[3];
    /*���ؽ��*/    
    n9m_calendar_result_t calendar_info[RMFS_MAX_CHN][RMFS_MAX_DAY];
    /*����˫����ʱ�����������Ϣ*/
    n9m_calendar_result_t sub_calendar_info[RMFS_MAX_CHN][RMFS_MAX_DAY];
}n9m_calendar_stream_query_t;


typedef struct _n9m_stream_segment_info_{
    N9M_FS_UCHAR year;
    N9M_FS_UCHAR month;
    N9M_FS_UCHAR day;
    
    N9M_FS_UCHAR start_hour;
    N9M_FS_UCHAR start_minute;
    N9M_FS_UCHAR start_second;
    
    N9M_FS_UCHAR end_hour;
    N9M_FS_UCHAR end_minute;
    N9M_FS_UCHAR end_second;
    
    N9M_FS_UCHAR dst_flag;

    N9M_FS_UCHAR channel;
    N9M_FS_UCHAR resolution;
    N9M_FS_UCHAR record_type;
    N9M_FS_UCHAR have_audio;    /*bit0:have audio,bit1:only audio*/
    N9M_FS_UCHAR tv_system;
    N9M_FS_UCHAR lock;
    N9M_FS_UCHAR DataMark;
    
    N9M_FS_ULL stream_segment_len;
}n9m_stream_segment_info_t;


typedef struct _rmfs_n9m_hdd_info_{
    N9M_FS_UINT block_size;/*���ֽ�Ϊ��λ�Ŀ��С*/
    N9M_FS_UINT total_block_num;/*�ܿ���*/
    N9M_FS_UINT free_block_num;/*ʣ�����*/
}rmfs_n9m_hdd_info_t;

typedef struct _rmfs_n9m_stream_lock_para_
{
    N9M_FS_UINT group_bitmap;
    N9M_FS_UINT channel_bitmap;
    N9M_FS_ULL stream_type_bitmap;
    N9M_FS_USHORT record_type_bitmap;
    n9m_fs_date_time_t start_time;
    n9m_fs_date_time_t end_time;
}rmfs_n9m_stream_lock_para_t;

/*
    1��ÿ��Ӳ�̱��뱣��һ���Ŀռ䣬Ϊϵͳ�ָ���׼������Ӳ��ʣ��ռ�С�ڻ��ߵ������ֵʱ���Ͳ�������¼���ˣ������ֵΪreserve_free_size_for_record
    2�������л���ʱ��һ��Ӳ�̿���Ϊ¼��Ӳ�̣�����������һ��������Ҳ����ʣ��ռ䲻��С��ĳ��ֵ������¼һС���ֹͣ�ˣ�Ҳ��
            �׵��������ֵΪused_for_recording_free_size����Ȼ used_for_recording_free_size >= reserve_free_size_for_record
    3���������ǵ�������:
            1)���е��̵�ʣ��ռ䶼С��Y��Ҳ����û���̿ɹ�����
            2)�ɹ����õ�Ӳ�̵��ܵ�ʣ������С��һ����ֵ������ΪZ
    4���������Ǻ󣬵��ɹ����õ�Ӳ�̵��ܵ�ʣ����������һ����ֵ����ֹͣ���ǣ�����ΪM                        
*/
typedef struct _rmfs_n9m_hdd_overwrite_config_{
    N9M_FS_ULL reserve_free_size_for_record;
    N9M_FS_ULL used_for_recording_free_size;
    N9M_FS_ULL start_delete_free_size;
    N9M_FS_ULL delete_size_per_time;
}rmfs_n9m_hdd_overwrite_config_t;

/*
	������¼�񸲸����ò����ṹ��
*/
typedef struct _rmfs_n9m_mainstream_overwrite_config_{
    N9M_FS_UCHAR overwrite_enable;		//ʹ�ܿ��� 0:�ر� 1:��
    N9M_FS_UCHAR reserve[3];
    N9M_FS_UINT start_delete_hour_for_record;	//��ͨ����ʼ����¼��ʱ��
    N9M_FS_UINT reserve_hour_for_record;	//��ͨ��¼����ʱ�䣬��Сʱ��
    N9M_FS_ULL delete_size_per_time;		//һ��ѭ�����ɾ������
}rmfs_n9m_mainstream_overwrite_config_t;

/*
    �����εı�־
*/
/*��������*/
#define RMFS_N9M_OSF_CONTINUE   0x01


#define RMFS_N9M_OSF_DEFAULT RMFS_N9M_OSF_CONTINUE


typedef enum _n9m_hdd_overwrite_policy_{
    N9M_HOP_BY_CAPACITY,
    N9M_HOP_BY_DAYS        
}n9m_hdd_overwrite_policy_t;


typedef enum _rmfs_n9m_recovery_policy_{
    N9M_RRP_FAT32_DEPTH_L1,
    N9M_RRP_FAT32_DEPTH_L2,
    N9M_RRP_RAW_DEPTH_L1,
    N9M_RRP_RAW_DEPTH_L2
}rmfs_n9m_recovery_policy_t;

typedef struct _rmfs_n9m_stream_open_para_{
    N9M_FS_UCHAR channel;
    N9M_FS_UCHAR stream_type;
    N9M_FS_USHORT record_type_bitmap;
    N9M_FS_UINT group_bitmap;
    n9m_fs_date_time_t open_time;
}rmfs_n9m_stream_open_para_t;

typedef struct _rmfs_n9m_modify_segment_para_{
    N9M_FS_UINT group_bitmap;/*��Ҫ�޸ĵ���ID��ʹ��bitλ��ʾ*/
    N9M_FS_UINT channel_bitmap;/*��Ҫ�޸ĵ�ͨ����ʹ��bitλ��ʾ*/
    N9M_FS_ULL stream_type_bitmap;/*��Ҫ�޸ĵ��������ͣ�ʹ��bitλ��ʾ*/
    n9m_fs_date_time_t start_time;/*��Ҫ�޸ĵĿ�ʼʱ��*/
    n9m_fs_date_time_t end_time;/*��Ҫ�޸ĵĽ���ʱ��*/
    N9M_FS_UCHAR modfiy_mask; /*bit0-�޸ļ���״̬��bit1-�޸�¼������*/
    N9M_FS_UCHAR lock;/*����״̬��bit0Ϊ1ʱ��Ч*/
    N9M_FS_UCHAR record_type;/*¼�����ͣ�bit1Ϊ1ʱ��Ч*/
    N9M_FS_UINT lock_type; /*�������ͣ�ֵ�ĺ������ϲ㶨�壬����bit0-Ϊ�ֶ�������bit1-Ϊ�Զ�����*/
    N9M_FS_ULL alarm_type; /*�������ͣ�ֵ�ú������ϲ㶨��*/
}rmfs_n9m_modify_segment_para_t;

typedef struct _rmfs_n9m_delete_para_{
    N9M_FS_UINT group_bitmap;
    N9M_FS_UINT channel_bitmap;
    N9M_FS_ULL stream_type_bitmap;
    n9m_fs_date_time_t end_time;
}rmfs_n9m_delete_para_t;

typedef struct _rmfs_n9m_recovery_para_
{
    N9M_FS_UCHAR chn;
    N9M_FS_UCHAR stream_type;
    n9m_fs_date_t start_date;
    n9m_fs_date_t end_date;
}rmfs_n9m_recovery_para_t;

typedef struct _rmfs_n9m_recovery_stream_info_
{
    N9M_FS_UCHAR is_new_stream;
    N9M_FS_UCHAR chn;
    N9M_FS_UCHAR stream_type;
    n9m_fs_date_t stream_date;
}rmfs_n9m_recovery_stream_info_t;

typedef void * RMFS_HANDLE;

#define INVALID_RMFS_HANDLE NULL

#endif/*__RMFS_STRUCT_H__*/


