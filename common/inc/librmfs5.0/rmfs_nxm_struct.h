/********************************************************
    Copyright (C), 2007-2099,SZ-STREAMING Tech. Co., Ltd.
    File name:
    Author:
        xzyang
    Date:
    Description:
********************************************************/
#ifndef __RMFS_NXM_STRUCT_H__
#define __RMFS_NXM_STRUCT_H__
#include "rmfs_n9m_config.h"

typedef struct _rmfs_nxm_stream_attr_ /*������*/
{
    N9M_FS_UCHAR lock;/* �����ԣ�0-δ������1-����*/
    N9M_FS_UCHAR resolution;/*�ֱ��ʣ�ȡֵ��ΧΪ:[0, 255]����ֵ���庬����Ӧ�ò����ж���ͽ���*/
    N9M_FS_UCHAR
    record_type;/*¼�����ͣ�ȡֵ��ΧΪ:[0, 15]����ֵ���庬����Ӧ�ò����ж���ͽ���*/
    N9M_FS_UCHAR tv_system;/*ϵͳ��ʽ��0��1�����������ϲ�Ӧ�����ж���*/
    N9M_FS_UCHAR audio;/*��Ƶ��0-����Ƶ��1-����Ƶ��2-����Ƶ����*/
    N9M_FS_UCHAR reserve[3];
    N9M_FS_ULL alarm_type[4];/*����¼��ʱ��Ч���������ͣ��������ϲ㶨��*/
} rmfs_nxm_stream_attr_t;


typedef struct _rmfs_nxm_create_ss_para_ /*����һ�����εĲ���*/
{
    /*������ID*/
    N9M_FS_UCHAR group_id;

    /*ʱ����Ϣ����������ʱ����*/
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*[1, 12]*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/

    N9M_FS_UCHAR channel;/*����0��ͨ����[0, 31]*/
    /*�������ͣ�ȡֵ��ΧΪ:[0, 255]����ֵ���庬����Ӧ�ò����ж���ͽ���*/
    N9M_FS_UCHAR stream_type;

    /*���������Ƿ�ΪԤ¼��0��ʾ���ǣ�1��ʾ��*/
    N9M_FS_UCHAR for_pre_record;
    N9M_FS_UCHAR reserved[2];

    N9M_FS_CHAR name[60];/*�ַ�����ʶ*/
    /*������Ϣ*/
    rmfs_nxm_stream_attr_t attr;
} rmfs_nxm_create_ss_para_t;

typedef struct _rmfs_nxm_date_time_
{
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*1, 12*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*0, 59*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR reserve1;
    N9M_FS_UCHAR reserve2;
} rmfs_nxm_date_time_t;

typedef struct _rmfs_nxm_date_
{
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*[1, 12]*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR reserve;
} rmfs_nxm_date_t;

typedef struct _rmfs_nxm_time_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR reserve;
} rmfs_nxm_time_t;

typedef struct _rmfs_nxm_record_date_info_
{
    rmfs_nxm_date_t date;
    N9M_FS_USHORT record_bitmap;
    N9M_FS_UCHAR lock;
} rmfs_nxm_record_date_info_t;

typedef struct _rmfs_nxm_stream_segment_id_ /*����ID��Ψһ�ı�ʶһ������*/
{
    N9M_FS_UCHAR hdd_id;
    N9M_FS_UCHAR reserve[3];
    N9M_FS_ULONG root_index;
    N9M_FS_ULONG stream_segment_index;
    N9M_FS_ULONG stream_segment_stamp;
} rmfs_nxm_stream_segment_id_t;

/*д��buff����ṹ��*/
typedef struct _rmfs_nxm_buffer_array_
{
    N9M_FS_CHAR* buffer;       ///< ָ��ǰbuffer��ָ�롣
    N9M_FS_ULONG len;    ///< ��ǰbufferָ�����ݵĳ��ȡ�
} rmfs_nxm_buffer_array_t;

/*д��Ƶ֡�ͺ�ϻ��֡һ��֡��Ϣ*/
typedef struct _rmfs_nxm_write_one_frame_info_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR sync_time_flag;/*�Ƿ���Уʱ��0-���� 1-��*/
    N9M_FS_ULONG frame_len;/*��һ�����ݳ���*/
    N9M_FS_ULONG iframe_len;/*I֡����*/
} rmfs_nxm_write_one_frame_info_t;

/*����Ƶ֡�ͺ�ϻ��֡һ��֡��Ϣ*/
typedef struct _rmfs_nxm_read_one_frame_info_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR channle;/*ͨ����[0, 31]*/
    N9M_FS_BOOL is_new_stream_segment;/*�Ƿ��µķֶ�����*/
} rmfs_nxm_read_one_frame_info_t;

/*д��־֡��Ϣ*/
typedef struct _rmfs_nxm_write_log_frame_info_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR sync_time_flag;/*�Ƿ���Уʱ��0-���� 1-��*/
    N9M_FS_ULONG frame_len;/*��һ�����ݳ���*/
    rmfs_nxm_stream_segment_id_t log_id;/*��־id,д��ɹ����ļ�ϵͳ����*/
} rmfs_nxm_write_log_frame_info_t;

/*дץ��ͼƬ֡��Ϣ*/
typedef struct _rmfs_nxm_write_snap_frame_info_
{
    N9M_FS_UCHAR stream_type;/*��������*/
    N9M_FS_UCHAR channel;/*ͨ����*/
    N9M_FS_UCHAR reserved[2];
    N9M_FS_ULONG frame_len;/*ͼƬ����*/
    N9M_FS_ULONG utc_time;/*ץ��ʱ���*/
    N9M_FS_UCHAR attached_info[236];/*ͼƬ������Ϣ*/
} rmfs_nxm_write_snap_frame_info_t;

typedef enum _rmfs_nxm_stream_query_cmd_
{
    NXM_SQC_FIRST_PAGE,
    NXM_SQC_END_PAGE,
    NXM_SQC_NEXT_PAGE,
    NXM_SQC_PRE_PAGE
} rmfs_nxm_stream_query_cmd_t;

typedef struct _rmfs_nxm_stream_query_result_ /*���β�ѯ���*/
{
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*1, 12*/
    N9M_FS_UCHAR day;/*[1, 31]*/
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
    N9M_FS_UCHAR have_audio;
    N9M_FS_ULL alarm_type[4];
    N9M_FS_ULL segment_length;
    N9M_FS_CHAR name[60];/*�ַ�����ʶ*/
    rmfs_nxm_stream_segment_id_t ssid;/*����ID*/
} rmfs_nxm_stream_query_result_t;

#define _NXM_NO_SEQUECE_ 0 /*������������򡢲�ѭ��*/
#define _NXM_SEQUECE_NO_CYCLE_ 1/*��������������С���ѭ��*/
#define _NXM_SEQUCE_CYCLE_ 2/*��������������С�ѭ��*/
#define _NXM_SEQUCE_DOWN_NO_CYCLE 3/*��������������С���ѭ��*/
#define _NXM_SEQUCE_DOWN_CYCLE 4/*��������������С�ѭ��*/
typedef struct _rmfs_nxm_stream_query_ /*���β�ѯ*/
{
    N9M_FS_ULONG group_bitmap;/*��ѯ��λͼ*/
    N9M_FS_ULONG chn_bitmap;/*ͨ��λͼ��һ��BITλ����һ��ͨ��*/
    rmfs_nxm_date_time_t start_time;
    rmfs_nxm_date_time_t end_time;
    N9M_FS_UCHAR
    sequence_cycle;/*�Ƿ���Ҫ���򣬶��������б��ѯ������Ҫ���򣬶���ʱ��������������ȡֵΪ_NXM_NO_SEQUECE_��
                                    _NXM_SEQUECE_NO_CYCLE_��_NXM_SEQUCE_CYCLE_*/
    N9M_FS_UCHAR
    lock_bitmap;/*���������ͣ�����bitλ��ʾ, bit0Ϊ1ʱ��ѯδ����¼��bit1Ϊ1ʱ��ѯ����¼��*/
    N9M_FS_UCHAR
    record_type_bitmap;/*����¼�����ͣ�����bitλ��ʾ��bit0Ϊ1ʱ��ѯ����¼��bit1Ϊ1ʱ��ѯ����¼��*/
    N9M_FS_ULL alarm_type[4];/*����������¼��ʱ��Ч����ʾ����ı�������*/
    N9M_FS_ULL stream_type_bitmap;/*��������*/
    N9M_FS_ULONG item_num_per_page;/*ÿҳ����Ŀ�ĸ���*/
    N9M_FS_UCHAR is_iframe; /*ֻ����I֡*/
    N9M_FS_UCHAR reserved[2];
    N9M_FS_UCHAR is_search_by_name;/*��������Ƿ�ƥ���ַ�����ʶ��0-��ƥ�� 1-ƥ��*/
    N9M_FS_CHAR name[60];
} rmfs_nxm_stream_query_t;

typedef struct _rmfs_nxm_calendar_result_
{
    N9M_FS_USHORT record_bitmap;
    N9M_FS_UCHAR lock;
} rmfs_nxm_calendar_result_t;

#define RMFS_NXM_MAX_CHN 32
#define RMFS_NXM_MAX_DAY 31
typedef struct _rmfs_nxm_calendar_stream_query_ /*������ѯ*/
{
    /*��ѯ��λͼ*/
    N9M_FS_ULONG group_bitmap;
    /*ͨ��λͼ��һ��BITλ����һ��ͨ��*/
    N9M_FS_ULONG channel_bitmap;
    /*¼������λͼ*/
    N9M_FS_USHORT record_type_bitmap;
    /*��������*/
    N9M_FS_ULL stream_type_bitmap;
    /*ʱ����Ϣ*/
    N9M_FS_UCHAR year;
    N9M_FS_UCHAR month;
    N9M_FS_UCHAR reserve;
    /*��ѯ����Ƿ��ַ���ƥ�� 0-��ƥ�� 1-ƥ��*/
    N9M_FS_UCHAR is_search_by_name;
    N9M_FS_CHAR name[60];
    /*���ؽ��*/
    rmfs_nxm_calendar_result_t calendar_info[RMFS_NXM_MAX_CHN][RMFS_NXM_MAX_DAY];
    /*����˫����ʱ�����������Ϣ*/
    rmfs_nxm_calendar_result_t sub_calendar_info[RMFS_NXM_MAX_CHN][RMFS_NXM_MAX_DAY];
} rmfs_nxm_calendar_stream_query_t;


typedef struct _rmfs_nxm_stream_segment_info_
{
    N9M_FS_UCHAR year;
    N9M_FS_UCHAR month;
    N9M_FS_UCHAR day;

    N9M_FS_UCHAR start_hour;
    N9M_FS_UCHAR start_minute;
    N9M_FS_UCHAR start_second;

    N9M_FS_UCHAR end_hour;
    N9M_FS_UCHAR end_minute;
    N9M_FS_UCHAR end_second;

    N9M_FS_UCHAR channel;
    N9M_FS_UCHAR resolution;
    N9M_FS_UCHAR record_type;
    N9M_FS_UCHAR audio;
    N9M_FS_UCHAR tv_system;
    N9M_FS_UCHAR lock;
    N9M_FS_UCHAR reserved;
    N9M_FS_CHAR name[60];
    N9M_FS_ULL stream_segment_len;
} rmfs_nxm_stream_segment_info_t;


typedef struct _rmfs_nxm_hdd_info_
{
    N9M_FS_ULONG block_size;/*���ֽ�Ϊ��λ�Ŀ��С*/
    N9M_FS_ULONG total_block_num;/*�ܿ���*/
    N9M_FS_ULONG free_block_num;/*ʣ�����*/
} rmfs_nxm_hdd_info_t;

/*fuse������Ϣ*/
typedef struct _rmfs_nxm_fuse_info_
{
    N9M_FS_ULL start_offset;/*��Դ�����ʼƫ����*/
    N9M_FS_ULL total_size;  /*�ܴ�С*/
    N9M_FS_UCHAR cur_disk_id;
    N9M_FS_UCHAR reserved[3];
} rmfs_nxm_fuse_info_t;

typedef struct _rmfs_nxm_stream_lock_para_
{
    N9M_FS_ULONG group_bitmap;
    N9M_FS_ULONG channel_bitmap;
    N9M_FS_ULL stream_type_bitmap;
    N9M_FS_USHORT record_type_bitmap;
    rmfs_nxm_date_time_t start_time;
    rmfs_nxm_date_time_t end_time;
} rmfs_nxm_stream_lock_para_t;

/*
    1��ÿ��Ӳ�̱��뱣��һ���Ŀռ䣬Ϊϵͳ�ָ���׼������Ӳ��ʣ��ռ�С�ڻ��ߵ������ֵʱ���Ͳ�������¼���ˣ������ֵΪreserve_free_size_for_record
    2�������л���ʱ��һ��Ӳ�̿���Ϊ¼��Ӳ�̣�����������һ��������Ҳ����ʣ��ռ䲻��С��ĳ��ֵ������¼һС���ֹͣ�ˣ�Ҳ��
            �׵��������ֵΪused_for_recording_free_size����Ȼ used_for_recording_free_size >= reserve_free_size_for_record
    3���������ǵ�������:
            1)���е��̵�ʣ��ռ䶼С��Y��Ҳ����û���̿ɹ�����
            2)�ɹ����õ�Ӳ�̵��ܵ�ʣ������С��һ����ֵ������ΪZ
    4���������Ǻ󣬵��ɹ����õ�Ӳ�̵��ܵ�ʣ����������һ����ֵ����ֹͣ���ǣ�����ΪM
*/
typedef struct _rmfs_nxm_hdd_overwrite_config_
{
    N9M_FS_ULL reserve_free_size_for_record;
    N9M_FS_ULL used_for_recording_free_size;
    N9M_FS_ULL start_delete_free_size;
    N9M_FS_ULL delete_size_per_time;
} rmfs_nxm_hdd_overwrite_config_t;

/*
    ������¼�񸲸����ò����ṹ��
*/
typedef struct _rmfs_nxm_mainstream_overwrite_config_
{
    N9M_FS_UCHAR overwrite_enable;      //ʹ�ܿ��� 0:�ر� 1:��
    N9M_FS_UCHAR reserve[3];
    N9M_FS_ULONG start_delete_hour_for_record;  //��ͨ����ʼ����¼��ʱ��
    N9M_FS_ULONG reserve_hour_for_record;   //��ͨ��¼����ʱ�䣬��Сʱ��
    N9M_FS_ULL delete_size_per_time;        //һ��ѭ�����ɾ������
} rmfs_nxm_mainstream_overwrite_config_t;

/*
    �����εı�־
*/
/*��������*/
#define RMFS_NXM_OSF_CONTINUE   0x01


#define RMFS_NXM_OSF_DEFAULT RMFS_NXM_OSF_CONTINUE


typedef enum _nxm_hdd_overwrite_policy_
{
    NXM_HOP_BY_CAPACITY,
    NXM_HOP_BY_DAYS
} nxm_hdd_overwrite_policy_t;

//
//typedef enum _rmfs_nxm_recovery_policy_
//{
//    N9M_RRP_FAT32_DEPTH_L1,
//    N9M_RRP_FAT32_DEPTH_L2,
//    N9M_RRP_RAW_DEPTH_L1,
//    N9M_RRP_RAW_DEPTH_L2
//} rmfs_nxm_recovery_policy_t;

typedef struct _rmfs_nxm_stream_open_para_
{
    N9M_FS_ULONG group_bitmap;
    N9M_FS_ULONG channel_bitmap;
    N9M_FS_UCHAR stream_type;
    N9M_FS_UCHAR reserved;
    N9M_FS_USHORT record_type_bitmap;
    rmfs_nxm_date_time_t open_time;
} rmfs_nxm_stream_open_para_t;

typedef struct _rmfs_nxm_modify_segment_para_
{
    N9M_FS_ULONG group_bitmap;/*��Ҫ�޸ĵ���ID��ʹ��bitλ��ʾ*/
    N9M_FS_ULONG channel_bitmap;/*��Ҫ�޸ĵ�ͨ����ʹ��bitλ��ʾ*/
    N9M_FS_ULL stream_type_bitmap;/*��Ҫ�޸ĵ��������ͣ�ʹ��bitλ��ʾ*/
    rmfs_nxm_date_time_t start_time;/*��Ҫ�޸ĵĿ�ʼʱ��*/
    rmfs_nxm_date_time_t end_time;/*��Ҫ�޸ĵĽ���ʱ��*/
    N9M_FS_UCHAR modfiy_mask; /*bit0-�޸ļ���״̬��bit1-�޸�¼������*/
    N9M_FS_UCHAR lock;/*����״̬��bit0Ϊ1ʱ��Ч*/
    N9M_FS_UCHAR record_type;/*¼�����ͣ�bit1Ϊ1ʱ��Ч*/
    N9M_FS_ULONG
    lock_type; /*�������ͣ�ֵ�ĺ������ϲ㶨�壬����bit0-Ϊ�ֶ�������bit1-Ϊ�Զ�����*/
    N9M_FS_ULL alarm_type[4]; /*�������ͣ�ֵ�ú������ϲ㶨��*/
} rmfs_nxm_modify_segment_para_t;

typedef struct _rmfs_nxm_delete_para_
{
    N9M_FS_ULONG group_bitmap;
    N9M_FS_ULONG channel_bitmap;
    N9M_FS_ULL stream_type_bitmap;
    rmfs_nxm_date_time_t end_time;
} rmfs_nxm_delete_para_t;

typedef struct _rmfs_nxm_recovery_para_
{
    N9M_FS_ULONG chn_bitmap;
    N9M_FS_ULONG stream_bitmap;
    rmfs_nxm_date_t start_date;
    rmfs_nxm_date_t end_date;
} rmfs_nxm_recovery_para_t;

typedef struct _rmfs_nxm_recovery_stream_info_
{
    N9M_FS_UCHAR is_new_stream;
    N9M_FS_UCHAR chn;
    N9M_FS_UCHAR stream_type;
    rmfs_nxm_date_t stream_date;
} rmfs_nxm_recovery_stream_info_t;

typedef struct _rmfs_nxm_snap_info_query_result_ /*ץ�İ�����Ϣ��ѯ���*/
{
    rmfs_nxm_stream_segment_id_t ssid;/*ץ��ͼƬID*/
    N9M_FS_ULONG length;/*ͼƬ����*/
    N9M_FS_UCHAR attached_info[236];/*������Ϣ*/
} rmfs_nxm_snap_info_query_result_t;

typedef struct _rmfs_nxm_snap_query_ /*ץ�Ĳ�ѯ*/
{
    N9M_FS_ULONG group_bitmap;/*��ѯ��λͼ*/
    N9M_FS_UCHAR
    sequence_cycle;/*�Ƿ���Ҫ���򣬶��������б��ѯ������Ҫ���򣬶���ʱ��������������ȡֵΪ_NXM_NO_SEQUECE_��
                                    _NXM_SEQUECE_NO_CYCLE_��_NXM_SEQUCE_CYCLE_*/
    N9M_FS_UCHAR reserved[3];
} rmfs_nxm_snap_query_t;

#endif/*__RMFS_STRUCT_H__*/


