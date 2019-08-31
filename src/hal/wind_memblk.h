/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_memblk.h
**创   建   人: Jason Zhou
**最后修改日期: 
**描        述: 创建内存块设备的接口
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 
** 版  本: v1.0
** 日　期: 
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_MEMBLK_H__
#define WIND_MEMBLK_H__

#include "wind_config.h"
#include "wind_type.h"
#include "wind_blkdev.h"

#ifdef __cplusplus
extern "C" {
#endif

#if WIND_BLKDEV_SUPPORT
w_err_t wind_memblk_create(w_blkdev_s *blkdev,char *name,void *mem,w_int32_t size,w_int32_t blksize);
w_err_t wind_memblk_destroy(w_blkdev_s *blkdev);
#endif

#ifdef __cplusplus
}
#endif


#endif

