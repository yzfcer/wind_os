/****************************************Copyright (c)**************************************************
**                                       God's harbor
** FileName    : thread_stati.c
** Author      : Jason Zhou
** Last Date   : 2016/04/03 20:24:37
** Description : Statistics threads, process CPU usage
**  
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2020/05/11 00:24:37
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : 
** Date        : 
** Description : 
** 
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_type.h"
#include "wind_core.h"
#include "wind_thread.h"
#include "wind_debug.h"
#if WIND_STATI_THREAD_SUPPORT


static w_stack_t statisstk[THREAD_STATI_STKSIZE];
static w_err_t thread_stati(w_int32_t argc,char **argv)
{
    w_uint32_t statcnt = 0;
    w_int32_t stati_ms = 1000;
    //w_core_var_s core_var;
    //wind_get_core_var(&core_var)
    while(1)
    {
        statcnt = g_core.idle_cnt;
        wind_thread_sleep(stati_ms);
        statcnt = g_core.idle_cnt - statcnt;
        g_core.cpu_usage = (g_core.idle_cnt_max - statcnt) *100 / g_core.idle_cnt_max;
        if(g_core.cpu_usage > 100)
            g_core.cpu_usage = 0;
    }
    return W_ERR_OK;
}

w_err_t _create_thread_stati(void)
{
    w_thread_s *thread;
    thread = wind_thread_create("statistics",thread_stati,
                     0,W_NULL,statisstk,THREAD_STATI_STKSIZE);
    WIND_ASSERT_RETURN(thread != W_NULL,W_ERR_FAIL);
    wind_thread_setflag(thread,F_THREAD_NO_KILL | F_THREAD_SYSTEM);
    wind_thread_set_priority(thread,5);
    return W_ERR_OK;
}
#endif
