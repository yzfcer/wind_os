/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_list.h / wind_list.c
**创   建   人: 周江村
**最后修改日期: 2012.09.26
**描        述: wind os的内核链表方法
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
#ifndef WIND_LIST_H__
#define WIND_LIST_H__


#include "wind_config.h"
#include "wind_types.h"
//#include "wind_thread.h"
//#include "wind_message.h"
//#include "wind_sem.h"

#ifdef __cplusplus
extern "C"{
#endif
typedef enum __core_type
{
    CORE_TYPE_MIN = 0,
    CORE_TYPE_PCB,//PCB
    CORE_TYPE_MSG,//消息
    CORE_TYPE_SEM,//信号量
    CORE_TYPE_TTIMER,//tick定时器
    CORE_TYPE_LOCK,//互斥锁
    CORE_TYPE_HEAP,//内存堆
    CORE_TYPE_MAX
} core_type;



typedef struct __wind_node
{
    core_type type;
    bool_t used;
    bool_t minus;
    s32_t key;
    void *obj;
    struct __wind_node *next;    
}node_s,*pnode_s;

pnode_s wind_node_malloc(core_type type);
err_t wind_node_free(pnode_s node);

err_t wind_list_insert(pnode_s *list,pnode_s node);
err_t wind_list_inserttoend(pnode_s *list,pnode_s node);
err_t wind_list_inserttohead(pnode_s *list,pnode_s node);
err_t wind_list_insert_with_minus(pnode_s *list,pnode_s node);
pnode_s wind_list_remove(pnode_s *list,pnode_s node);
pnode_s wind_list_search(pnode_s *list,void *obj);

void printlist(pnode_s node);
#ifdef __cplusplus
}
#endif

#endif
