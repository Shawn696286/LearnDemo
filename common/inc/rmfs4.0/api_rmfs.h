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
        ��ʼ�������ļ�ϵͳ��ʹ�������ļ�ϵͳ�������ȳ�ʼ��
    Input: 
        rmfs_type------0:��׼�ļ�ϵͳ 1:�Ͷ˻�ר���ļ�ϵͳ
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_init(N9M_FS_UCHAR rmfs_type);

/*********************************************************************  
    Description: 
        ȥ��ʼ�������ļ�ϵͳ
    Input: 
        ��
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_uinit();

/*********************************************************************  
    Description: 
        �����ļ�ϵͳ���Եȼ�
    Input:  
        debug_level------ȡֵ��Χ0-4��0���Եȼ���ͣ�Ҳ��������ĵ�����Ϣ����
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_set_debug_level(N9M_FS_UINT debug_level);

/*********************************************************************  
    Description: 
        �ؽ��ļ�ϵͳ��windows�������ķ�����FAT��windows����Ϊ���������(��"\\\\.\\PhysicalDrive1"),�������̷�(��"H:"),ͬʱ���øýӿڵ��û���Ҫ���ܲ������豸��Ȩ��;
        linux��Ϊ�����豸��(��"/dev/sda"),�����Ƿ�����(��:"/dev/sda1")���ýӿڲ����ƻ�������ԭ��¼�����豸��������ʹ�ã���PC���޷�ʶ��ʱ����
    Input:  
        hdd_id------Ӳ��ID,Ҳ����Ӳ�̵��Ա�ţ���Ӧ�ò������������Ҫ��֤��ͬ�Ĵ���ID��Ҫ��һ����ȡֵ��Χ0-32
        p_dev_name------Ӳ���豸�ļ���
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_rebuild_rely(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);


/*********************************************************************  
    Description: 
        ��Ӳ�̸�ʽ��Ϊ�����ļ�ϵͳ��windows����Ϊ���������(��"\\\\.\\PhysicalDrive1"),�������̷�(��"H:"),ͬʱ���øýӿڵ��û���Ҫ���ܲ������豸��Ȩ��;
        linux��Ϊ�����豸��(��"/dev/sda"),�����Ƿ�����(��:"/dev/sda1")
    Input:  
        hdd_id------Ӳ��ID,Ҳ����Ӳ�̵��Ա�ţ���Ӧ�ò������������Ҫ��֤��ͬ�Ĵ���ID��Ҫ��һ����ȡֵ��Χ0-32
        p_dev_name------Ӳ���豸�ļ���
        p_serial_num------�豸���кš��������Ҫ��¼�豸���кţ���ֵ������ΪFS_NULL
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_format(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, N9M_FS_CHAR *p_serial_num);

/*********************************************************************  
    Description: 
        ���ٸ�ʽ������windows�ϵ���ʱ��ֻ�ܸ�ʽ���Ѿ�ΪN9M�ļ�ϵͳ��Ӳ�̣�����᷵��ʧ��
    Input:  
        hdd_id------Ӳ��ID
        p_dev_name------Ӳ���豸�ļ�����windows��Ϊ�߼��̷�
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_fast_format(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);

/*********************************************************************  
    Description: 
        ���������ļ�ϵͳӲ�̡�windows����Ϊ���������(��"\\\\.\\PhysicalDrive1"),�������̷�(��"H:"),ͬʱ���øýӿڵ��û���Ҫ���ܲ������豸��Ȩ��;
        linux��Ϊ�����豸��(��"/dev/sda"),�����Ƿ�����(��:"/dev/sda1")
    Input:  
        hdd_id------Ӳ��ID,Ҳ����Ӳ�̵��Ա�ţ���Ӧ�ò������������Ҫ��֤��ͬ�Ĵ���ID��Ҫ��һ����ȡֵ��Χ0-32
        p_dev_name------Ӳ���豸�ļ���
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_mount(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);

/*********************************************************************  
    Description: 
        ����windowsֱ�Ӷ�ȡ�����豸��Ȩ�����ƣ������������ر��ṩһ��widows�ϵĹ��ؽӿڣ�ʹ�øýӿڹ��ص�Ӳ�̽���ʹ�ö��ӿڣ��޷�ʹ��д�����ݻָ��ӿ�
    Input:  
        hdd_id------Ӳ��ID,Ҳ����Ӳ�̵��Ա�ţ���Ӧ�ò������������Ҫ��֤��ͬ�Ĵ���ID��Ҫ��һ����ȡֵ��Χ0-32
        part_num------������
        p_part_name------������ (ע��:���밴����˳�����룬�����¶�ȡ�����쳣)
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_mount_for_windows(N9M_FS_UCHAR hdd_id, N9M_FS_INT part_num, N9M_FS_CHAR *p_part_name[N9M_FS_MAX_PARTITION_NUM]);

/*********************************************************************  
    Description: 
        ж�������ļ�ϵͳӲ��
    Input:  
        hdd_id------Ӳ��ID
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_umount(N9M_FS_UCHAR hdd_id);

/*********************************************************************  
    Description: 
        ��ȡӲ����Ϣ
    Input:  
        hdd_id------Ӳ��ID
    output:
        p_hdd_info------Ӳ����Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_hdd_info(N9M_FS_UCHAR hdd_id, rmfs_n9m_hdd_info_t *p_hdd_info);

/*********************************************************************  
    Description: 
        ���Ӳ�̵�ָ��������
    Input:  
        hdd_id------Ӳ��ID
        group_id------��ID����Ӧ�ò�ȷ����ȡֵ0-32������ͨ��api_rmfs_read_device_info�õ��豸��Ϣ���豸��Ϣһ���ģ�֤��Ӳ��������ͬһ���豸��
        ����ӵ�ͬһ���飬ͨ���齫���Ӳ�̺ϲ���һ���洢�豸��������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_add_disk_to_group(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR group_id);

/*********************************************************************  
    Description: 
        ��ȡָ���������Ӳ����Ŀ
    Input:  
        group_id------��ID
    output:
        ��
    Return: 
        ����:ʧ��
        ����:ָ�����Ӳ����Ŀ
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_disk_num_from_group(N9M_FS_UCHAR group_id);

/*********************************************************************  
    Description: 
        ��ȡָ���������Ӳ�̳�Ա��
    Input:  
        group_id------��ID
        p_disk_list------���̳�Ա�б���
        list_size------�б����С
    output:
        p_disk_list------Ӳ�̳�Ա�б�
    Return: 
        ����:ʧ��
        ����:ָ������ʵ�ʴ��ڵ�Ӳ����
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_disk_list_from_group(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_disk_list, N9M_FS_INT list_size);

/*********************************************************************  
    Description: 
        ��ָ���������Ƴ�Ӳ��
    Input:  
        hdd_id------Ӳ��ID
        group_id------��ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_disk_from_group(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR group_id);

/*********************************************************************  
    Description: 
        ����һ�����Ρ�stream_type��ֵ���ϲ㶨�岢����
    Input:  
        p_rcsp------�������β���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_create_stream_segment(rmfs_n9m_create_ss_para_t *p_rcsp, rmfs_n9m_stream_device_info_t *p_devinfo = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ͨ������ID������
    Input:  
        pStream_segment_id------����ID��ͨ���ϲ㲻����������ݣ�������ʱ�ļ�ϵͳ����
        record_type_bitmap------¼������λͼ
        auto_jump------�Ƿ��ڶ�ȡ����ʱ���Զ���ת����һ���Ρ�FS_TRUE,�Զ���ת��FS_FALSE�����Զ���ת
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_open_stream_segment_by_id(n9m_stream_segment_id_t *pStream_segment_id, N9M_FS_USHORT record_type_bitmap, N9M_FS_BOOL auto_jump);

/*********************************************************************  
    Description: 
        ͨ������ID������
    Input:  
        pStream_segment_id------����ID��ͨ���ϲ㲻����������ݣ�������ʱ�ļ�ϵͳ����
        expect_len------������ȡ���ȡ������ֵ�������γ��ȣ���ʾ�öο������ڱ�������֣���������Ҫ����������
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_special_open_stream_segment(n9m_stream_segment_id_t *pStream_segment_id, N9M_FS_ULL expect_len);

/*********************************************************************  
    Description: 
        ͨ������ֱ�Ӵ򿪷�������������
    Input:  
        open_para------�򿪲��������е��������ͣ���group_bitmap��Ϊ0ʱ����bitmap������group_bitmapΪ0ʱ������ֵ��
        auto_jump------�Ƿ��ڶ�ȡ����ʱ���Զ���ת����һ���Ρ�FS_TRUE,�Զ���ת��FS_FALSE�����Զ���ת
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_open_stream_segment_by_stream_bitmap_para(rmfs_n9m_stream_open_para_t *p_open_para, N9M_FS_UCHAR auto_jump);
    
/*********************************************************************  
    Description: 
        ͨ������ֱ�Ӵ򿪷�������������
    Input:  
        open_para------�򿪲���
        auto_jump------�Ƿ��ڶ�ȡ����ʱ���Զ���ת����һ���Ρ�FS_TRUE,�Զ���ת��FS_FALSE�����Զ���ת
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_open_stream_segment_by_para(rmfs_n9m_stream_open_para_t *p_open_para, N9M_FS_UCHAR auto_jump);

/*********************************************************************  
    Description: 
        ͨ��ʱ�䶨λ�����εĶ�дλ�á�¼��������(������)дʱ��֧�ָýӿ�
    Input:  
        ssfd------��������ID
        p_date_time------��λʱ��
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_seek_stream_segment_by_time(N9M_FS_INT ssfd, n9m_fs_date_time_t *p_date_time);

/*********************************************************************  
    Description: 
        ͨ��ƫ������λ�����εĶ�дλ�á�¼��������(������)дʱ��֧�ָýӿ�
    Input:  
        ssfd------��������ID
        offset------ƫ����
        whence------������ʵλ�á�ȡֵΪSEEK_SET, SEEK_CUR, SEEK_END
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_seek_stream_segment_by_offset(N9M_FS_INT ssfd, N9M_FS_LL offset, N9M_FS_INT whence);

/*********************************************************************  
    Description: 
        ��ȡ��ǰ��дָ�������������ʼλ�õ�ƫ����
    Input:  
        ssfd------��������ID
    output:
        p_offset------��ǰ��дƫ����
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_stream_segment_tell(N9M_FS_INT ssfd, N9M_FS_LL *p_offset);

/*********************************************************************  
    Description: 
        �رմ򿪵�����
    Input:  
        ssfd------��������ID
        p_stream_info---������Ϣ
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_close_stream_segment(N9M_FS_INT ssfd, n9m_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        д������
    Input:  
        ssfd------��������ID
        p_buffer------���ݻ�����
        len------д�����ݳ���
        frame_num------д�뻺������֡������ֻ��¼I֡����С����ʱ����ֵ��0
        p_vdi------֡��Ϣ��С����ʱ����ֵ��FS_NULL
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_video_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_INT frame_num, n9m_video_frame_info_t *p_vdi);

/*********************************************************************  
    Description: 
        ��ָ�����ε����ݴ��ں˻���ͬ����Ӳ��
    Input:  
        ssfd------��������ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_fsync(N9M_FS_INT ssfd);

/*********************************************************************  
    Description: 
        ��ȡ����
    Input:  
        ssfd------��������ID
        p_buffer------���ݻ�����
        len------������ȡ���ݳ���
    output:
        pNew_stream_segment------�����ʱ���Զ���ת����ô��ֵ��ʾ�Ƿ�������һ���µ����Ρ�����Ҫ��ֵʱ���������FS_NULL
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_video_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        ��ȡ��ǰλ������n��I֡
    Input:  
        ssfd------��������ID
        jump_iframe_num------������I֡��Ŀ
    output:
        p_frame_buffer------I֡���ݵ�ַ
        p_frame_len------I֡���ݳ���
        pNew_stream_segment------�����ʱ���Զ���ת����ô��ֵ��ʾ�Ƿ�������һ���µ����Ρ�����Ҫ��ֵʱ���������FS_NULL
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_next_iframe(N9M_FS_INT ssfd, N9M_FS_UCHAR jump_iframe_num, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        ��ȡ��ǰλ����ǰ��n��I֡
    Input:  
        ssfd------��������ID
        jump_iframe_num------������I֡��Ŀ
    output:
        p_frame_buffer------I֡���ݵ�ַ
        p_frame_len------I֡���ݳ���
        pNew_stream_segment------�����ʱ���Զ���ת����ô��ֵ��ʾ�Ƿ�������һ���µ����Ρ�����Ҫ��ֵʱ���������FS_NULL
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_pre_iframe(N9M_FS_INT ssfd, N9M_FS_UCHAR jump_iframe_num, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        ��ȡ��ѯ���
    Input:  
        p_query_para------��ѯ������ע��:��������е�sequence_cycleΪ0ʱ����ģʽ�£�û�ж����ݽ���ͳ�Ʒ�����
        ��Ϊ�˿�����������������ܽ�����ǰ��ҳ��Ҳ�޷�����ָ��ҳ��
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��ѯ������
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_query_stream_segment_handle(n9m_stream_query_t *p_query_para, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ȡ��ѯ���
    Input:  
        query_handle------��ѯ������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_close_query_stream_segment_handle(N9M_FS_INT query_handle);

/*********************************************************************  
    Description: 
        ��ҳ��ѯ
    Input:  
        query_handle------��ѯ������
        query_cmd------��ҳָ��
    output:
        p_get_num------�������
        p_query_result------�������
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_query_stream_segment(N9M_FS_INT query_handle, n9m_stream_query_cmd_t query_cmd, N9M_FS_INT *p_get_num, n9m_stream_query_result_t *p_query_result);

/*********************************************************************  
    Description: 
        ��ȡ������������ҳ��
    Input:  
        query_handle------��ѯ������
    output:
        ��
    Return: 
        -1:ʧ��
        ����:������������ҳ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_total_page_num(N9M_FS_INT query_handle);

/*********************************************************************  
    Description: 
        ��ת��ָ������ҳ
    Input:  
        query_handle------��ѯ������
        page_num------ָ��ҳ��
    output:
        p_get_num------�������
        p_query_result------�������
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_jump_specific_page(N9M_FS_INT handle, N9M_FS_INT page_num, N9M_FS_INT *pGet_num, n9m_stream_query_result_t *pStream_segment_list);

/*********************************************************************  
    Description: 
        ��ȡָ��������������
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ��������������
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_num(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ȡָ�������͵������б�.
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
        p_date_list------���������������������б���
        list_size------�б����С
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ����������ʵ������
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_list(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, n9m_fs_date_t *p_date_list, N9M_FS_INT list_size, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ȡָ��������������
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
        chn_bitmap------����ͨ����ʹ��bitλ��ʾ��
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ��������������
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_info_num(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ȡָ�������͵������б�.
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
        chn_bitmap------����ͨ����ʹ��bitλ��ʾ��
        p_record_list------���������������������б���
        list_size------�б����С
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ����������ʵ������
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_date_info(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, n9m_fs_record_date_info_t *p_record_list, N9M_FS_INT list_size, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ȡ������
    Input:  
        p_query_para------�������ѯ����
    output:
        record_bitmap------��������ֵ�����p_query_para�ṹ�µ�record_bitmap��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_query_calendar(n9m_calendar_stream_query_t *p_query_para, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ͨ������ID�����ν��м���
    Input:  
        p_stream_segment_id------����ID
        lock------������ʶ��0-������1-����
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_stream_segment_lock_by_id(n9m_stream_segment_id_t *p_stream_segment_id, N9M_FS_UCHAR lock);

/*********************************************************************  
    Description: 
        ͨ��ʱ����������ݼ���
    Input:  
        p_stream_segment_id------����ID
        lock------������ʶ��0-������1-����
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_stream_segment_lock_by_time(rmfs_n9m_stream_lock_para_t  *p_lock_para, N9M_FS_UCHAR lock);

/*********************************************************************  
    Description: 
        �Զ�����ָ������������
    Input:  
        p_cur_date_time------��ǰʱ��
        reserve_days------��������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_auto_unlock(n9m_fs_date_time_t *p_cur_date_time, N9M_FS_INT reserve_days);

/*********************************************************************  
    Description: 
        ���ҵ�ǰ����д���ݵĹ������̡�д����ǰ���ȵ��øýӿڣ��鿴�Ƿ��п��Թ����Ĵ���
    Input:  
        group_id------��ID
    output:
        p_cur_disk_id---��ǰ��������ID
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_find_work_hdd(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_cur_disk_id);

/*********************************************************************  
    Description: 
        ���ø��ǲ���������ϲ㲻���øýӿڽ������ã���ô�ļ�ϵͳ����Ĭ��ֵ���д���
    Input:  
        group_id------��ID
        p_rhoc------���ǲ���
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_config_overwrite(N9M_FS_UCHAR group_id, rmfs_n9m_hdd_overwrite_config_t *p_rhoc);

/*********************************************************************  
    Description: 
        Ӳ�̸��ǡ������ļ�ϵͳ���ڣ��������̡߳�������Ҫ�ϲ���øýӿڽ��и��ǲ�����
    Input:  
        group_id------��ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_overwrite_big_stream(N9M_FS_INT GroupId);

/*********************************************************************  
    Description: 
        Ӳ�̸��ǡ������ļ�ϵͳ���ڣ��������̡߳�������Ҫ�ϲ���øýӿڽ��и��ǲ�����
    Input:  
        group_id------��ID
        check_video_exist------���С�������Ӧ��¼���Ƿ���ڣ�true��ʾ���������¼���򲻸��ǣ�false��ʾ������û��¼�񶼸���
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_overwrite_small_stream(N9M_FS_INT GroupId, N9M_FS_UINT reserve_days, N9M_FS_BOOL check_video_exist);

/*********************************************************************  
    Description: 
        ͨ�����δ򿪾����ȡ��Ӧ������ID
    Input:  
        ssfd------��������ID
    output:
        p_ssid------����ID
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_fd_info(N9M_FS_INT ssfd, n9m_stream_segment_id_t *p_ssid);

/*********************************************************************  
    Description: 
        ͨ������ID��ȡ��Ӧ��������Ϣ��
    Input:  
        p_ssid------����ID
    output:
        p_stream_info------������Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_info(n9m_stream_segment_id_t *p_ssid, n9m_stream_segment_info_t *p_stream_info);

/*********************************************************************  
    Description: 
        ͨ������ID��ȡָ��ʱ��ε�������Ϣ
    Input:  
        p_ssid------����ID
        start_time------��ʼʱ��
        end_time------����ʱ��
    output:
        p_offset------ָ����ʼʱ��������������ڵ�ƫ����
        p_data_len------ָ��ʱ����ڵ����ݳ���
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, N9M_FS_ULL *p_data_len);

/*********************************************************************  
    Description: 
        ͨ������ID��ȡָ��ʱ��ε�������Ϣ
    Input:  
        p_ssid------����ID
        start_time------��ʼʱ��
        end_time------����ʱ��
        out_search------�Ƿ������κ����������ܱ��������β�֣�����������Ҫ�ϴ���������������
    output:
        p_offset------ָ����ʼʱ��������������ڵ�ƫ����
        p_data_len------ָ��ʱ����ڵ����ݳ���
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_special_get_stream_segment_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, N9M_FS_ULL *p_data_len, N9M_FS_BOOL out_search);

/*********************************************************************  
    Description: 
        ����ͨ�ļ�
    Input:  
        group_id------������ID
        p_file_name------�ļ�����,���14���ֽڣ�������������
        open_mode------��ģʽ��0������ļ������ڣ������ļ��󷵻��ļ�������������ļ����ڣ�����ļ����ݺ󷵻أ�
                                 1������ļ������ڣ������ļ��󷵻��ļ�������������ļ����ڣ����ļ�β׷��д�룬Ҳ���Ǵ򿪺󽫶�дָ�������ļ�β��
                                 2������ļ������ڣ�ֱ�ӷ���ʧ�ܣ�������򿪣�������дָ�������ļ���ʼ��
                                 3, ��ֻ����ʽ�򿪣�����ļ�������ֱ�ӷ��ش���
    output:
        ��
    Return: 
        INVALID_RMFS_HANDLE:ʧ��
        ����:��ͨ�ļ���������
 ********************************************************************/
N9M_DLL_API RMFS_HANDLE api_rmfs_open_normal_file(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name, N9M_FS_INT open_mode);

/*********************************************************************  
    Description: 
        ����ͨ�ļ���д������
    Input:  
        file_handle------��ͨ�ļ�������
        p_buffer------���ݻ�����
        buffer_len------д�����ݳ���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д�����ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_normal_file(RMFS_HANDLE file_handle, N9M_FS_CHAR *p_buffer, N9M_FS_INT buffer_len);

/*********************************************************************  
    Description: 
        ��д�����ͨ�ļ�����ǿ��ˢ��Ӳ��
    Input:  
        file_handle------��ͨ�ļ�������
    output:
        ��
    Return: 
        0:�ɹ�
        -1:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_sync_normal_file(RMFS_HANDLE file_handle);

/*********************************************************************  
    Description: 
        ����ͨ�ļ��ڶ�ȡ����
    Input:  
        file_handle------��ͨ�ļ�������
        p_buffer------���ݻ�����
        buffer_len------������ȡ���ݳ���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ���ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_normal_file(RMFS_HANDLE file_handle, N9M_FS_CHAR *p_buffer, N9M_FS_INT buffer_len);

/*********************************************************************  
    Description: 
        ��ȡ��ǰ��дλ��
    Input:  
        file_handle------��ͨ�ļ�������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_normal_file_cur_offset(RMFS_HANDLE file_handle, N9M_FS_LL &offset);

/*********************************************************************  
    Description: 
        ͨ��ƫ������λ��ͨ�ļ���дλ��
    Input:  
        file_handle------��ͨ�ļ�������
        offset------��λƫ����
        whence------��λ��ʼλ�á�SEEK_SET-�ļ���ʼ��SEEK_CUR-��ǰλ�ã�SEEK_END-�ļ�β
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_seek_normal_file(RMFS_HANDLE file_handle, N9M_FS_LL offset, N9M_FS_INT whence);

/*********************************************************************  
    Description: 
        �ر���ͨ�ļ���
    Input:  
        file_handle------��ͨ�ļ�������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_close_normal_file(RMFS_HANDLE file_handle);

/*********************************************************************  
    Description: 
        ��ȡ��ͨ�ļ���С
    Input:  
        file_handle------��ͨ�ļ�������
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��ͨ�ļ��Ĵ�С�����ֽ�Ϊ��λ
 ********************************************************************/
N9M_DLL_API N9M_FS_LL api_rmfs_get_normal_file_size_by_handle(RMFS_HANDLE file_handle);

/*********************************************************************  
    Description: 
        ��ȡ��ͨ�ļ���С
    Input:  
        group_id------������ID
        p_file_name------�ļ�����
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��ͨ�ļ��Ĵ�С�����ֽ�Ϊ��λ
 ********************************************************************/
N9M_DLL_API N9M_FS_LL api_rmfs_get_normal_file_size(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        ɾ����ͨ�ļ�
    Input:  
        group_id------������ID
        p_file_name------�ļ�����
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_normal_file(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        ��ȡ��ѯ���
    Input:  
        group_id------������ID
        p_file_name------�ļ����ơ�������ȫ���ļ�����Ҳ�����ǲ����ļ���
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API RMFS_HANDLE api_rmfs_get_search_normal_file_handle(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        ��ȡ��ѯ�ļ���
    Input:  
        search_handle------�������
        opt_mark------������ǡ�0-��һ���ļ���1-��һ���ļ���2-��һ���ļ���3-���һ���ļ���
    output:
        p_file_name------�ļ������洢�ռ�Ҫ����14���ֽ�
    Return: 
        -1:ʧ��
        0:�������λ��
        1:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_normal_file_name(RMFS_HANDLE search_handle, N9M_FS_UCHAR opt_mark, N9M_FS_CHAR *p_file_name);

/*********************************************************************  
    Description: 
        �ͷŲ�ѯ���
    Input:  
        search_handle------�������
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_release_search_normal_file_handle(RMFS_HANDLE search_handle);

/*********************************************************************  
    Description: 
        ��Ԥ¼���θ�Ϊ����򱨾�����
    Input:  
        ssfd------��������ID
        record_type------¼������
        alarm_type------��������
        lock------�Ƿ����
        lock_type------�������͡�
        start_time------��ʼʱ�䡣��������ε���ʼʱ���ڸ�ʱ��֮ǰ����ô���øýӿں�֮ǰ��Ԥ¼����ɾ��
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_pre_record_info(N9M_FS_INT ssfd, N9M_FS_UCHAR record_type, N9M_FS_ULL alarm_type, N9M_FS_UCHAR lock, N9M_FS_UINT lock_type, n9m_fs_time_t start_time, n9m_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ����Ԥ¼����
    Input:  
        ssfd------��������ID
        end_time------ɾ����ֹʱ��
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_overwrite_pre_record_stream(N9M_FS_INT ssfd, n9m_fs_time_t end_time);

/*********************************************************************  
    Description: 
        �޸�ָ�����Ľ���ʱ�䡣���øýӿں�ָ������end_time֮������ݻ�ȫ����ɾ����
        �ýӿڲ��ܲ�������д�����Σ���Ҫ�رպ����޸ġ�
    Input:  
        ssid------����ID
        end_time------���ν���ʱ��
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_stream_segment_end_time(n9m_stream_segment_id_t ssid, n9m_fs_time_t end_time);

/*********************************************************************  
    Description: 
        �޸�����¼�����ͺͼ���״̬
    Input:  
        p_modify_para------�޸Ĳ���
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_stream_segment_info(rmfs_n9m_modify_segment_para_t *p_modify_para);

/*********************************************************************  
    Description: 
        ���ݴ��������޸�������Ϣ
    Input:  
        ssfd------����������
        modify_mask------bit0-�޸ļ���״̬��bit1-�޸�¼������
        lock------�Ƿ����
        lock_type------��������
        record_type------¼������
        alarm_type------��������
        p_start_time------��ʼ�޸�ʱ��,���ΪN9M_FS_NULLʱ���޸���������
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_modify_stream_segment_info_by_fd(N9M_FS_INT ssfd, N9M_FS_UCHAR modify_mask, N9M_FS_UCHAR lock, N9M_FS_UINT lock_type, N9M_FS_UCHAR record_type, N9M_FS_ULL alarm_type, n9m_fs_time_t *p_start_time, n9m_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ָ��Ӳ����д���豸��Ϣ������Ϣ�ṹ���ϲ㶨��
    Input:  
        hdd_id------Ӳ��ID
        p_dev_info------�豸��Ϣ����
        dev_info_len------�豸��Ϣ����
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_device_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_info, N9M_FS_INT dev_info_len);

/*********************************************************************  
    Description: 
        �������Ѽ��ص�Ӳ����д���豸��Ϣ
    Input:
        p_dev_info------�豸��Ϣ����
        dev_info_len------�豸��Ϣ����
    output:
        ��
    Return: 
        -1:ʧ��
        0:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_write_device_info_to_all_disk(N9M_FS_CHAR *p_dev_info, N9M_FS_INT dev_info_len);

/*********************************************************************  
    Description: 
        ��ȡָ��Ӳ���е��豸��Ϣ���ݳ���
    Input:  
        hdd_id------Ӳ��ID
    output:
        ��
    Return: 
        -1:ʧ��
        ����:�豸��Ϣ���ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_device_info_len(N9M_FS_UCHAR hdd_id);

/*********************************************************************  
    Description: 
        ��ȡָ��Ӳ���е��豸��Ϣ
    Input:  
        hdd_id------Ӳ��ID
        p_read_buffer------��ȡ�豸��Ϣ����
        buffer_len------�豸��Ϣ���峤��
    output:
        ��
    Return: 
        -1:ʧ��
        ����:�豸��Ϣ���ݳ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_read_device_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_read_buffer, N9M_FS_INT buffer_len);

/*********************************************************************  
    Description: 
        ����Ӳ�̽ӿ�
    Input:  
        hdd_id------Ӳ��ID
        data_size------�������ݳ���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:�ɹ�
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_test_hdd(N9M_FS_UCHAR hdd_id, N9M_FS_UINT data_size);

/*********************************************************************  
    Description: 
        ���ڻָ�ָ���������ڵ��𻵵�¼������
    Input:  
        hdd_id------Ӳ��ID
        p_dev_name------Ӳ���豸�ļ���
        p_recovery_para------�ָ�����
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_recovery(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, rmfs_n9m_recovery_para_t *p_recovery_para);

/*********************************************************************  
    Description: 
        �Զ�ɾ������¼�񣬽������������ڱ仯ʱ����
    Input:  
        p_cur_date_time------��ǰʱ��
        reserve_days------��������
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_auto_delete(n9m_fs_date_time_t *p_cur_date_time, N9M_FS_INT reserve_days, N9M_FS_UINT group_bitmap);

/*********************************************************************  
    Description: 
        ���ݲ���ɾ������
    Input:  
        p_delete_para------ɾ������
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_stream_segment_by_para(rmfs_n9m_delete_para_t *p_delete_para);

/*********************************************************************  
    Description: 
        ��������IDɾ������
    Input:  
        pStream_segment_id------����ID
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_delete_stream_segment(n9m_stream_segment_id_t *pStream_segment_id);

/*********************************************************************  
    Description: 
       ��ȡ��ͨ�ļ������Ĵ�����
    Input:  
        ��
    output: 
        ��
    Return: 
        ������:-1-Ŀ��������ЧӲ�̣�-2-�����Ƿ���-3-�����û����ڲ�����-4-�ļ��쳣
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_last_error();

/*********************************************************************  
    Description: 
        ��ȡ˫��������������
    Input:  
        p_query_para------�������ѯ����
    output:
        record_bitmap------��������ֵ�����p_query_para�ṹ�µ�record_bitmap��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_query_calendar_more(n9m_calendar_stream_query_t *p_query_para, rmfs_n9m_stream_query_device_info_t *p_dev_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ����������¼�񸲸ǲ���������ϲ㲻���øýӿڽ������ã���ô�ļ�ϵͳĬ�Ϲرոù���
    Input:  
        group_id------��ID
        p_rhoc------���ǲ���
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_config_overwrite_mainstream(N9M_FS_UCHAR group_id, rmfs_n9m_mainstream_overwrite_config_t *p_rhoc);

/*********************************************************************  
    Description: 
       ������¼�񸲸ǽӿڡ������ļ�ϵͳ���ڣ��������̡߳�������Ҫ�ϲ���øýӿڽ��и��ǲ�����
    Input:  
        group_id------��ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_disk_overwrite_mainstream(N9M_FS_INT GroupId);

/*********************************************************************  
    Description: 
        ��ȡ������Ϣ�б�
    Input:  
        group_bitmap------������λͼ
        stream_type_bitmap------������������,��bit����
        mask----------������������bit0:���ƺ� bit1:��˾����
        p_info_list------�����������������γ�����Ϣ�б�
        list_size------�б����С
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ����������ʵ�ʸ���
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_device_info_list(N9M_FS_UINT group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_UINT mask, rmfs_n9m_stream_device_info_t *p_info_list, N9M_FS_INT list_size);

/*********************************************************************  
    Description: 
        ����д�����Ƿ��Զ�fsync
    Input:  
        hdd_id------Ӳ��ID,Ҳ����Ӳ�̵��Ա�ţ���Ӧ�ò������������Ҫ��֤��ͬ�Ĵ���ID��Ҫ��һ����ȡֵ��Χ0-32
        is_sync-----�Զ�fsyncʹ��
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_set_auto_fsync(N9M_FS_UCHAR hdd_id, N9M_FS_BOOL is_sync);

/*********************************************************************  
    Description: 
        ͨ������ID��ȡָ��ʱ��ε�I֡������Ϣ
    Input:  
        p_ssid------����ID
        start_time------��ʼʱ��
        end_time------����ʱ��
    output:
        p_offset------ָ����ʼʱ��������������ڵ�ƫ����
        p_stream_info------����I֡��Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_iframe_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, n9m_stream_segment_info_t *p_stream_info);

/*********************************************************************  
    Description: 
        ͨ������ID��ȡָ��ʱ��ε�I֡������Ϣ
    Input:  
        p_ssid------����ID
        start_time------��ʼʱ��
        end_time------����ʱ��
        search_len------�Ƿ������κ����������ܱ��������β�֣�����������Ҫ�ϴ���������������
    output:
        p_offset------ָ����ʼʱ��������������ڵ�ƫ����
        p_stream_info------����I֡��Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_special_get_stream_segment_iframe_data_info(n9m_stream_segment_id_t *p_ssid, n9m_fs_time_t *p_start_time, n9m_fs_time_t *p_end_time, N9M_FS_ULL *p_offset, n9m_stream_segment_info_t *p_stream_info, N9M_FS_ULL search_len);

/*********************************************************************  
    Description: 
        ͨ������ID��ȡ������Ϣ�б�
    Input:  
        p_ssid------����ID
    output:
        p_device_info------���γ�����Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_get_stream_segment_device_info(n9m_stream_segment_id_t *p_ssid, rmfs_n9m_stream_device_info_t *p_device_info);

/*********************************************************************  
    Description: 
        windows�����������ļ�ϵͳ�Ƿ��д
    Input:  
        hdd_id------Ӳ��ID
        write_enable------��д״̬��0-����д��1-��д
    output: 
        ��
    Return: 
        ������:0-�ɹ���-1-ʧ��
 ********************************************************************/
N9M_DLL_API N9M_FS_INT api_rmfs_set_rmfs_write_attr_for_windows(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR write_enable);

#endif

