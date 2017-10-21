/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
**
**                                       yzfcer@163.com
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: wind_message.c
**��   ��   ��: �ܽ���
**����޸�����: 2012.09.26
**��        ��: wind os����Ϣ��صĴ���
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: �ܽ���
** ��  ��: v1.0
** �ա���: 2012.09.26
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: �ܽ���
** �ա���: 2012.10.20
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

#include "wind_config.h"
#include "wind_type.h"
#include "wind_os_hwif.h"
#include "wind_msgbox.h"
#include "wind_core.h"
#include "wind_stati.h"
#include "wind_var.h"
#include "wind_err.h"
#include "wind_assert.h"
#if WIND_MESSAGE_SUPPORT > 0
extern void wind_thread_dispatch(void);

static pmsg_s msg_malloc(void)
{
    return (pmsg_s)wind_core_alloc(STAT_MESSAGE);
}

static w_err_t msg_free(pmsg_s msg)
{
    return wind_core_free(STAT_MESSAGE,(void *)msg);
}


static pmbox_s mbox_malloc(void)
{
    return (pmbox_s)wind_core_alloc(STAT_MBOX);
}

static w_err_t mbox_free(pmbox_s mbox)
{
    return wind_core_free(STAT_MBOX,(void *)mbox);
}


//********************************************internal functions******************************

//ɾ�����������������Ϣ
static w_err_t mbox_delete_msgs(pmbox_s mbox)
{
    pdnode_s pnode;
    pmsg_s msg;
    WIND_ASSERT_RETURN(mbox != NULL,ERR_NULL_POINTER);
    foreach_node(pnode,&mbox->msglist)
    {
        dlist_remove(&mbox->msglist,pnode);
        msg = DLIST_OBJ(pnode,msg_s,msgnode);
        wind_message_destroy(msg);
    }
    return ERR_OK;
}
//********************************************internal functions******************************


//**********************************************extern functions******************************

//����һ����Ϣ����������Ϣ
pmsg_s wind_message_create(const char *name,w_uint16_t msg_id,
                            w_uint16_t msg_len,void *msg_arg)
{
    pmsg_s pmsg;
    pmsg = msg_malloc();
    WIND_ASSERT_RETURN(pmsg != NULL,NULL);
    pmsg->name = name;
    DNODE_INIT(pmsg->msgnode);
    pmsg->used = B_TRUE;
    pmsg->msg_id = msg_id;
    pmsg->msg_len = msg_len;
    pmsg->msg_arg = msg_arg;
    return pmsg;
}

w_err_t wind_message_destroy(pmsg_s pmsg)
{
    w_err_t err;
    WIND_ASSERT_RETURN(pmsg != NULL,ERR_NULL_POINTER);
    pmsg->used = B_FALSE;
    pmsg->name = NULL;
    err = msg_free(pmsg);
    return err;
}


//�������䣬ֻ�����߳��д������������ж��к��߳�����֮ǰ
pmbox_s wind_mbox_create(const char *name,pthread_s owner)
{
    pmbox_s pmbox;
    pmbox = mbox_malloc();
    WIND_ASSERT_RETURN(pmbox != NULL,NULL);

    pmbox->name = name;
    DNODE_INIT(pmbox->mboxnode);
    DLIST_INIT(pmbox->msglist);
    pmbox->num = 0;
    pmbox->used = B_TRUE;
    pmbox->valid = B_TRUE;
    pmbox->owner = owner;
    wind_close_interrupt();
    dlist_insert_tail(&g_core.mboxlist,&pmbox->mboxnode);
    wind_open_interrupt();
    return pmbox;
}

w_err_t wind_mbox_destroy(pmbox_s pmbox)
{
    w_err_t err;
    pthread_s pthread;
    WIND_ASSERT_RETURN(pmbox != NULL,ERR_NULL_POINTER);
    pthread = pmbox->owner;
    if((pmbox->owner->runstat == THREAD_STATUS_SUSPEND) 
       && (pmbox->owner->cause == CAUSE_MSG))
    {
        pthread->runstat = THREAD_STATUS_READY;
    }

    wind_close_interrupt();
    dlist_remove_tail(&g_core.mboxlist);
    pmbox->valid = B_FALSE;
    pmbox->owner = NULL;
    pmbox->name = NULL;
    err = mbox_delete_msgs(pmbox);
    WIND_ASSERT_RETURN(err == ERR_OK,err);
    mbox_free(pmbox);
    wind_open_interrupt();
    return ERR_OK;
}

w_err_t wind_mbox_post(pmbox_s mbox,pmsg_s pmsg)
{
    pthread_s pthread;
    WIND_ASSERT_RETURN(mbox != NULL,ERR_NULL_POINTER);
    WIND_ASSERT_RETURN(pmsg != NULL,ERR_NULL_POINTER);
    WIND_ASSERT_RETURN(mbox->valid,ERR_COMMAN);
    WIND_ASSERT_RETURN(mbox->owner,ERR_COMMAN);
    //����Ϣ��������
    wind_close_interrupt();
    dlist_insert_tail(&mbox->msglist,&pmsg->msgnode);
    mbox->num ++;

    //����������߳�
    pthread = mbox->owner;
    if((pthread->runstat != THREAD_STATUS_SUSPEND) 
       || (pthread->cause != CAUSE_MSG))
    {
        wind_open_interrupt();
        return ERR_OK;
    }
    mbox->owner->runstat = THREAD_STATUS_READY;
    wind_open_interrupt();
    wind_thread_dispatch();//�л��߳�
    return ERR_OK;
}


w_err_t wind_mbox_fetch(pmbox_s mbox,pmsg_s *pmsg,w_uint32_t timeout)
{
    w_err_t err;
    w_uint32_t ticks;
    pdnode_s dnode;
    pthread_s pthread;
    WIND_ASSERT_RETURN(mbox != NULL,ERR_NULL_POINTER);
    WIND_ASSERT_RETURN(pmsg != NULL,ERR_NULL_POINTER);
    WIND_ASSERT_RETURN(mbox->valid,ERR_COMMAN);
    WIND_ASSERT_RETURN(mbox->owner,ERR_COMMAN);
    
    //�������������Ϣ����ֱ�ӷ�����Ϣ
    wind_close_interrupt();
    if(mbox->num > 0)
    {
        dnode = dlist_remove_head(&mbox->msglist);
        *pmsg = DLIST_OBJ(dnode,msg_s,msgnode);
        wind_open_interrupt();
        return ERR_OK;
    }

    //�����̼߳���˯�߶���
    ticks = timeout * WIND_TICK_PER_SEC / 1000;
    if(ticks == 0)
        ticks = 1;
    pthread = mbox->owner;
    pthread->runstat = THREAD_STATUS_SUSPEND;
    pthread->cause = CAUSE_MSG;
    dlist_insert_tail(&g_core.sleeplist,&pthread->sleepthr.node);
    wind_open_interrupt();
    
    wind_thread_dispatch();
    if(pthread->cause == CAUSE_MSG)
    {
        if(mbox->num <= 0)
        {
            pthread->runstat = THREAD_STATUS_READY;
            return ERR_NULL_POINTER;
        }
        dnode = dlist_remove_head(&mbox->msglist);
        *pmsg = DLIST_OBJ(dnode,msg_s,msgnode);
        wind_open_interrupt();
        err = ERR_OK;
    }
    else if(pthread->cause == CAUSE_SLEEP)
    {
        err = ERR_OK;
    }
    
    return err;
}


#endif  //WIND_MESSAGE_SUPPORT
