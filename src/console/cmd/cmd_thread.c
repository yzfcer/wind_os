/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: cmd_thread.c
** 创   建   人: 周江村
** 最后修改日期: 2018/9/14 21:24:37
** 描        述: 线程基本操作命令
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2018/9/14 21:24:37
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "wind_thread.h"
#include "wind_conv.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************头文件定义***********************************************/

#if (WIND_CONSOLE_SUPPORT && CMD_THREAD_SUPPORT)

/********************************************内部变量定义**********************************************/




/********************************************内部函数定义*********************************************/



/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/
COMMAND_DISC(thread)
{
    console_printf("to control thread status.\r\n");
}

COMMAND_USAGE(thread)
{
    console_printf("thread start <threadname>:to start a thread.\r\n");
    console_printf("thread suspend <threadname>:to suspend a thread.\r\n");
    console_printf("thread kill <threadname>:to kill a thread.\r\n");
    console_printf("thread setprio <threadname> <prio>:to change a thread priority.\r\n");
}

COMMAND_MAIN(thread,argc,argv)
{
    w_bool_t res;
    w_int32_t prio;
    w_thread_s *thread;
    if(argc < 3)
        return W_ERR_FAIL;
	thread = wind_thread_get(argv[2]);
    if(thread == W_NULL)
    {
        wind_error("has no such a thread:%s",argv[2]);
        return W_ERR_INVALID;
    }
    if(wind_strcmp(argv[1],"start") == 0)
    {
        wind_thread_start(thread);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"suspend") == 0)
    {
        wind_thread_suspend(thread);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"kill") == 0)
    {
        wind_thread_destroy(thread);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"setprio") == 0)
    {
        if(argc < 4)
            return W_ERR_FAIL;
        res = wind_atoi(argv[3],&prio);
        if(res != W_TRUE)
            return W_ERR_INVALID;
        wind_thread_set_priority(thread,prio);
        return W_ERR_OK;
    }
    return W_ERR_FAIL;
}

COMMAND_DEF(thread);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
