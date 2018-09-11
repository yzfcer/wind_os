/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_mpool.h / wind_mpool.c
**创   建   人: 周江村
**最后修改日期: 2012.09.26
**描        述: wind os的内存池管理相关的功能函数
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2013.11.27
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 周江村
** 日　期: 2013.11.27
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_pool.h"
#include "wind_debug.h"
#include "wind_var.h"
#include "wind_core.h"
#include "wind_string.h"

#define WIND_MPOOL_ALIGN_R(x) (((x)+3) & (~0x03))
#define WIND_MPOOL_ALIGN_L(x) ((x) & (~0x03))

#define WIND_MPOOL_DEBUG(...) 

pool_s *wind_pool_get(const char *name)
{
    pool_s *pool;
    dnode_s *dnode;
    wind_disable_switch();
    foreach_node(dnode,&g_core.poollist)
    {
        pool = DLIST_OBJ(dnode,pool_s,poolnode);
        if(wind_strcmp(name,pool->name) == 0)
        {
            wind_enable_switch();
            return pool;
        }
    }
    wind_enable_switch();
    return NULL;
}

w_err_t wind_pool_create(const char *name,void *mem,w_uint32_t memsize,w_uint32_t itemsize)
{
    w_uint32_t i,si;
    pool_item_s* item;
    pool_s *pm;
    wind_notice("create pool:%s",name);
    WIND_ASSERT_RETURN(mem != NULL,W_ERR_NULL);
    WIND_ASSERT_RETURN(memsize > 0,W_ERR_INVALID);
    WIND_ASSERT_RETURN(itemsize > 0,W_ERR_INVALID);
    
    pm = (pool_s *)WIND_MPOOL_ALIGN_R((w_uint32_t)mem);
    if(pm != (pool_s *)mem)
        memsize -= (w_uint32_t)((w_uint32_t)pm - (w_uint32_t)mem);
    memsize = WIND_MPOOL_ALIGN_L(memsize);

    si = itemsize < sizeof(pool_item_s*)?sizeof(pool_item_s*):itemsize;
    si = WIND_MPOOL_ALIGN_R(si);
    if(memsize < sizeof(pool_s) + si)
        return -1;
    item = (pool_item_s*)(sizeof(pool_s) + (w_uint32_t)pm);
    pm->head = item;
    pm->name = name;
    DNODE_INIT(pm->poolnode);
    pm->size = memsize - sizeof(pool_s);
    pm->itemsize = si + sizeof(pool_item_s);
    pm->itemnum = pm->size / pm->itemsize;
    pm->free_head = (pool_item_s*)pm->head;
    item = (pool_item_s*)pm->head;
    for(i = 0;i < pm->itemnum;i ++)
    {
        pm->free_end = item;
        item->flag = POOL_BLK_FREE;
        item->next = (pool_item_s*)(pm->itemsize + (w_uint32_t)item);
        item = item->next;
    }
    item->next = NULL;
    WIND_STATI_INIT(pm->stati,pm->itemnum);
    wind_disable_interrupt();
    dlist_insert_tail(&g_core.poollist,&pm->poolnode);
    wind_enable_interrupt();
    pm->magic = WIND_POOL_MAGIC;
    //_wind_pool_print_list(&g_core.poollist);
    return W_ERR_OK;
}

w_err_t wind_pool_destroy(void *mem)
{
    pool_s *pm;
    WIND_ASSERT_RETURN(mem != NULL,W_ERR_NULL);
    pm = (pool_s *)WIND_MPOOL_ALIGN_R((w_uint32_t)mem);
    WIND_ASSERT_RETURN(pm->magic == WIND_POOL_MAGIC,W_ERR_INVALID);
    wind_notice("destroy pool:%s",pm->name);
    wind_disable_interrupt();
    dlist_remove(&g_core.poollist,&pm->poolnode);
    wind_enable_interrupt();
    pm->magic = 0;
    return W_ERR_OK;
}

void *wind_pool_malloc(void *mem)
{
    void *p;
    pool_s *pm;
    pool_item_s* item;
    WIND_ASSERT_RETURN(mem != NULL,NULL);
    pm = (pool_s *)WIND_MPOOL_ALIGN_R((w_uint32_t)mem);
    WIND_ASSERT_RETURN(pm->magic == WIND_POOL_MAGIC,NULL);

    wind_disable_interrupt();
    if(pm->free_head == NULL)
    {
        WIND_STATI_ERR_INC(pm->stati);
        wind_enable_interrupt();
        wind_error("mpool empty");
        return NULL;
    }
    item = pm->free_head;
    if(item->flag != POOL_BLK_FREE)
    {
        WIND_STATI_ERR_INC(pm->stati);
        wind_enable_interrupt();
        wind_error("mpool is NOT free.");
        return NULL;
    }
    pm->free_head = item->next;
    WIND_STATI_INC(pm->stati);
    if(pm->free_head == NULL)
        pm->free_end = NULL;
    
    item->flag = POOL_BLK_USED;
    item->next = NULL;
    p = (void*)(sizeof(pool_item_s*) + (w_uint32_t)item);
    wind_enable_interrupt();
    return p;
}

w_err_t wind_pool_free(void *mem,void *block)
{
    pool_s *pm;
    pool_item_s* item;
    
    WIND_ASSERT_RETURN(mem != NULL,W_ERR_NULL);
    WIND_ASSERT_RETURN(block != NULL,W_ERR_NULL);    
    pm = (pool_s *)WIND_MPOOL_ALIGN_R((w_uint32_t)mem);
    WIND_ASSERT_RETURN(pm->magic == WIND_POOL_MAGIC,W_ERR_INVALID);
    item = (pool_item_s*)(((w_uint32_t)block) - sizeof(pool_item_s*));
    WIND_ASSERT_RETURN(item->flag == POOL_BLK_USED,W_ERR_INVALID);
    wind_disable_interrupt();
    item->flag = POOL_BLK_FREE;
    item->next = NULL;
    if(pm->free_end == NULL)
    {
        pm->free_head = (pool_item_s*)item;
        pm->free_end = (pool_item_s*)item;
    }
    else
    {
        pm->free_end->next = (pool_item_s*)item;
        pm->free_end = (pool_item_s*)item;
    }
    WIND_STATI_DEC(pm->stati);
    wind_enable_interrupt();
    return W_ERR_OK;
}


void _wind_pool_print_list(dlist_s *list)
{
    dnode_s *pdnode;
    pool_s *pm;
    wind_printf("\r\n\r\nmpool list as following:\r\n");
    wind_print_space(7);
    wind_printf("%-12s %-12s %-8s %-8s %-8s\r\n","name","head","size","itemnum","itemsize");
    wind_print_space(7);
    foreach_node(pdnode,list)
    {
        pm = DLIST_OBJ(pdnode,pool_s,poolnode);
        wind_printf("%-12s 0x%-10x %-8d %-8d %-8d\r\n",
            pm->name,pm->head,pm->size,pm->itemnum,pm->itemsize);
    }
    wind_print_space(7);
}



