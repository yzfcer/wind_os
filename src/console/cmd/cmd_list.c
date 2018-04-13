/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: cmd_list.c
**创   建   人: 周江村
**最后修改日期: 2013.10.19
**描        述: 系统的控制台命令show处理函数，输出一些系统内部信息
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
#include "wind_config.h"
#include "wind_type.h"
#include "console_framework.h"
#include "wind_debug.h"
#include "wind_mem.h"
#include "wind_string.h"
#include "wind_thread.h"
#include "wind_sem.h"
#include "wind_mutex.h"
#include "wind_var.h"
#include "wind_cmd.h"
#include "wind_mpool.h"
#include "wind_msgbox.h"
#if WIND_CONSOLE_SUPPORT

COMMAND_DISC(list)
{
    console_printf("show core objects infomation.\r\n");
}

COMMAND_USAGE(list)
{
    console_printf("list thread:show thread infomation.\r\n");
    console_printf("list sem:show sem infomation.\r\n");
    console_printf("list mutex:show all mutex status.\r\n");
    console_printf("list pool:show all core object pools.\r\n");
    console_printf("list pipe:show all pipe infomation.\r\n");
    console_printf("list msgbox:show all message box infomation.\r\n");
}

COMMAND_MAIN(list,argc,argv)
{
    if(0 == wind_strcmp(argv[1],"thread"))
    {
        wind_thread_print(&g_core.threadlist);
        return ERR_OK;
    }
#if WIND_SEM_SUPPORT
    else if(0 == wind_strcmp(argv[1],"sem"))
    {
        wind_sem_print(&g_core.semlist);
        return ERR_COMMAN;
    }
#endif
    else if(0 == wind_strcmp(argv[1],"mutex"))
    {
        wind_mutex_print(&g_core.mutexlist);
        return ERR_COMMAN;
    }
    else if(0 == wind_strcmp(argv[1],"pool"))
    {
        _wind_pool_print_list(&g_core.poollist);
        return ERR_COMMAN;
    }
    else if(0 == wind_strcmp(argv[1],"pipe"))
    {
        _wind_pipe_print(&g_core.pipelist);
        return ERR_COMMAN;
    }
    else if(0 == wind_strcmp(argv[1],"msgbox"))
    {
        _wind_msgbox_print(&g_core.msgboxlist);
        return ERR_COMMAN;
    }
    return ERR_COMMAN;
}

COMMAND_DEF(list);

#endif
