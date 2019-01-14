/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
** ��   ��   ��: cmd_thread.c
** ��   ��   ��: Jason Zhou
** ����޸�����: 2018/9/14 21:24:37
** ��        ��: �̻߳�����������
**  
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2018/9/14 21:24:37
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
** ���ļ���C����Դ�ļ�ģ���������ɡ�------------��纣����Ʒ��������Ʒ��------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "wind_thread.h"
#include "wind_conv.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************ͷ�ļ�����***********************************************/

#if (WIND_CONSOLE_SUPPORT && CMD_THREAD_SUPPORT)

/********************************************�ڲ���������**********************************************/




/********************************************�ڲ���������*********************************************/



/********************************************ȫ�ֱ�������**********************************************/



/********************************************ȫ�ֺ�������**********************************************/
COMMAND_DISC(thread)
{
    console_printf("to control thread status.\r\n");
}

COMMAND_USAGE(thread)
{
    console_printf("thread start <threadname>:to start a thread.\r\n");
    console_printf("thread suspend <threadname>:to suspend a thread.\r\n");
    console_printf("thread kill <threadname>:to kill a thread.\r\n");
    console_printf("thread setprio <threadname> <prio>:to change a thread priority.\r\n");
}

COMMAND_MAIN(thread,argc,argv)
{
    w_bool_t res;
    w_int32_t prio;
    w_thread_s *thread;
    WIND_ASSERT_RETURN(argc >= 3,W_ERR_INVALID);
	thread = wind_thread_get(argv[2]);
    if(thread == W_NULL)
    {
        wind_error("has no such a thread:%s",argv[2]);
        return W_ERR_INVALID;
    }
    if(wind_strcmp(argv[1],"start") == 0)
    {
        wind_thread_start(thread);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"suspend") == 0)
    {
        wind_thread_suspend(thread);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"kill") == 0)
    {
        wind_thread_destroy(thread);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"setprio") == 0)
    {
        WIND_ASSERT_RETURN(argc >= 4,W_ERR_INVALID);
        res = wind_atoi(argv[3],&prio);
        if(res != W_TRUE)
            return W_ERR_INVALID;
        wind_thread_set_priority(thread,prio);
        return W_ERR_OK;
    }
    return W_ERR_FAIL;
}

COMMAND_DEF(thread);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus