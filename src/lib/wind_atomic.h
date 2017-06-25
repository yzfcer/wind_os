/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: wind_atomic.h / wind_atomic.c
** 创   建   人: 周江村
** 最后修改日期: 2014/10/26 2:20:23
** 描        述: 
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2014/10/26 2:20:23
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef __WIND_ATOMIC_H__
#define __WIND_ATOMIC_H__

/*********************************************头文件定义***********************************************/
#include "wind_config.h"
#include "wind_types.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus



/***********************************************宏定义*************************************************/



/**********************************************枚举定义************************************************/



/*********************************************结构体定义***********************************************/
typedef struct __atomic_t
{
    volatile u32_t value;
}atomic_t;

/********************************************全局变量申明**********************************************/



/********************************************全局函数申明**********************************************/
void atomic_inc(atomic_t atom);
void atomic_dec(atomic_t atom);

void atomic_add(atomic_t atom,u32_t va);
void atomic_minus(atomic_t atom,u32_t va);

void atomic_set(atomic_t atom,u32_t value);
void atomic_get(atomic_t atom,u32_t *value);



#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif // #ifndef __WIND_ATOMIC_H__

