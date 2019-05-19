/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
** ��   ��   ��: cmd_timer.c
** ��   ��   ��: Jason Zhou
** ����޸�����: 2019/5/12 
** ��        ��: ��ʱ����������
**  
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2019/5/12 
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
#include "wind_timer.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************ͷ�ļ�����***********************************************/

#if (CMD_TIMER_SUPPORT)

/********************************************�ڲ���������**********************************************/




/********************************************�ڲ���������*********************************************/



/********************************************ȫ�ֱ�������**********************************************/



/********************************************ȫ�ֺ�������**********************************************/
COMMAND_DISC(timer)
{
    wind_printf("to control timer objects in the system.\r\n");
}

COMMAND_USAGE(timer)
{
    wind_printf("timer list:--to show timer list info.\r\n");
    wind_printf("timer start <name>:--to enable a timer identified by name.\r\n");
    wind_printf("timer stop <name>:--to disable a timer identified by name.\r\n");
}

COMMAND_MAIN(timer,argc,argv)
{
    w_timer_s *timer;
    WIND_ASSERT_RETURN(argc >= 2,W_ERR_INVALID);
    if(wind_strcmp(argv[1],"list") == 0)
        return wind_timer_print();
    
    WIND_ASSERT_RETURN(argc >= 3, W_ERR_FAIL);
    timer = wind_timer_get(argv[2]);
    WIND_ASSERT_RETURN(timer != W_NULL, W_ERR_INVALID);
    
    if(wind_strcmp(argv[1],"start") == 0)
        return wind_timer_setflag(timer,F_TIMER_RUN);
    else if(wind_strcmp(argv[1],"stop") == 0)
        return wind_timer_clrflag(timer,F_TIMER_RUN);
    else
        return W_ERR_FAIL;
}

COMMAND_DEF(timer);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus