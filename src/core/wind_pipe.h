/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_pipe.h
**创   建   人: Jason Zhou
**最后修改日期: 2012.09.26
**描        述: wind os的管道相关的代码,管道是一种数据通信机制，不是线程同步机制
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2012.09.26
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: Jason Zhou
** 日　期: 2012.10.20
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_PIPE_H__
#define WIND_PIPE_H__

#include "wind_config.h"
#include "wind_type.h"
#include "wind_dlist.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (WIND_PIPE_SUPPORT)

#define WIND_PIPE_MAGIC 0x56384c6a
#define PIPE_NAME_LEN 12

typedef struct __w_pipe_s
{
    w_uint32_t magic;
    const char *name;
    w_dnode_s pipenode;
    void *buff;
    w_uint16_t buflen;
    w_uint16_t flag_pool:1;
}w_pipe_s;

w_err_t _wind_pipe_mod_init(void);
w_err_t _wind_pipe_print(w_dlist_s* list);
w_pipe_s* wind_pipe_get(const char *name);
w_err_t wind_pipe_init(w_pipe_s* pipe,const char *name,void *buff,w_uint32_t buflen);
w_pipe_s* wind_pipe_create(const char *name,void *buff,w_uint32_t buflen);
w_int32_t wind_pipe_read(w_pipe_s* pipe,w_int8_t *str,w_int16_t len);
w_int32_t wind_pipe_write(w_pipe_s* pipe,w_int8_t *str,w_int16_t len);
w_err_t wind_pipe_destroy(w_pipe_s* pipe);


#endif //WIND_PIPE_SUPPORT
#ifdef __cplusplus
}
#endif


#endif

