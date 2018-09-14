/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: cmd_bee.c
**创   建   人: 周江村
**最后修改日期: 2013.10.19
**描        述: 蜂鸣器开关命令
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2013.10.19
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 周江村
** 日　期: 2013.10.19
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "wind_chdev.h"
#if WIND_CONSOLE_SUPPORT
#if WIND_DRVFRAME_SUPPORT


COMMAND_DISC(beep)
{
    console_printf("control the beep device.\r\n");
}

COMMAND_USAGE(beep)
{
    console_printf("beep on:to open the beep device.\r\n");
    console_printf("beep off:to close the beep device.\r\n");
}

COMMAND_MAIN(beep,argc,argv)
{
    w_chdev_s *dev;
    w_err_t err;
    w_uint8_t stat;
    dev = wind_chdev_get("beep");
    WIND_ASSERT_RETURN(dev != W_NULL,W_ERR_INVALID);
    if(0 == wind_strcmp(argv[1],"on"))
    {
        err = wind_chdev_open(dev);
        WIND_ASSERT_RETURN(err == W_ERR_OK,W_ERR_FAIL);
        stat = 1;
        wind_chdev_write(dev,&stat,1);
        return W_ERR_OK;
    }
    else if(0 == wind_strcmp(argv[1],"off"))
    {
        err = wind_chdev_open(dev);
        WIND_ASSERT_RETURN(err == W_ERR_OK,W_ERR_FAIL);
        stat = 0;
        wind_chdev_write(dev,&stat,1);
        return W_ERR_OK;
    }
    return W_ERR_FAIL;
}

COMMAND_DEF(beep);

#endif
#endif

