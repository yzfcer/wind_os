/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
**
**                                       yzfcer@163.com
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: entry.c
**��   ��   ��: Jason Zhou
**����޸�����: 2012.09.26
**��        ��: wind os���û�̬�������
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2012.09.26
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: Jason Zhou
** �ա���: 2012.10.20
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

/*
����ļ����û��������ڣ��û�������wind_main�������뿪ʼִ�У�����������������̵߳�
���ȼ��ܸߣ���˲������û�����������ֱ��ִ�У�������û������ﴴ�������е����ȼ����߳�
��ת���µ��߳���ִ���û�����ͬʱ���������Ҫ��ѭ���������˳��������߳�������˳�ʱ
û�д��������û����򽫲����ٴα�ִ�е�����Ϊwind_main����ֻ�ᱻϵͳ����һ��
*/

#include "beep.h"
#include "wind_debug.h"
#include "wind_sem.h"
#include "wind_mutex.h"
#include "wind_pipe.h"
extern led_start(void);
#if WIND_PIPE_SUPPORT
w_uint8_t pipebuff[128];
#endif



w_err_t wind_main(void)
{
    wind_notice("enter wind main.");
    led_start();
    BEEP_Init();
    return 0;
}