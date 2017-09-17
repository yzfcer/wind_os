/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_test.c
**创   建   人: 周江村
**最后修改日期: 2013.11.06
**描        述: 系统的控制台命令test处理函数，提供一些系统内核测试的命令的响应函数
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2013.11.06
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 周江村
** 日　期: 2013.11.06
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_config.h"
#include "wind_type.h"
#include "console_framework.h"
#include "wind_err.h"
#include "wind_debug.h"
#include "wind_mem.h"
#include "wind_string.h"
#include "wind_thread.h"
#include "wind_list.h"
#include "wind_softint.h"
#include "wind_heap.h"

w_err_t cmd_testsoftint_main(w_int32_t argc,char **argv)
{
#if WIND_SOFTINT_SUPPORT > 0
    if(0 == wind_strcmp(argv[0],"softint"))
    {
        wind_softint_test();
        return ERR_OK;
    }
#endif
    return ERR_OK;
}

w_err_t cmd_testheap_main(w_int32_t argc,char **argv)
{
#if WIND_HEAP_SUPPORT > 0
    if(0 == wind_strcmp(argv[0],"heap"))
    {
        //wind_heap_test();
        wind_printf("heaptest not support yet\r\n");
        return ERR_OK;
    }
#endif
    return ERR_COMMAN;
}

static void cmd_showdisc(void)
{
    wind_printf("to test some test cases.\r\n");
}

static void cmd_showusage(void)
{
    wind_printf("test softint:to test soft interrupt module.");
    wind_printf("test heap","to test to allocate memory from the system memory heap.");
}

static w_err_t cmd_main(w_int32_t argc,char **argv)
{
    if(argc < 2)
    {
        cmd_showusage();
        return ERR_OK;
    }
    else if(0 == wind_strcmp(argv[1],"softint"))
    {
        return cmd_testsoftint_main(argc,argv);
    }
    else if(0 == wind_strcmp(argv[1],"heap"))
    {
        return cmd_testheap_main(argc,argv);
    }
    return  ERR_COMMAN;
}

CMD_DEF(test);

//#endif
