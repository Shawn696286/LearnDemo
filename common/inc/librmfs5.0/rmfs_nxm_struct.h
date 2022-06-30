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

typedef struct _rmfs_nxm_stream_attr_ /*流属性*/
{
    N9M_FS_UCHAR lock;/* 锁属性，0-未加锁，1-加锁*/
    N9M_FS_UCHAR resolution;/*分辨率，取值范围为:[0, 255]，该值具体含义由应用层自行定义和解释*/
    N9M_FS_UCHAR
    record_type;/*录像类型，取值范围为:[0, 15]，该值具体含义由应用层自行定义和解释*/
    N9M_FS_UCHAR tv_system;/*系统制式，0或1，代表含义由上层应用自行定义*/
    N9M_FS_UCHAR audio;/*音频，0-无音频，1-有音频，2-纯音频数据*/
    N9M_FS_UCHAR reserve[3];
    N9M_FS_ULL alarm_type[4];/*报警录像时有效，报警类型，含义由上层定义*/
} rmfs_nxm_stream_attr_t;


typedef struct _rmfs_nxm_create_ss_para_ /*创建一个流段的参数*/
{
    /*磁盘组ID*/
    N9M_FS_UCHAR group_id;

    /*时间信息，即年月日时分秒*/
    N9M_FS_UCHAR year;/*[0, 99]*/
    N9M_FS_UCHAR month;/*[1, 12]*/
    N9M_FS_UCHAR day;/*[1, 31]*/
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/

    N9M_FS_UCHAR channel;/*基于0的通道号[0, 31]*/
    /*码流类型，取值范围为:[0, 255]，该值具体含义由应用层自行定义和解释*/
    N9M_FS_UCHAR stream_type;

    /*创建流段是否为预录，0表示不是，1表示是*/
    N9M_FS_UCHAR for_pre_record;
    N9M_FS_UCHAR reserved[2];

    N9M_FS_CHAR name[60];/*字符串标识*/
    /*属性信息*/
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

typedef struct _rmfs_nxm_stream_segment_id_ /*流段ID，唯一的标识一个流段*/
{
    N9M_FS_UCHAR hdd_id;
    N9M_FS_UCHAR reserve[3];
    N9M_FS_ULONG root_index;
    N9M_FS_ULONG stream_segment_index;
    N9M_FS_ULONG stream_segment_stamp;
} rmfs_nxm_stream_segment_id_t;

/*写流buff数组结构体*/
typedef struct _rmfs_nxm_buffer_array_
{
    N9M_FS_CHAR* buffer;       ///< 指向当前buffer的指针。
    N9M_FS_ULONG len;    ///< 当前buffer指向数据的长度。
} rmfs_nxm_buffer_array_t;

/*写视频帧和黑匣子帧一秒帧信息*/
typedef struct _rmfs_nxm_write_one_frame_info_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR sync_time_flag;/*是否有校时，0-不是 1-是*/
    N9M_FS_ULONG frame_len;/*这一秒数据长度*/
    N9M_FS_ULONG iframe_len;/*I帧长度*/
} rmfs_nxm_write_one_frame_info_t;

/*读视频帧和黑匣子帧一秒帧信息*/
typedef struct _rmfs_nxm_read_one_frame_info_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR channle;/*通道号[0, 31]*/
    N9M_FS_BOOL is_new_stream_segment;/*是否新的分段数据*/
} rmfs_nxm_read_one_frame_info_t;

/*写日志帧信息*/
typedef struct _rmfs_nxm_write_log_frame_info_
{
    N9M_FS_UCHAR hour;/*[0, 23]*/
    N9M_FS_UCHAR minute;/*[0, 59]*/
    N9M_FS_UCHAR second;/*[0, 59]*/
    N9M_FS_UCHAR sync_time_flag;/*是否有校时，0-不是 1-是*/
    N9M_FS_ULONG frame_len;/*这一秒数据长度*/
    rmfs_nxm_stream_segment_id_t log_id;/*日志id,写入成功后文件系统返回*/
} rmfs_nxm_write_log_frame_info_t;

/*写抓拍图片帧信息*/
typedef struct _rmfs_nxm_write_snap_frame_info_
{
    N9M_FS_UCHAR stream_type;/*码流类型*/
    N9M_FS_UCHAR channel;/*通道号*/
    N9M_FS_UCHAR reserved[2];
    N9M_FS_ULONG frame_len;/*图片长度*/
    N9M_FS_ULONG utc_time;/*抓拍时间点*/
    N9M_FS_UCHAR attached_info[236];/*图片伴随信息*/
} rmfs_nxm_write_snap_frame_info_t;

typedef enum _rmfs_nxm_stream_query_cmd_
{
    NXM_SQC_FIRST_PAGE,
    NXM_SQC_END_PAGE,
    NXM_SQC_NEXT_PAGE,
    NXM_SQC_PRE_PAGE
} rmfs_nxm_stream_query_cmd_t;

typedef struct _rmfs_nxm_stream_query_result_ /*流段查询结果*/
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
    N9M_FS_CHAR name[60];/*字符串标识*/
    rmfs_nxm_stream_segment_id_t ssid;/*流段ID*/
} rmfs_nxm_stream_query_result_t;

#define _NXM_NO_SEQUECE_ 0 /*搜索结果不排序、不循环*/
#define _NXM_SEQUECE_NO_CYCLE_ 1/*搜索结果升序排列、不循环*/
#define _NXM_SEQUCE_CYCLE_ 2/*搜索结果升序排列、循环*/
#define _NXM_SEQUCE_DOWN_NO_CYCLE 3/*搜索结果降序排列、不循环*/
#define _NXM_SEQUCE_DOWN_CYCLE 4/*搜索结果降序排列、循环*/
typedef struct _rmfs_nxm_stream_query_ /*流段查询*/
{
    N9M_FS_ULONG group_bitmap;/*查询组位图*/
    N9M_FS_ULONG chn_bitmap;/*通道位图，一个BIT位代表一个通道*/
    rmfs_nxm_date_time_t start_time;
    rmfs_nxm_date_time_t end_time;
    N9M_FS_UCHAR
    sequence_cycle;/*是否需要排序，对于流段列表查询，则需要排序，对于时间轴则无需排序，取值为_NXM_NO_SEQUECE_、
                                    _NXM_SEQUECE_NO_CYCLE_、_NXM_SEQUCE_CYCLE_*/
    N9M_FS_UCHAR
    lock_bitmap;/*搜索锁类型，采用bit位表示, bit0为1时查询未加锁录像，bit1为1时查询加锁录像*/
    N9M_FS_UCHAR
    record_type_bitmap;/*搜索录像类型，采用bit位表示，bit0为1时查询常规录像，bit1为1时查询报警录像*/
    N9M_FS_ULL alarm_type[4];/*当搜索报警录像时有效，表示具体的报警类型*/
    N9M_FS_ULL stream_type_bitmap;/*码流类型*/
    N9M_FS_ULONG item_num_per_page;/*每页的条目的个数*/
    N9M_FS_UCHAR is_iframe; /*只搜索I帧*/
    N9M_FS_UCHAR reserved[2];
    N9M_FS_UCHAR is_search_by_name;/*搜索结果是否匹配字符串标识，0-不匹配 1-匹配*/
    N9M_FS_CHAR name[60];
} rmfs_nxm_stream_query_t;

typedef struct _rmfs_nxm_calendar_result_
{
    N9M_FS_USHORT record_bitmap;
    N9M_FS_UCHAR lock;
} rmfs_nxm_calendar_result_t;

#define RMFS_NXM_MAX_CHN 32
#define RMFS_NXM_MAX_DAY 31
typedef struct _rmfs_nxm_calendar_stream_query_ /*月历查询*/
{
    /*查询组位图*/
    N9M_FS_ULONG group_bitmap;
    /*通道位图，一个BIT位代表一个通道*/
    N9M_FS_ULONG channel_bitmap;
    /*录像类型位图*/
    N9M_FS_USHORT record_type_bitmap;
    /*码流类型*/
    N9M_FS_ULL stream_type_bitmap;
    /*时间信息*/
    N9M_FS_UCHAR year;
    N9M_FS_UCHAR month;
    N9M_FS_UCHAR reserve;
    /*查询结果是否字符串匹配 0-不匹配 1-匹配*/
    N9M_FS_UCHAR is_search_by_name;
    N9M_FS_CHAR name[60];
    /*返回结果*/
    rmfs_nxm_calendar_result_t calendar_info[RMFS_NXM_MAX_CHN][RMFS_NXM_MAX_DAY];
    /*搜索双码流时存放子码流信息*/
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
    N9M_FS_ULONG block_size;/*以字节为单位的块大小*/
    N9M_FS_ULONG total_block_num;/*总块数*/
    N9M_FS_ULONG free_block_num;/*剩余块数*/
} rmfs_nxm_hdd_info_t;

/*fuse分区信息*/
typedef struct _rmfs_nxm_fuse_info_
{
    N9M_FS_ULL start_offset;/*相对磁盘起始偏移量*/
    N9M_FS_ULL total_size;  /*总大小*/
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
    1，每个硬盘必须保留一定的空间，为系统恢复做准备，当硬盘剩余空间小于或者等于这个值时，就不可以再录像了，假设此值为reserve_free_size_for_record
    2，当进行换盘时，一个硬盘可作为录像硬盘，他必须满足一定条件，也就是剩余空间不能小于某个值，否则录一小会就停止了，也不
            妥当，假设此值为used_for_recording_free_size，显然 used_for_recording_free_size >= reserve_free_size_for_record
    3，启动覆盖的条件是:
            1)所有的盘的剩余空间都小于Y，也就是没有盘可供换了
            2)可供换置的硬盘的总的剩余容量小于一定数值，假设为Z
    4，启动覆盖后，当可供换置的硬盘的总的剩余容量大于一定数值，即停止覆盖，假设为M
*/
typedef struct _rmfs_nxm_hdd_overwrite_config_
{
    N9M_FS_ULL reserve_free_size_for_record;
    N9M_FS_ULL used_for_recording_free_size;
    N9M_FS_ULL start_delete_free_size;
    N9M_FS_ULL delete_size_per_time;
} rmfs_nxm_hdd_overwrite_config_t;

/*
    主码流录像覆盖配置参数结构体
*/
typedef struct _rmfs_nxm_mainstream_overwrite_config_
{
    N9M_FS_UCHAR overwrite_enable;      //使能开关 0:关闭 1:打开
    N9M_FS_UCHAR reserve[3];
    N9M_FS_ULONG start_delete_hour_for_record;  //单通道开始覆盖录像时长
    N9M_FS_ULONG reserve_hour_for_record;   //单通道录像保留时间，按小时计
    N9M_FS_ULL delete_size_per_time;        //一个循环最大删除容量
} rmfs_nxm_mainstream_overwrite_config_t;

/*
    打开流段的标志
*/
/*连续查找*/
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
    N9M_FS_ULONG group_bitmap;/*需要修改的组ID，使用bit位表示*/
    N9M_FS_ULONG channel_bitmap;/*需要修改的通道，使用bit位表示*/
    N9M_FS_ULL stream_type_bitmap;/*需要修改的码流类型，使用bit位表示*/
    rmfs_nxm_date_time_t start_time;/*需要修改的开始时间*/
    rmfs_nxm_date_time_t end_time;/*需要修改的结束时间*/
    N9M_FS_UCHAR modfiy_mask; /*bit0-修改加锁状态，bit1-修改录像类型*/
    N9M_FS_UCHAR lock;/*加锁状态，bit0为1时有效*/
    N9M_FS_UCHAR record_type;/*录像类型，bit1为1时有效*/
    N9M_FS_ULONG
    lock_type; /*加锁类型，值的含义由上层定义，比如bit0-为手动加锁，bit1-为自动加锁*/
    N9M_FS_ULL alarm_type[4]; /*报警类型，值得含义由上层定义*/
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

typedef struct _rmfs_nxm_snap_info_query_result_ /*抓拍伴随信息查询结果*/
{
    rmfs_nxm_stream_segment_id_t ssid;/*抓拍图片ID*/
    N9M_FS_ULONG length;/*图片长度*/
    N9M_FS_UCHAR attached_info[236];/*伴随信息*/
} rmfs_nxm_snap_info_query_result_t;

typedef struct _rmfs_nxm_snap_query_ /*抓拍查询*/
{
    N9M_FS_ULONG group_bitmap;/*查询组位图*/
    N9M_FS_UCHAR
    sequence_cycle;/*是否需要排序，对于流段列表查询，则需要排序，对于时间轴则无需排序，取值为_NXM_NO_SEQUECE_、
                                    _NXM_SEQUECE_NO_CYCLE_、_NXM_SEQUCE_CYCLE_*/
    N9M_FS_UCHAR reserved[3];
} rmfs_nxm_snap_query_t;

#endif/*__RMFS_STRUCT_H__*/


