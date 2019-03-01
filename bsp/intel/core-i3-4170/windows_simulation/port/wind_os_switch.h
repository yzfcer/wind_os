/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_os_switch.h
**创   建   人: Jason Zhou
**最后修改日期: 2019.02.27
**描        述: wind-os的线程上下文切换相关函数
**功        能: 
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2019.02.27
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: Jason Zhou
** 日　期: 2019.02.27
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_OS_SWITCH_H__
#define WIND_OS_SWITCH_H__
#include "wind_type.h"
#include "wind_dlist.h"
#include "wind_thread.h"
#include <Windows.h>

typedef struct
{
    char *name;
    HANDLE h_thread;
    w_dnode_s winthrnode;
    w_thread_s *thread;
}w_winthread_s;

w_winthread_s *windthread_get(char *name);


#endif

