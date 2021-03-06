/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_diagnose.h
**创   建   人: Jason Zhou
**最后修改日期: 2019.02.24
**描        述: 系统故障诊断处理模块
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2019.02.24
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: Jason Zhou
** 日　期: 2019.02.24
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_DIAGNOSE_H__
#define WIND_DIAGNOSE_H__


#include "wind_config.h"
#include "wind_type.h"
#include "wind_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

#if WIND_DIAGNOSE_SUPPORT
#define WIND_DIAGNOSE_MAGIC 0x387A5247
typedef w_int32_t (*diagnose_fn)(void);
typedef enum
{
    DIAG_RES_OK = 0,
    DIAG_RES_ERROR,
    DIAG_RES_DIAG_MAGIC_ERROR,
    DIAG_RES_OBJ_MAGIC_ERROR,
    DIAG_RES_FUNC_NULL,
}w_diag_res_e;

typedef struct _wind_diagnose
{
    w_obj_s obj;
    w_int32_t result;
    diagnose_fn diagnose_func;
}w_diagnose_s;


#define DIAGNOSENOSE_DEF(name,func) \
    static w_diagnose_s g_diagnose_##name = \
    {{(~WIND_DIAGNOSE_MAGIC),#name,{W_NULL,W_NULL},0,0},0,func}
#define DIAGNOSENOSE(name) &g_diagnose_##name


w_err_t _wind_diagnose_mod_init(void);
w_diagnose_s *wind_diagnose_get(const char *name);
w_err_t wind_diagnose_register(w_diagnose_s *diagnose);
w_err_t wind_diagnose_unregister(w_diagnose_s *diagnose);
w_err_t wind_diagnose_check(void);
w_err_t wind_diagnose_print(void);

#endif
#ifdef __cplusplus
}
#endif
#endif//#ifndef WIND_DIAGNOSE_H__

