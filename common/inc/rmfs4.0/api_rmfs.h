#ifndef _API_RMFS_H__
#define _API_RMFS_H__
#include "rmfs_n9m_struct.h"

#ifdef WIN32
#define N9M_DLL_API _declspec(dllexport)
#else
#define N9M_DLL_API
#endif

/*********************************************************************  
    Description: 
        初始化特殊文件系统。使用特殊文件系统，必须先初始化
    Input: 
        rmfs_type------0:标准文件系统 1:低端机专用文件系统
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_init(N9M_FS_UCHAR rmfs_type);

/*********************************************************************  
    Description: 
        去初始化特殊文件系统
    Input: 
        无
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_uinit();

/*********************************************************************  
    Description: 
        设置文件系统调试等级
    Input:  
        debug_level------取值范围0-4。0调试等级最低，也就是输出的调试信息最少
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_set_debug_level(N9M_FS_UINT debug_level);

/*********************************************************************  
    Description: 
        重建文件系统在windows下依赖的分区和FAT表。windows下需为物理磁盘名(如"\\\\.\\PhysicalDrive1"),而不是盘符(如"H:"),同时调用该接口的用户，要有能操作裸设备的权限;
        linux下为磁盘设备名(如"/dev/sda"),而不是分区名(如:"/dev/sda1")，该接口不会破坏磁盘内原有录像，在设备上能正常使用，而PC上无法识别时调用
    Input:  
        hdd_id------硬盘ID,也就是硬盘的自编号，由应用层决定，不过需要保证不同的磁盘ID需要不一样，取值范围0-32
        p_dev_name------硬盘设备文件名
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_rebuild_rely(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);


/*********************************************************************  
    Description: 
        将硬盘格式化为特殊文件系统。windows下需为物理磁盘名(如"\\\\.\\PhysicalDrive1"),而不是盘符(如"H:"),同时调用该接口的用户，要有能操作裸设备的权限;
        linux下为磁盘设备名(如"/dev/sda"),而不是分区名(如:"/dev/sda1")
    Input:  
        hdd_id------硬盘ID,也就是硬盘的自编号，由应用层决定，不过需要保证不同的磁盘ID需要不一样，取值范围0-32
        p_dev_name------硬盘设备文件名
        p_serial_num------设备序列号。如果不需要记录设备序列号，该值可以置为FS_NULL
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_format(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, N9M_FS_CHAR *p_serial_num);

/*********************************************************************  
    Description: 
        快速格式化，在windows上调用时，只能格式化已经为N9M文件系统的硬盘，否则会返回失败
    Input:  
        hdd_id------硬盘ID
        p_dev_name------硬盘设备文件名，windows下为逻辑盘符
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_fast_format(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);

/*********************************************************************  
    Description: 
        加载特殊文件系统硬盘。windows下需为物理磁盘名(如"\\\\.\\PhysicalDrive1"),而不是盘符(如"H:"),同时调用该接口的用户，要有能操作裸设备的权限;
        linux下为磁盘设备名(如"/dev/sda"),而不是分区名(如:"/dev/sda1")
    Input:  
        hdd_id------硬盘ID,也就是硬盘的自编号，由应用层决定，不过需要保证不同的磁盘ID需要不一样，取值范围0-32
        p_dev_name------硬盘设备文件名
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_mount(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);

/*********************************************************************  
    Description: 
        由于windows直接读取物理设备有权限限制，针对这个特性特别提供一个widows上的挂载接口，使用该接口挂载的硬盘仅能使用读接口，无法使用写和数据恢复接口
    Input:  
        hdd_id------硬盘ID,也就是硬盘的自编号，由应用层决定，不过需要保证不同的磁盘ID需要不一样，取值范围0-32
        part_num------分区数
        p_part_name------分区名 (注意:必须按分区顺序填入，否则导致读取数据异常)
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_mount_for_windows(N9M_FS_UCHAR hdd_id, N9M_FS_INT part_num, N9M_FS_CHAR *p_part_name[N9M_FS_MAX_PARTITION_NUM]);

/*********************************************************************  
    Description: 
        卸载特殊文件系统硬盘
    Input:  
        hdd_id------硬盘ID
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_umount(N9M_FS_UCHAR hdd_id);

/*********************************************************************  
    Description: 
        获取硬盘信息
    Input:  
        hdd_id------硬盘ID
    output:
        p_hdd_info------硬盘信息
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_hdd_info(N9M_FS_UCHAR hdd_id, rmfs_n9m_hdd_info_t *p_hdd_info);

/*********************************************************************  
    Description: 
        添加硬盘到指定磁盘组
    Input:  
        hdd_id------硬盘ID
        group_id------组ID，由应用层确定，取值0-32。可以通过api_rmfs_read_device_info得到设备信息，设备信息一样的，证明硬盘来自于同一个设备，
        请添加到同一个组，通过组将多个硬盘合并成一个存储设备来操作。
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_add_disk_to_group(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR group_id);

/*********************************************************************  
    Description: 
        获取指定磁盘组的硬盘数目
    Input:  
        group_id------组ID
    output:
        无
    Return: 
        负数:失败
        其他:指定组的硬盘数目
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_disk_num_from_group(N9M_FS_UCHAR group_id);

/*********************************************************************  
    Description: 
        获取指定磁盘组的硬盘成员。
    Input:  
        group_id------组ID
        p_disk_list------磁盘成员列表缓存
        list_size------列表缓存大小
    output:
        p_disk_list------硬盘成员列表
    Return: 
        负数:失败
        其他:指定组中实际存在的硬盘数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_disk_list_from_group(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_disk_list, N9M_FS_INT list_size);

/*********************************************************************  
    Description: 
        从指定磁盘组移除硬盘
    Input:  
        hdd_id------硬盘ID
        group_id------组ID
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_disk_from_group(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR group_id);

/*********************************************************************  
    Description: 
        创建一个流段。stream_type的值由上层定义并解释
    Input:  
        p_rcsp------创建流段参数
    output:
        无
    Return: 
        -1:失败
        其他:流段描述ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_create_stream_segment(rmfs_n9m_create_ss_para_t *p_rcsp, rmfs_n9m_stream_device_info_t *p_devinfo = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        通过流段ID打开流段
    Input:  
        pStream_segment_id------流段ID。通常上层不用理解其内容，在搜索时文件系统返回
        record_type_bitmap------录像类型位图
        auto_jump------是否在读取结束时，自动跳转到下一流段。FS_TRUE,自动跳转；FS_FALSE，不自动跳转
    output:
        无
    Return: 
        -1:失败
        其他:流段描述ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_open_stream_segment_by_id(n9m_stream_segment_id_t *pStream_segment_id, N9M_FS_USHORT record_type_bitmap, N9M_FS_BOOL auto_jump);

/*********************************************************************  
    Description: 
        通过流段ID打开流段
    Input:  
        pStream_segment_id------流段ID。通常上层不用理解其内容，在搜索时文件系统返回
        expect_len------期望读取长度。如果该值大于流段长度，表示该段可能由于报警被拆分，但下载需要完整的数据
    output:
        无
    Return: 
        -1:失败
        其他:流段描述ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_special_open_stream_segment(n9m_stream_segment_id_t *pStream_segment_id, N9M_FS_ULL expect_len);

/*********************************************************************  
    Description: 
        通过参数直接打开符合条件的流段
    Input:  
        open_para------打开参数，其中的码流类型，当group_bitmap不为0时，按bitmap来，当group_bitmap为0时，按数值来
        auto_jump------是否在读取结束时，自动跳转到下一流段。FS_TRUE,自动跳转；FS_FALSE，不自动跳转
    output:
        无
    Return: 
        -1:失败
        其他:流段描述ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_open_stream_segment_by_stream_bitmap_para(rmfs_n9m_stream_open_para_t *p_open_para, N9M_FS_UCHAR auto_jump);
    
/*********************************************************************  
    Description: 
        通过参数直接打开符合条件的流段
    Input:  
        open_para------打开参数
        auto_jump------是否在读取结束时，自动跳转到下一流段。FS_TRUE,自动跳转；FS_FALSE，不自动跳转
    output:
        无
    Return: 
        -1:失败
        其他:流段描述ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_open_stream_segment_by_para(rmfs_n9m_stream_open_para_t *p_open_para, N9M_FS_UCHAR auto_jump);

/*********************************************************************  
    Description: 
        通过时间定位打开流段的读写位置。录像数据流(大流段)写时不支持该接口
    Input:  
        ssfd------流段描述ID
        p_date_time------定位时间
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_seek_stream_segment_by_time(N9M_FS_INT ssfd, n9m_fs_date_time_t *p_date_time);

/*********************************************************************  
    Description: 
        通过偏移量定位打开流段的读写位置。录像数据流(大流段)写时不支持该接口
    Input:  
        ssfd------流段描述ID
        offset------偏移量
        whence------便宜其实位置。取值为SEEK_SET, SEEK_CUR, SEEK_END
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_seek_stream_segment_by_offset(N9M_FS_INT ssfd, N9M_FS_LL offset, N9M_FS_INT whence);

/*********************************************************************  
    Description: 
        获取当前读写指针相对于流段起始位置的偏移量
    Input:  
        ssfd------流段描述ID
    output:
        p_offset------当前读写偏移量
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_stream_segment_tell(N9M_FS_INT ssfd, N9M_FS_LL *p_offset);

/*********************************************************************  
    Description: 
        关闭打开的流段
    Input:  
        ssfd------流段描述ID
        p_stream_info---流段信息
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_close_stream_segment(N9M_FS_INT ssfd, n9m_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        写入数据
    Input:  
        ssfd------流段描述ID
        p_buffer------数据缓冲区
        len------写入数据长度
        frame_num------写入缓冲区的帧数，可只记录I帧数。小流段时，该值填0
        p_vdi------帧信息。小流段时，该值填FS_NULL
    output:
        无
    Return: 
        -1:失败
        其他:实际写入的数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_video_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_INT frame_num, n9m_video_frame_info_t *p_vdi);

/*********************************************************************  
    Description: 
        将指定流段的数据从内核缓存同步到硬盘
    Input:  
        ssfd------流段描述ID
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_fsync(N9M_FS_INT ssfd);

/*********************************************************************  
    Description: 
        读取数据
    Input:  
        ssfd------流段描述ID
        p_buffer------数据缓冲区
        len------期望读取数据长度
    output:
        pNew_stream_segment------如果打开时是自动跳转，那么该值表示是否跳到了一个新的流段。不需要该值时，可以填成FS_NULL
    Return: 
        -1:失败
        其他:实际读取的数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_video_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        读取当前位置向后第n个I帧
    Input:  
        ssfd------流段描述ID
        jump_iframe_num------跳过的I帧数目
    output:
        p_frame_buffer------I帧数据地址
        p_frame_len------I帧数据长度
        pNew_stream_segment------如果打开时是自动跳转，那么该值表示是否跳到了一个新的流段。不需要该值时，可以填成FS_NULL
    Return: 
        -1:失败
        其他:实际读取的数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_next_iframe(N9M_FS_INT ssfd, N9M_FS_UCHAR jump_iframe_num, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        读取当前位置向前第n个I帧
    Input:  
        ssfd------流段描述ID
        jump_iframe_num------跳过的I帧数目
    output:
        p_frame_buffer------I帧数据地址
        p_frame_len------I帧数据长度
        pNew_stream_segment------如果打开时是自动跳转，那么该值表示是否跳到了一个新的流段。不需要该值时，可以填成FS_NULL
    Return: 
        -1:失败
        其他:实际读取的数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_pre_iframe(N9M_FS_INT ssfd, N9M_FS_UCHAR jump_iframe_num, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        获取查询句柄
    Input:  
        p_query_para------查询参数。注意:如果参数中的sequence_cycle为0时，该模式下，没有对数据进行统计分析，
        仅为了快速搜索到结果，不能进行向前翻页，也无法跳到指定页，
    output:
        无
    Return: 
        -1:失败
        其他:查询描述符
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_query_stream_segment_handle(n9m_stream_query_t *p_query_para, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        获取查询句柄
    Input:  
        query_handle------查询描述符
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_close_query_stream_segment_handle(N9M_FS_INT query_handle);

/*********************************************************************  
    Description: 
        翻页查询
    Input:  
        query_handle------查询描述符
        query_cmd------翻页指令
    output:
        p_get_num------结果条数
        p_query_result------搜索结果
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_query_stream_segment(N9M_FS_INT query_handle, n9m_stream_query_cmd_t query_cmd, N9M_FS_INT *p_get_num, n9m_stream_query_result_t *p_query_result);

/*********************************************************************  
    Description: 
        获取满足条件的总页数
    Input:  
        query_handle------查询描述符
    output:
        无
    Return: 
        -1:失败
        其他:满足条件的总页数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_total_page_num(N9M_FS_INT query_handle);

/*********************************************************************  
    Description: 
        调转到指定搜索页
    Input:  
        query_handle------查询描述符
        page_num------指定页码
    output:
        p_get_num------结果条数
        p_query_result------搜索结果
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_jump_specific_page(N9M_FS_INT handle, N9M_FS_INT page_num, N9M_FS_INT *pGet_num, n9m_stream_query_result_t *pStream_segment_list);

/*********************************************************************  
    Description: 
        获取指定条件流的天数
    Input:  
        group_bitmap------搜索组位图
        stream_type------搜索码流类型
    output:
        无
    Return: 
        负数:失败
        其他:有指定条件流的天数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_num(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        获取指定流类型的日期列表.
    Input:  
        group_bitmap------搜索组位图
        stream_type------搜索码流类型
        p_date_list------满足搜索条件的流日期列表缓存
        list_size------列表缓存大小
    output:
        无
    Return: 
        负数:失败
        其他:有指定条件流的实际天数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_list(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, n9m_fs_date_t *p_date_list, N9M_FS_INT list_size, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        获取指定条件流的天数
    Input:  
        group_bitmap------搜索组位图
        stream_type------搜索码流类型
        chn_bitmap------搜索通道。使用bit位表示。
    output:
        无
    Return: 
        负数:失败
        其他:有指定条件流的天数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_info_num(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        获取指定流类型的日期列表.
    Input:  
        group_bitmap------搜索组位图
        stream_type------搜索码流类型
        chn_bitmap------搜索通道。使用bit位表示。
        p_record_list------满足搜索条件的流日期列表缓存
        list_size------列表缓存大小
    output:
        无
    Return: 
        负数:失败
        其他:有指定条件流的实际天数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_info(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, n9m_fs_record_date_info_t *p_record_list, N9M_FS_INT list_size, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        获取月历表
    Input:  
        p_query_para------月历表查询条件
    output:
        record_bitmap------月历表。该值存放在p_query_para结构下的record_bitmap中
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_query_calendar(n9m_calendar_stream_query_t *p_query_para, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        通过流段ID对流段进行加锁
    Input:  
        p_stream_segment_id------流段ID
        lock------加锁标识。0-解锁；1-加锁
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_stream_segment_lock_by_id(n9m_stream_segment_id_t *p_stream_segment_id, N9M_FS_UCHAR lock);

/*********************************************************************  
    Description: 
        通过时间对流段数据加锁
    Input:  
        p_stream_segment_id------流段ID
        lock------加锁标识。0-解锁；1-加锁
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_stream_segment_lock_by_time(rmfs_n9m_stream_lock_para_t  *p_lock_para, N9M_FS_UCHAR lock);

/*********************************************************************  
    Description: 
        自动解锁指定条件的流段
    Input:  
        p_cur_date_time------当前时间
        reserve_days------加锁天数
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_auto_unlock(n9m_fs_date_time_t *p_cur_date_time, N9M_FS_INT reserve_days);

/*********************************************************************  
    Description: 
        查找当前可以写数据的工作磁盘。写数据前，先调用该接口，查看是否有可以工作的磁盘
    Input:  
        group_id------组ID
    output:
        p_cur_disk_id---当前工作磁盘ID
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_find_work_hdd(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_cur_disk_id);

/*********************************************************************  
    Description: 
        设置覆盖参数。如果上层不调用该接口进行配置，那么文件系统采用默认值进行处理
    Input:  
        group_id------组ID
        p_rhoc------覆盖参数
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_config_overwrite(N9M_FS_UCHAR group_id, rmfs_n9m_hdd_overwrite_config_t *p_rhoc);

/*********************************************************************  
    Description: 
        硬盘覆盖。由于文件系统库内，不创建线程。所以需要上层调用该接口进行覆盖操作。
    Input:  
        group_id------组ID
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_overwrite_big_stream(N9M_FS_INT GroupId);

/*********************************************************************  
    Description: 
        硬盘覆盖。由于文件系统库内，不创建线程。所以需要上层调用该接口进行覆盖操作。
    Input:  
        group_id------组ID
        check_video_exist------检测小流当天对应的录像是否存在，true表示如果当天有录像，则不覆盖，false表示不管有没有录像都覆盖
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_overwrite_small_stream(N9M_FS_INT GroupId, N9M_FS_UINT reserve_days, N9M_FS_BOOL check_video_exist);

/*********************************************************************  
    Description: 
        通过流段打开句柄获取相应的流段ID
    Input:  
        ssfd------流段描述ID
    output:
        p_ssid------流段ID
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_fd_info(N9M_FS_INT ssfd, n9m_stream_segment_id_t *p_ssid);

/*********************************************************************  
    Description: 
        通过流段ID获取相应的流段信息。
    Input:  
        p_ssid------流段ID
    output:
        p_stream_info------流段信息
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_info(n9m_stream_segment_id_t *p_ssid, n9m_stream_segment_info_t *p_stream_info);

/*********************************************************************  
    Description: 
        通过流段ID获取指定时间段的数据信息
    Input:  
        p_ssid------流段ID
        start_time------开始时间
        end_time------结束时间
    output:
        p_offset------指定开始时间的数据在流段内的偏移量
        p_data_len------指定时间段内的数据长度
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, N9M_FS_ULL *p_data_len);

/*********************************************************************  
    Description: 
        通过流段ID获取指定时间段的数据信息
    Input:  
        p_ssid------流段ID
        start_time------开始时间
        end_time------结束时间
        out_search------是否往流段后搜索，可能报警将流段拆分，但下载又需要上次搜索的完整数据
    output:
        p_offset------指定开始时间的数据在流段内的偏移量
        p_data_len------指定时间段内的数据长度
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_special_get_stream_segment_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, N9M_FS_ULL *p_data_len, N9M_FS_BOOL out_search);

/*********************************************************************  
    Description: 
        打开普通文件
    Input:  
        group_id------磁盘组ID
        p_file_name------文件名称,最多14个字节，包括结束符。
        open_mode------打开模式。0，如果文件不存在，创建文件后返回文件描述符；如果文件存在，清空文件内容后返回；
                                 1，如果文件不存在，创建文件后返回文件描述符；如果文件存在，在文件尾追加写入，也就是打开后将读写指针置于文件尾；
                                 2，如果文件不存在，直接返回失败；存在则打开，并将读写指针置于文件开始；
                                 3, 以只读方式打开，如果文件不存在直接返回错误
    output:
        无
    Return: 
        INVALID_RMFS_HANDLE:失败
        其他:普通文件打开描述符
 ********************************************************************/
N9M_DLL_API RMFS_HANDLE api_rmfs_open_normal_file(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name, N9M_FS_INT open_mode);

/*********************************************************************  
    Description: 
        往普通文件内写入数据
    Input:  
        file_handle------普通文件描述符
        p_buffer------数据缓冲区
        buffer_len------写入数据长度
    output:
        无
    Return: 
        -1:失败
        其他:实际写入数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_normal_file(RMFS_HANDLE file_handle, N9M_FS_CHAR *p_buffer, N9M_FS_INT buffer_len);

/*********************************************************************  
    Description: 
        将写入的普通文件数据强制刷入硬盘
    Input:  
        file_handle------普通文件描述符
    output:
        无
    Return: 
        0:成功
        -1:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_sync_normal_file(RMFS_HANDLE file_handle);

/*********************************************************************  
    Description: 
        从普通文件内读取数据
    Input:  
        file_handle------普通文件描述符
        p_buffer------数据缓冲区
        buffer_len------期望读取数据长度
    output:
        无
    Return: 
        -1:失败
        其他:实际读取数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_normal_file(RMFS_HANDLE file_handle, N9M_FS_CHAR *p_buffer, N9M_FS_INT buffer_len);

/*********************************************************************  
    Description: 
        获取当前读写位置
    Input:  
        file_handle------普通文件描述符
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_normal_file_cur_offset(RMFS_HANDLE file_handle, N9M_FS_LL &offset);

/*********************************************************************  
    Description: 
        通过偏移量定位普通文件读写位置
    Input:  
        file_handle------普通文件描述符
        offset------定位偏移量
        whence------定位起始位置。SEEK_SET-文件开始，SEEK_CUR-当前位置，SEEK_END-文件尾
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_seek_normal_file(RMFS_HANDLE file_handle, N9M_FS_LL offset, N9M_FS_INT whence);

/*********************************************************************  
    Description: 
        关闭普通文件。
    Input:  
        file_handle------普通文件描述符
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_close_normal_file(RMFS_HANDLE file_handle);

/*********************************************************************  
    Description: 
        获取普通文件大小
    Input:  
        file_handle------普通文件描述符
    output:
        无
    Return: 
        -1:失败
        其他:普通文件的大小，以字节为单位
 ********************************************************************/
N9M_DLL_API N9M_FS_LL api_rmfs_get_normal_file_size_by_handle(RMFS_HANDLE file_handle);

/*********************************************************************  
    Description: 
        获取普通文件大小
    Input:  
        group_id------磁盘组ID
        p_file_name------文件名称
    output:
        无
    Return: 
        -1:失败
        其他:普通文件的大小，以字节为单位
 ********************************************************************/
N9M_DLL_API N9M_FS_LL api_rmfs_get_normal_file_size(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        删除普通文件
    Input:  
        group_id------磁盘组ID
        p_file_name------文件名称
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_normal_file(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        获取查询句柄
    Input:  
        group_id------磁盘组ID
        p_file_name------文件名称。可以是全部文件名，也可以是部分文件名
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API RMFS_HANDLE api_rmfs_get_search_normal_file_handle(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        获取查询文件名
    Input:  
        search_handle------搜索句柄
        opt_mark------操作标记。0-第一个文件，1-下一个文件，2-上一个文件，3-最后一个文件。
    output:
        p_file_name------文件名。存储空间要大于14个字节
    Return: 
        -1:失败
        0:到达结束位置
        1:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_normal_file_name(RMFS_HANDLE search_handle, N9M_FS_UCHAR opt_mark, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        释放查询句柄
    Input:  
        search_handle------搜索句柄
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_release_search_normal_file_handle(RMFS_HANDLE search_handle);

/*********************************************************************  
    Description: 
        将预录流段改为常规或报警流段
    Input:  
        ssfd------流段描述ID
        record_type------录像类型
        alarm_type------报警类型
        lock------是否加锁
        lock_type------加锁类型。
        start_time------起始时间。如果该流段的起始时间在该时间之前，那么调用该接口后之前的预录将被删除
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_pre_record_info(N9M_FS_INT ssfd, N9M_FS_UCHAR record_type, N9M_FS_ULL alarm_type, N9M_FS_UCHAR lock, N9M_FS_UINT lock_type, n9m_fs_time_t start_time, n9m_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        覆盖预录流段
    Input:  
        ssfd------流段描述ID
        end_time------删除截止时间
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_overwrite_pre_record_stream(N9M_FS_INT ssfd, n9m_fs_time_t end_time);

/*********************************************************************  
    Description: 
        修改指定流的结束时间。调用该接口后，指定流段end_time之后的数据会全部被删除。
        该接口不能操作正在写的流段，需要关闭后再修改。
    Input:  
        ssid------流段ID
        end_time------流段结束时间
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_stream_segment_end_time(n9m_stream_segment_id_t ssid, n9m_fs_time_t end_time);

/*********************************************************************  
    Description: 
        修改流段录像类型和加锁状态
    Input:  
        p_modify_para------修改参数
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_stream_segment_info(rmfs_n9m_modify_segment_para_t *p_modify_para);

/*********************************************************************  
    Description: 
        根据打开描述符修改流段信息
    Input:  
        ssfd------流段描述符
        modify_mask------bit0-修改加锁状态，bit1-修改录像类型
        lock------是否加锁
        lock_type------加锁类型
        record_type------录像类型
        alarm_type------报警类型
        p_start_time------开始修改时间,如果为N9M_FS_NULL时，修改整个流段
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_stream_segment_info_by_fd(N9M_FS_INT ssfd, N9M_FS_UCHAR modify_mask, N9M_FS_UCHAR lock, N9M_FS_UINT lock_type, N9M_FS_UCHAR record_type, N9M_FS_ULL alarm_type, n9m_fs_time_t *p_start_time, n9m_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        往指定硬盘中写入设备信息，改信息结构由上层定义
    Input:  
        hdd_id------硬盘ID
        p_dev_info------设备信息缓存
        dev_info_len------设备信息长度
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_device_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_info, N9M_FS_INT dev_info_len);

/*********************************************************************  
    Description: 
        往所有已加载的硬盘中写入设备信息
    Input:
        p_dev_info------设备信息缓存
        dev_info_len------设备信息长度
    output:
        无
    Return: 
        -1:失败
        0:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_device_info_to_all_disk(N9M_FS_CHAR *p_dev_info, N9M_FS_INT dev_info_len);

/*********************************************************************  
    Description: 
        获取指定硬盘中的设备信息数据长度
    Input:  
        hdd_id------硬盘ID
    output:
        无
    Return: 
        -1:失败
        其他:设备信息数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_device_info_len(N9M_FS_UCHAR hdd_id);

/*********************************************************************  
    Description: 
        获取指定硬盘中的设备信息
    Input:  
        hdd_id------硬盘ID
        p_read_buffer------获取设备信息缓冲
        buffer_len------设备信息缓冲长度
    output:
        无
    Return: 
        -1:失败
        其他:设备信息数据长度
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_device_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_read_buffer, N9M_FS_INT buffer_len);

/*********************************************************************  
    Description: 
        测试硬盘接口
    Input:  
        hdd_id------硬盘ID
        data_size------测试数据长度
    output:
        无
    Return: 
        -1:失败
        其他:成功
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_test_hdd(N9M_FS_UCHAR hdd_id, N9M_FS_UINT data_size);

/*********************************************************************  
    Description: 
        用于恢复指定条件的内的损坏的录像数据
    Input:  
        hdd_id------硬盘ID
        p_dev_name------硬盘设备文件名
        p_recovery_para------恢复条件
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_recovery(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, rmfs_n9m_recovery_para_t *p_recovery_para);

/*********************************************************************  
    Description: 
        自动删除过期录像，建议启动或日期变化时调用
    Input:  
        p_cur_date_time------当前时间
        reserve_days------保留天数
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_auto_delete(n9m_fs_date_time_t *p_cur_date_time, N9M_FS_INT reserve_days, N9M_FS_UINT group_bitmap);

/*********************************************************************  
    Description: 
        根据参数删除流段
    Input:  
        p_delete_para------删除参数
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_stream_segment_by_para(rmfs_n9m_delete_para_t *p_delete_para);

/*********************************************************************  
    Description: 
        根据流段ID删除流段
    Input:  
        pStream_segment_id------流段ID
    output: 
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_stream_segment(n9m_stream_segment_id_t *pStream_segment_id);

/*********************************************************************  
    Description: 
       获取普通文件操作的错误码
    Input:  
        无
    output: 
        无
    Return: 
        错误码:-1-目标组无有效硬盘，-2-参数非法，-3-其他用户正在操作，-4-文件异常
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_last_error();

/*********************************************************************  
    Description: 
        获取双码流流段月历表
    Input:  
        p_query_para------月历表查询条件
    output:
        record_bitmap------月历表。该值存放在p_query_para结构下的record_bitmap中
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_query_calendar_more(n9m_calendar_stream_query_t *p_query_para, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        设置主码流录像覆盖参数。如果上层不调用该接口进行配置，那么文件系统默认关闭该功能
    Input:  
        group_id------组ID
        p_rhoc------覆盖参数
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_config_overwrite_mainstream(N9M_FS_UCHAR group_id, rmfs_n9m_mainstream_overwrite_config_t *p_rhoc);

/*********************************************************************  
    Description: 
       主码流录像覆盖接口。由于文件系统库内，不创建线程。所以需要上层调用该接口进行覆盖操作。
    Input:  
        group_id------组ID
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_overwrite_mainstream(N9M_FS_INT GroupId);

/*********************************************************************  
    Description: 
        获取车辆信息列表
    Input:  
        group_bitmap------搜索组位图
        stream_type_bitmap------搜索码流类型,按bit设置
        mask----------搜索类型掩码bit0:车牌号 bit1:公司名称
        p_info_list------满足搜索条件的流段车辆信息列表
        list_size------列表缓存大小
    output:
        无
    Return: 
        负数:失败
        其他:有指定条件流的实际个数
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_device_info_list(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_UINT mask, rmfs_n9m_stream_device_info_t *p_info_list, N9M_FS_INT list_size);

/*********************************************************************  
    Description: 
        设置写流段是否自动fsync
    Input:  
        hdd_id------硬盘ID,也就是硬盘的自编号，由应用层决定，不过需要保证不同的磁盘ID需要不一样，取值范围0-32
        is_sync-----自动fsync使能
    output:
        无
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_set_auto_fsync(N9M_FS_UCHAR hdd_id, N9M_FS_BOOL is_sync);

/*********************************************************************  
    Description: 
        通过流段ID获取指定时间段的I帧数据信息
    Input:  
        p_ssid------流段ID
        start_time------开始时间
        end_time------结束时间
    output:
        p_offset------指定开始时间的数据在流段内的偏移量
        p_stream_info------流段I帧信息
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_iframe_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, n9m_stream_segment_info_t *p_stream_info);

/*********************************************************************  
    Description: 
        通过流段ID获取指定时间段的I帧数据信息
    Input:  
        p_ssid------流段ID
        start_time------开始时间
        end_time------结束时间
        search_len------是否往流段后搜索，可能报警将流段拆分，但下载又需要上次搜索的完整数据
    output:
        p_offset------指定开始时间的数据在流段内的偏移量
        p_stream_info------流段I帧信息
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_special_get_stream_segment_iframe_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, n9m_stream_segment_info_t *p_stream_info, N9M_FS_ULL search_len);

/*********************************************************************  
    Description: 
        通过流段ID获取车辆信息列表
    Input:  
        p_ssid------流段ID
    output:
        p_device_info------流段车辆信息
    Return: 
        0:成功
        非0:失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_device_info(n9m_stream_segment_id_t *p_ssid, rmfs_n9m_stream_device_info_t *p_device_info);

/*********************************************************************  
    Description: 
        windows下设置特殊文件系统是否可写
    Input:  
        hdd_id------硬盘ID
        write_enable------可写状态。0-不可写，1-可写
    output: 
        无
    Return: 
        错误码:0-成功，-1-失败
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_set_rmfs_write_attr_for_windows(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR write_enable);

#endif

