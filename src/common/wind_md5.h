/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_md5.h
**创   建   人: Jason Zhou
**最后修改日期: 2019.2.18
**描        述: MD5算法模块
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 
** 版  本: v1.0
** 日　期: 2019.2.18
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 2019.2.18
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_MD5_H__
#define WIND_MD5_H__
#include "wind_type.h"
   

typedef struct { 
    w_uint32_t state[4];        /* state (ABCD) */ 
    w_uint32_t count[2]; /* number of bits, modulo 2^64 (lsb first) */ 
    w_uint8_t buffer[64];      /* input buffer */ 
} w_md5_ctx_s; 
   
void wind_md5_init   (w_md5_ctx_s *ctx); 
void wind_md5_update (w_md5_ctx_s *ctx,w_uint8_t *data, w_uint32_t len); 
void wind_md5_final  (w_md5_ctx_s *ctx,w_uint8_t digest[16]); 


#endif