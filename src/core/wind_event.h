/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_event.h
**创   建   人: Jason Zhou
**最后修改日期: 2012.09.26
**描        述: wind os的事件对象相关功能
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
#ifndef WIND_EVENT_H__
#define WIND_EVENT_H__


#include "wind_config.h"
#include "wind_type.h"
#include "wind_obj.h"
#include "wind_thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#if WIND_EVENT_SUPPORT
#define WIND_EVENT_MAGIC 0x5A9C524C

#define F_EVENT_POOL (0x01 << 0) //标记event对象是否通过内存池分配
#define IS_F_EVENT_POOL(event) ((event->obj.flag & F_EVENT_POOL) == F_EVENT_POOL)
#define SET_F_EVENT_POOL(event) (event->obj.flag |= F_EVENT_POOL)
#define CLR_F_EVENT_POOL(event) (event->obj.flag &= (~F_EVENT_POOL))

typedef struct __w_event_s w_event_s;
typedef void (*w_event_cb_fn)(w_event_s *event,void *arg);
	
typedef struct _w_event_cb
{
    w_dnode_s listenernode;
    w_event_cb_fn cb_fn;
}w_event_cb; 

struct __w_event_s
{
    w_obj_s obj;
    w_int16_t cbcnt;
    w_dlist_s cblist;//消息队列
};

w_err_t _wind_event_mod_init(void);
w_event_s *wind_event_get(const char *name);
w_err_t wind_event_init(w_event_s *event,const char *name);
w_event_s *wind_event_create(const char *name);

w_err_t wind_event_destroy(w_event_s *event);

w_err_t wind_event_regcb(w_event_s *event,w_event_cb *cb);
w_err_t wind_event_unregcb(w_event_s *event,w_event_cb *cb);
w_err_t wind_event_trig(w_event_s *event,void *arg);
w_err_t wind_event_print(void);


#endif //WIND_EVENT_SUPPORT

#ifdef __cplusplus
}
#endif
#endif  //WIND_EVENT_H__

