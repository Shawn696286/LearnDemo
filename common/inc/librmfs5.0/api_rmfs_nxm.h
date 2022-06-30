#ifndef _API_RMFS_H_
#define _API_RMFS_H_
#include "rmfs_nxm_struct.h"

#ifdef WIN32
#define NXM_DLL_API _declspec(dllexport)
#else
#define NXM_DLL_API
#endif

/*********************************************************************  
    Description: 
        ��ʼ�������ļ�ϵͳ��ʹ�������ļ�ϵͳ�������ȳ�ʼ��
    Input: 
    output: 
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_init();

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_uinit();

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_set_debug_level(N9M_FS_ULONG debug_level);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_rebuild_rely(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);


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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_format(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, N9M_FS_CHAR *p_serial_num);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_fast_format(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_mount(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_mount_for_windows(N9M_FS_UCHAR hdd_id, N9M_FS_INT part_num, N9M_FS_CHAR *p_part_name[N9M_FS_MAX_PARTITION_NUM]);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_umount(N9M_FS_UCHAR hdd_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_hdd_info(N9M_FS_UCHAR hdd_id, rmfs_nxm_hdd_info_t *p_hdd_info);

/*********************************************************************  
    Description: 
        ��ȡ��ǰӲ��fuse������Ϣ
    Input:  
        group_id------������ID
    output:
        p_fuse_info------fuse������Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_fuse_info(N9M_FS_UCHAR group_id, N9M_FS_CHAR *p_serial_num, rmfs_nxm_fuse_info_t *p_fuse_info);

/*********************************************************************  
    Description: 
        ���Ӳ�̵�ָ��������
    Input:  
        hdd_id------Ӳ��ID
        group_id------��ID����Ӧ�ò�ȷ����ȡֵ0-32������ͨ��api_rmfs_nxm_read_device_info�õ��豸��Ϣ���豸��Ϣһ���ģ�֤��Ӳ��������ͬһ���豸��
        ����ӵ�ͬһ���飬ͨ���齫���Ӳ�̺ϲ���һ���洢�豸��������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_add_disk_to_group(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR group_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_disk_num_from_group(N9M_FS_UCHAR group_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_disk_list_from_group(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_disk_list, N9M_FS_INT list_size);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_delete_disk_from_group(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR group_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_create_stream_segment(rmfs_nxm_create_ss_para_t *p_rcsp);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_open_stream_segment_by_id(rmfs_nxm_stream_segment_id_t *pStream_segment_id, N9M_FS_USHORT record_type_bitmap, N9M_FS_BOOL auto_jump);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_special_open_stream_segment(rmfs_nxm_stream_segment_id_t *pStream_segment_id, N9M_FS_ULL expect_len);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_open_stream_segment_by_para(rmfs_nxm_stream_open_para_t *p_open_para, N9M_FS_UCHAR auto_jump);

/*********************************************************************  
    Description: 
        ͨ��ʱ�䶨λ�����εĶ�дλ�á�дʱ��֧�ָýӿ�
    Input:  
        ssfd------��������ID
        p_date_time------��λʱ��
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_seek_stream_segment_by_time(N9M_FS_INT ssfd, rmfs_nxm_date_time_t *p_date_time);

/*********************************************************************  
    Description: 
        ͨ��ƫ������λ�����εĶ�дλ�á�дʱ��֧�ָýӿ�
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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_seek_stream_segment_by_offset(N9M_FS_INT ssfd, N9M_FS_LL offset, N9M_FS_INT whence);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_stream_segment_tell(N9M_FS_INT ssfd, N9M_FS_LL *p_offset);

/*********************************************************************  
    Description: 
        �رմ򿪵�����
    Input:  
        ssfd------��������ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_close_stream_segment(N9M_FS_INT ssfd, rmfs_nxm_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        д�������ݣ�һ֡���ݱ�ʾ��������I֮֡������ݣ���һ��д��֡
    Input:  
        ssfd------��������ID
        p_buffer------���ݻ�����
        len------д�����ݳ���
        frame_num------д�뻺������֡������ֻ��¼I֡����
        p_frame_info------֡��Ϣ��
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_write_stream_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_INT frame_num, rmfs_nxm_write_one_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        д��������, д����������I֮֡������ݣ�����ɷֿ���һ��ֻдһ֡
    Input:  
        ssfd------��������ID
        p_buffer------���ݻ���������
        count------���ݻ������������
        p_frame_info------I֡��Ϣ��
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_write_stream_data(N9M_FS_INT ssfd, rmfs_nxm_buffer_array_t *p_buffer, N9M_FS_INT count, rmfs_nxm_write_one_frame_info_t *p_frame_info);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_fsync(N9M_FS_INT ssfd);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_stream_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_BOOL *pNew_stream_segment);

/*********************************************************************  
    Description: 
        ��ȡһ������
    Input:  
        ssfd------��������ID
    output:        
        p_frame_buffer------�����ݵ�ַ
        p_frame_len------��ȡ���ݳ���
        p_frame_info------��ȡ֡��Ϣ
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_stream_data(N9M_FS_INT ssfd, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, rmfs_nxm_read_one_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        ��ȡ��һ������
    Input:  
        ssfd------��������ID
    output:        
        p_frame_buffer------�����ݵ�ַ
        p_frame_len------��ȡ���ݳ���
        p_frame_info------��ȡ֡��Ϣ
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_pre_second(N9M_FS_INT ssfd, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, rmfs_nxm_read_one_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        ��ȡ��ǰλ������n��I֡
    Input:  
        ssfd------��������ID
        jump_iframe_num------������I֡��Ŀ
    output:
        p_frame_buffer------I֡���ݵ�ַ
        p_frame_len------I֡���ݳ���
        p_frame_info------��ȡ֡��Ϣ
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_next_iframe(N9M_FS_INT ssfd, N9M_FS_UCHAR jump_iframe_num, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, rmfs_nxm_read_one_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        ��ȡ��ǰλ����ǰ��n��I֡
    Input:  
        ssfd------��������ID
        jump_iframe_num------������I֡��Ŀ
    output:
        p_frame_buffer------I֡���ݵ�ַ
        p_frame_len------I֡���ݳ���
        p_frame_info------��ȡ֡��Ϣ
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_pre_iframe(N9M_FS_INT ssfd, N9M_FS_UCHAR jump_iframe_num, N9M_FS_UCHAR **p_frame_buffer, N9M_FS_INT *p_frame_len, rmfs_nxm_read_one_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        ͨ������ID����־����
    Input:  
        pStream_segment_id------����ID��ͨ���ϲ㲻����������ݣ�������ʱ�ļ�ϵͳ����
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_open_log_stream(rmfs_nxm_stream_segment_id_t *pStream_segment_id);

/*********************************************************************  
    Description: 
        ͨ������ֱ�Ӵ򿪷�����������־����
    Input:  
        open_para------�򿪲���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��������ID
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_open_log_stream_by_para(rmfs_nxm_stream_open_para_t *p_open_para);

/*********************************************************************  
    Description: 
        д����־����
    Input:  
        ssfd------��������ID
        p_buffer------���ݻ�����
        len------д�����ݳ���
        frame_num------д�뻺������֡������ֻ��¼I֡����
        p_frame_info------֡��Ϣ��
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_write_log_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_INT frame_num, rmfs_nxm_write_log_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        �޸���־���� (Ŀǰֻ�б�����־֧���޸�)
    Input:  
        group_bitmap------������λͼ
        uuid------��־����Ψһ��ʶ
        p_buffer------���ݻ�����
        len------д�����ݳ���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_log_data(N9M_FS_ULONG group_bitmap, N9M_FS_ULONG uuid, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len);

/*********************************************************************  
    Description: 
        ������־id�޸���־���� (Ŀǰֻ�б�����־֧���޸�)
    Input:  
        pLog_id------��־ID (д��һ����־ʱ���ص�id)
        p_buffer------���ݻ�����
        len------д�����ݳ���
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_log_data_by_id(rmfs_nxm_stream_segment_id_t *pLog_id, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len);

/*********************************************************************  
    Description: 
        ͨ��ƫ������λ����־���εĶ�дλ�á�
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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_seek_log_by_offset(N9M_FS_INT ssfd, N9M_FS_LL offset, N9M_FS_INT whence);

/*********************************************************************  
    Description: 
        ͨ��ʱ�䶨λ����־���εĶ�дλ�á�
    Input:  
        ssfd------��������ID
        p_date_time------��λʱ��
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_seek_log_by_time(N9M_FS_INT ssfd, rmfs_nxm_date_time_t *p_date_time);

/*********************************************************************  
    Description: 
        ��ȡ��־����
    Input:  
        ssfd------��������ID
        p_buffer------���ݻ�����
        len------������ȡ���ݳ���
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_log_data(N9M_FS_INT ssfd, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len);

/*********************************************************************  
    Description: 
        �رմ򿪵���־����
    Input:  
        ssfd------��������ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_close_log_stream(N9M_FS_INT ssfd);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_query_stream_segment_handle(rmfs_nxm_stream_query_t *p_query_para);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_close_query_stream_segment_handle(N9M_FS_INT query_handle);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_query_stream_segment(N9M_FS_INT query_handle, rmfs_nxm_stream_query_cmd_t query_cmd, N9M_FS_INT *p_get_num, rmfs_nxm_stream_query_result_t *p_query_result);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_total_page_num(N9M_FS_INT query_handle);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_jump_specific_page(N9M_FS_INT handle, N9M_FS_INT page_num, N9M_FS_INT *pGet_num, rmfs_nxm_stream_query_result_t *pStream_segment_list);

/*********************************************************************  
    Description: 
        ��ȡָ��������������
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
        p_name_info------ƥ���ַ���
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ��������������
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_date_num(N9M_FS_ULONG group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_CHAR *p_name_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        ��ȡָ�������͵������б�.
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
        p_date_list------���������������������б���
        list_size------�б����С
        p_name_info------ƥ���ַ���
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ����������ʵ������
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_date_list(N9M_FS_ULONG group_bitmap, N9M_FS_ULL stream_type_bitmap, rmfs_nxm_date_t *p_date_list, N9M_FS_INT list_size, N9M_FS_CHAR *p_name_info = N9M_FS_NULL);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_date_info_num(N9M_FS_ULONG group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, N9M_FS_CHAR *p_name_info = N9M_FS_NULL);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_date_info(N9M_FS_ULONG group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, rmfs_nxm_record_date_info_t *p_record_list, N9M_FS_INT list_size, N9M_FS_CHAR *p_name_info = N9M_FS_NULL);

/*********************************************************************  
    Description: 
        �ж��Ƿ���ָ��������¼������.
    Input:  
        group_bitmap------������λͼ
        stream_type------������������
        chn_bitmap------����ͨ����ʹ��bitλ��ʾ��
        record_type_bitmap------���������������������б���
    output:
        ��
    Return: 
        0:�ɹ�
        ����:����������������
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_check_stream_record_type(N9M_FS_ULONG group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_ULL chn_bitmap, N9M_FS_USHORT record_type_bitmap);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_query_calendar(rmfs_nxm_calendar_stream_query_t *p_query_para);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_query_calendar_more(rmfs_nxm_calendar_stream_query_t *p_query_para);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_stream_segment_lock_by_id(rmfs_nxm_stream_segment_id_t *p_stream_segment_id, N9M_FS_UCHAR lock);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_stream_segment_lock_by_time(rmfs_nxm_stream_lock_para_t  *p_lock_para, N9M_FS_UCHAR lock);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_auto_unlock(rmfs_nxm_date_time_t *p_cur_date_time, N9M_FS_INT reserve_days, N9M_FS_ULL stream_bitmap);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_find_work_hdd(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_cur_disk_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_config_overwrite(N9M_FS_UCHAR group_id, rmfs_nxm_hdd_overwrite_config_t *p_rhoc);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_disk_overwrite_big_stream(N9M_FS_INT GroupId);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_disk_overwrite_small_stream(N9M_FS_INT GroupId, N9M_FS_ULONG reserve_days, N9M_FS_BOOL check_video_exist);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_fd_info(N9M_FS_INT ssfd, rmfs_nxm_stream_segment_id_t *p_ssid);

/*********************************************************************  
    Description: 
        ͨ�����δ򿪾����ȡ��Ӧ��������Ϣ
    Input:  
        ssfd------��������ID
    output:
        p_stream_info------������Ϣ
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_segment_info_by_fd(N9M_FS_INT ssfd, rmfs_nxm_stream_segment_info_t *p_stream_info);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_segment_info(rmfs_nxm_stream_segment_id_t *p_ssid, rmfs_nxm_stream_segment_info_t *p_stream_info);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_segment_data_info(rmfs_nxm_stream_segment_id_t *p_ssid, rmfs_nxm_time_t *p_start_time, rmfs_nxm_time_t *p_end_time, N9M_FS_ULL *p_offset, N9M_FS_ULL *p_data_len);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_special_get_stream_segment_data_info(rmfs_nxm_stream_segment_id_t *p_ssid, rmfs_nxm_time_t *p_start_time, rmfs_nxm_time_t *p_end_time, N9M_FS_ULL *p_offset, N9M_FS_ULL *p_data_len, N9M_FS_BOOL out_search);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_pre_record_info(N9M_FS_INT ssfd, N9M_FS_UCHAR record_type, N9M_FS_ULL alarm_type[4], N9M_FS_UCHAR lock, N9M_FS_ULONG lock_type, rmfs_nxm_time_t start_time, rmfs_nxm_stream_segment_info_t *p_stream_info = N9M_FS_NULL);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_overwrite_pre_record_stream(N9M_FS_INT ssfd, rmfs_nxm_time_t end_time);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_stream_segment_end_time(rmfs_nxm_stream_segment_id_t ssid, rmfs_nxm_time_t end_time);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_stream_segment_info(rmfs_nxm_modify_segment_para_t *p_modify_para);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_stream_segment_info_by_fd(N9M_FS_INT ssfd, N9M_FS_UCHAR modify_mask, N9M_FS_UCHAR lock, N9M_FS_ULONG lock_type, N9M_FS_UCHAR record_type, N9M_FS_ULL alarm_type[4], rmfs_nxm_time_t *p_start_time, rmfs_nxm_stream_segment_info_t *p_stream_info = N9M_FS_NULL, N9M_FS_ULONG* p_split_num = N9M_FS_NULL);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_write_device_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_info, N9M_FS_INT dev_info_len);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_write_device_info_to_all_disk(N9M_FS_CHAR *p_dev_info, N9M_FS_INT dev_info_len);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_device_info_len(N9M_FS_UCHAR hdd_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_device_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_read_buffer, N9M_FS_INT buffer_len);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_test_hdd(N9M_FS_UCHAR hdd_id, N9M_FS_ULONG data_size);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_disk_recovery(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, rmfs_nxm_recovery_para_t *p_recovery_para);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_auto_delete(rmfs_nxm_date_time_t *p_cur_date_time, N9M_FS_INT reserve_days, N9M_FS_UINT group_bitmap);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_delete_stream_segment_by_para(rmfs_nxm_delete_para_t *p_delete_para);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_delete_stream_segment(rmfs_nxm_stream_segment_id_t *pStream_segment_id);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_config_overwrite_mainstream(N9M_FS_UCHAR group_id, rmfs_nxm_mainstream_overwrite_config_t *p_rhoc);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_disk_overwrite_mainstream(N9M_FS_INT GroupId);

/*********************************************************************  
    Description: 
        ��ȡ������Ϣ�б�
    Input:  
        group_bitmap------������λͼ
        stream_type_bitmap------������������,��bit����
        p_name_list------�������������������ַ��������б�
        list_size------�б����С
    output:
        ��
    Return: 
        ����:ʧ��
        ����:��ָ����������ʵ�ʸ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_segment_name_list(N9M_FS_ULONG group_bitmap, N9M_FS_ULL stream_type_bitmap, N9M_FS_CHAR *p_name_list[60], N9M_FS_INT list_size);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_set_auto_fsync(N9M_FS_UCHAR hdd_id, N9M_FS_BOOL is_sync);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_stream_segment_iframe_data_info(rmfs_nxm_stream_segment_id_t *p_ssid, rmfs_nxm_time_t *p_start_time, rmfs_nxm_time_t *p_end_time, N9M_FS_ULL *p_offset, rmfs_nxm_stream_segment_info_t *p_stream_info);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_special_get_stream_segment_iframe_data_info(rmfs_nxm_stream_segment_id_t *p_ssid, rmfs_nxm_time_t *p_start_time, rmfs_nxm_time_t *p_end_time, N9M_FS_ULL *p_offset, rmfs_nxm_stream_segment_info_t *p_stream_info, N9M_FS_ULL search_len);


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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_set_rmfs_write_attr_for_windows(N9M_FS_UCHAR hdd_id, N9M_FS_UCHAR write_enable);

/*********************************************************************  
    Description: 
        sync disk
    Input:  
        hdd_id------Ӳ��ID,Ҳ����Ӳ�̵��Ա�ţ���Ӧ�ò������������Ҫ��֤��ͬ�Ĵ���ID��Ҫ��һ����ȡֵ��Χ0-32
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_sync_disk(N9M_FS_UCHAR hdd_id);

/*********************************************************************  
    Description: 
        д��ץ��ͼƬ
    Input:  
        p_buffer------ץ��ͼƬ���ݻ�����
        len------д��ͼƬ���ݳ���
        frame_num------д�뻺������ͼƬ����
        p_frame_info------ͼƬ֡��Ϣ��
    output:
        ��
    Return: 
        -1:ʧ��
        ����:ʵ��д������ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_write_snap_data(N9M_FS_UCHAR group_id, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_INT frame_num, rmfs_nxm_write_snap_frame_info_t *p_frame_info);

/*********************************************************************  
    Description: 
        ��ȡץ��ͼƬ����
    Input:  
        pSnap_id------ץ��ͼƬID,��ѯ�������
        p_buffer------���ݻ�����
        len------������ȡ���ݳ���
        p_attached_info--������Ϣ
    Return: 
        -1:ʧ��
        ����:ʵ�ʶ�ȡ�����ݳ���
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_read_snap_data(rmfs_nxm_stream_segment_id_t *pSnap_id, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len, N9M_FS_UCHAR *p_attached_info);

/*********************************************************************  
    Description: 
        ����ץ�ĸ��Ǳ����������������ϲ㲻���øýӿڽ������ã���ô�ļ�ϵͳĬ�������20000��
    Input:  
        group_id------��ID
        reserve_num---���������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_config_overwrite_snap(N9M_FS_UCHAR group_id, N9M_FS_ULONG reserve_num);

/*********************************************************************  
    Description: 
        ץ�ĸ��ǡ������ļ�ϵͳ���ڣ��������̡߳�������Ҫ�ϲ���øýӿڽ��и��ǲ�����
    Input:  
        group_id------��ID
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_overwrite_snap(N9M_FS_INT GroupId);

/*********************************************************************  
    Description: 
        ��ȡ��ѯץ����Ϣ���
    Input:  
        p_query_para------��ѯ����
    output:
        ��
    Return: 
        -1:ʧ��
        ����:��ѯ������
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_query_snap_handle(rmfs_nxm_snap_query_t *p_query_para);

/*********************************************************************  
    Description: 
        �ر�ץ�Ĳ�ѯ���
    Input:  
        query_handle------��ѯ������
    output:
        ��
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_close_query_snap_handle(N9M_FS_INT query_handle);

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
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_query_snap_info(N9M_FS_INT query_handle, N9M_FS_INT *p_get_num, rmfs_nxm_snap_info_query_result_t *p_query_result);

/*********************************************************************  
    Description: 
        �޸�ץ�İ�����Ϣ
    Input:  
        pSnap_id------ץ��ͼƬID,��ѯ�������
        p_buffer------д�뻺����
        len------�����а�����Ϣ����
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_modify_snap_info(rmfs_nxm_stream_segment_id_t *pSnap_id, N9M_FS_UCHAR *p_buffer, N9M_FS_INT len);

/*********************************************************************  
    Description: 
        ��ȡץ������������λ��
    Input:  
        hdd_id------����id
        p_dev_name------�豸����
        offset------������ʼƫ����
        size-------��������С
    Return: 
        0:�ɹ�
        ��0:ʧ��
 ********************************************************************/
NXM_DLL_API N9M_FS_INT api_rmfs_nxm_get_disk_snap_index_info(N9M_FS_UCHAR hdd_id, N9M_FS_CHAR *p_dev_name, N9M_FS_ULL &offset, N9M_FS_ULL &size);
#endif

