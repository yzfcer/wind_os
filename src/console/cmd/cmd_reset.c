/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: cmd_reset.c
**创   建   人: 周江村
**最后修改日期: 
**描        述: 系统的用户管理相关的定义，需要等待相关的文件系统支持
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
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
#include "wind_config.h"
#include "wind_type.h"
#include "wind_os_hwif.h"
#include "wind_cmd.h"
COMMAND_DISC(reset)
{
    console_printf("to reset system.\r\n");
}

COMMAND_USAGE(reset)
{
    console_printf("reset:to reset system.\r\n");
}

COMMAND_MAIN(reset,argc,argv)
{
    console_printf("system will reset now!\r\n");
    wind_thread_sleep(1000);
    wind_system_reset();
    while(1);
    //return ERR_OK;
}

COMMAND_DEF(reset);
