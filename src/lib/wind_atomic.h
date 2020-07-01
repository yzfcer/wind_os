/****************************************Copyright (c)**************************************************
**                                       God's harbor
** FileName    : wind_atomic.h
** Author      : Jason Zhou
** Last Date   : 2014/10/26 2:20:23
** Description : Atomic variable operation interface
**  
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2014/10/26 2:20:23
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : 
** Date        : 
** Description : 
** 
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_ATOMIC_H__
#define WIND_ATOMIC_H__


#include "wind_config.h"
#include "wind_type.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus



/***********************************************macros*************************************************/



/***********************************************enum*************************************************/



/***********************************************struct*************************************************/
typedef struct __atomic_t
{
    volatile w_uint32_t value;
}w_atomic_t;

/********************************************global variable declare**********************************************/



/********************************************global function declare**********************************************/
void atomic_inc(w_atomic_t atom);
void atomic_dec(w_atomic_t atom);

void atomic_add(w_atomic_t atom,w_uint32_t va);
void atomic_minus(w_atomic_t atom,w_uint32_t va);

void atomic_set(w_atomic_t atom,w_uint32_t value);
void atomic_get(w_atomic_t atom,w_uint32_t *value);



#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif // #ifndef WIND_ATOMIC_H__

