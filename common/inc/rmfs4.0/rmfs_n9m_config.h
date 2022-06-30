/********************************************************
    Copyright (C), 2007-2099,SZ-STREAMING Tech. Co., Ltd.
    File name:        
    Author:
        xzyang
    Date:        
    Description:
********************************************************/
#ifndef __RMFS_N9M_CONFIG_H__
#define __RMFS_N9M_CONFIG_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#define _PLATFORM_LINX_
#endif


/*各种数据类型*/
/********************************************************/
typedef char                N9M_FS_CHAR;
typedef unsigned char       N9M_FS_UCHAR;
typedef short               N9M_FS_SHORT;
typedef unsigned short      N9M_FS_USHORT;
typedef int                 N9M_FS_INT;
typedef unsigned int        N9M_FS_UINT;
typedef long                N9M_FS_LONG;
typedef unsigned long       N9M_FS_ULONG; 
typedef void                N9M_FS_VOID;
typedef N9M_FS_UCHAR            N9M_FS_BOOL;
#define N9M_FS_NULL             NULL
#define N9M_FS_TRUE             1
#define N9M_FS_FALSE            0

#if defined(_PLATFORM_LINX_)
    typedef long long       N9M_FS_LL;
    typedef unsigned long long  N9M_FS_ULL;
#else
    typedef __int64           N9M_FS_LL;
    typedef unsigned __int64  N9M_FS_ULL;
#endif
/********************************************************/


/********************************************************/
/*
    一个磁盘最大的分区的数目        
*/
#define N9M_FS_MAX_PARTITION_NUM    10
/********************************************************/


#endif/*__RMFS_CONFIG_H__*/

