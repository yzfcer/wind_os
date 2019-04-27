/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: listfs_cache.h
**创   建   人: Jason Zhou
**最后修改日期: 2019.04.05
**描        述: 文件系统对块设备的操作接口
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2019.04.05
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: Jason Zhou
** 日　期: 2019.04.05
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef LISTFS_FILEINFO_H__
#define LISTFS_FILEINFO_H__
#include "wind_config.h"
#include "wind_type.h"
#include "wind_blkdev.h"



//固化文件系统信息
typedef struct __lfs_cache_s
{
    w_uint64_t magic;        //魔术字
    w_int32_t  self_addr;    //地址
    w_uint32_t blkcount;     //块数量
    
    w_uint16_t unit_size;    //文件单位大小
    w_uint16_t blksize;      //块大小
    w_uint16_t reserve_blk;  //保留块数
    w_uint16_t attr;         //文件系统属性
    w_uint32_t bitmap_cnt;   //位图块数
    w_addr_t   bitmap1_addr; //主位图地址
    w_addr_t   bitmap2_addr; //备份位图地址
    w_addr_t   root_addr;    //根目录位置
}lfs_cache_s;

w_err_t lfs_cache_init(lfs_cache_s *cache);

w_err_t lfs_cache_read(lfs_cache_s *cache,w_blkdev_s *blkdev,w_uint8_t *blk,w_int32_t cnt);

w_err_t lfs_cache_write(lfs_cache_s *cache,w_blkdev_s *blkdev,w_uint8_t *blk,w_int32_t cnt);

w_err_t lfs_cache_flush(lfs_cache_s *cache,w_blkdev_s *blkdev);


#endif

