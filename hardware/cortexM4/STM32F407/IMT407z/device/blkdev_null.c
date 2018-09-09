/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: blkdev_null.c
**创   建   人: 周江村
**最后修改日期: 2018.03.26
**描        述: 24C02 EEPROM块设备注册文件
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2018.03.26  
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 周江村
** 日　期: 2018.03.26
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_blkdev.h"
#include "wind_debug.h"
#include "wind_string.h"
#include "24c02.h"
#if WIND_BLK_DRVFRAME_SUPPORT

static w_err_t   null_open(blkdev_s *dev)
{
    return ERR_OK;
}

static w_err_t   null_erase(blkdev_s *dev,w_addr_t addr,w_int32_t blkcnt)
{
    return ERR_OK;
}

static w_err_t   null_eraseall(blkdev_s *dev)
{
    return ERR_OK;
}


static w_int32_t null_read(blkdev_s *dev,w_addr_t addr,w_uint8_t *buf,w_int32_t blkcnt)
{
    return blkcnt;
}

static w_int32_t null_write(blkdev_s *dev,w_addr_t addr,w_uint8_t *buf,w_int32_t blkcnt)
{   
    return blkcnt;
}

static w_err_t   null_close(blkdev_s *dev)
{
    return ERR_OK;
}

const blkdev_ops_s null_ops = 
{
    NULL,
    null_open,
    null_erase,
    null_eraseall,
    null_read,
    null_write,
    null_close
};

blkdev_s null_dev[1] = 
{
    WIND_BLKDEV_DEF("null",0,0,0,0,&null_ops)
};

#endif


