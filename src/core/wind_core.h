/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_core.h
**创   建   人: 周江村
**最后修改日期: 2012.09.26
**描        述: wind os的核心代码头文件
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2012.09.26
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 周江村
** 日　期: 2012.10.20
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

#ifndef WIND_CORE_H__
#define WIND_CORE_H__
#include "wind_config.h"
#include "wind_types.h"
#include "wind_thread.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct 
{
    char *name;
    err_t (*init)(void);
}init_step_s;


#if WIND_REALTIME_CORE_SUPPORT > 0
void wind_thread_dispatch(void);
#else
#define wind_thread_dispatch() 
#endif

void wind_enter_core(void);
void wind_exit_core(void);

void wind_enter_int(void);
void wind_exit_int(void);


#ifdef __cplusplus
}
#endif

#endif

