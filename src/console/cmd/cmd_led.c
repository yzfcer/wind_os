/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_led.c
**创   建   人: 周江村
**最后修改日期: 2013.10.19
**描        述: 系统的控制台命令stat处理函数，统计资源使用情况
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
#include "stdio.h"
#include "wind_config.h"
#include "wind_type.h"
#include "wind_debug.h"
#include "wind_cmd.h"
#include "wind_dev.h"
#if WIND_CONSOLE_SUPPORT
#if WIND_DRVFRAME_SUPPORT

COMMAND_DISC(led)
{
    console_printf("control a led device.\r\n");
}

COMMAND_USAGE(led)
{
    console_printf("led on <ledindex>:to open a led device.\r\n");
    console_printf("led off <ledindex>:to close a led device.\r\n");
}

COMMAND_MAIN(led,argc,argv)
{
    w_err_t err;
    dev_s *led;
    w_uint8_t stat;
    char devname[8];
    WIND_ASSERT_RETURN(argc == 3,ERR_INVALID_PARAM);
    wind_memset(devname,0,sizeof(devname));
    sprintf(devname,"led%s",argv[2]);
    led = wind_dev_get(devname);
    WIND_ASSERT_RETURN(led != NULL,ERR_INVALID_PARAM);
    if(0 == wind_strcmp(argv[1],"on"))
    {
        err = wind_dev_open(led);
        WIND_ASSERT_RETURN(err == ERR_OK,ERR_COMMAN);
        stat = 1;
        wind_dev_write(led,&stat,1);
        return ERR_OK;
    }
    else if(0 == wind_strcmp(argv[1],"off"))
    {
        err = wind_dev_open(led);
        WIND_ASSERT_RETURN(err == ERR_OK,ERR_COMMAN);
        stat = 0;
        wind_dev_write(led,&stat,1);
        return ERR_OK;
    }
    return ERR_COMMAN;
}

COMMAND_DEF(led);

#endif
#endif

