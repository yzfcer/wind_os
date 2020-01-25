/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
**
**                                       yzfcer@163.com
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: list_dev.c
**��   ��   ��: Jason Zhou
**����޸�����: 2018.03.26
**��        ��: ���豸����ע���ļ�
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2018.03.26  
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: Jason Zhou
** �ա���: 2018.03.26
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_blkdev.h"
#include "wind_debug.h"
#if WIND_BLKDEV_SUPPORT
extern w_blkdev_s memblk_dev[1];
extern w_blkdev_s disk_dev[4];
//extern w_blkdev_s spi_flash_dev[2];
//extern w_blkdev_s at24c02_dev[1];
//extern w_blkdev_s null_dev[2];
w_err_t _register_blkdevs(void)
{
    //wind_blkdev_register(&gpio_dev,1);
    //wind_blkdev_register(at24c02_dev,1);
    //wind_blkdev_register(spi_flash_dev,2);
    wind_blkdev_register(memblk_dev,1);
    wind_blkdev_register(disk_dev,4);
    //wind_blkdev_register(null_dev,2);
    return W_ERR_OK;
}
#endif
