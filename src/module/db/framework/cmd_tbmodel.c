/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
**
**                                       yzfcer@163.com
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: cmd_tbmodel.c
**��   ��   ��: Jason Zhou
**����޸�����: 
**��        ��: DBģ�����ݱ�ģ�Ͳ�������
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "tb_model.h"
#if (CMD_DB_SUPPORT)
	

static w_err_t cmd_tbmodel_list(void)
{
    return wind_tbmodel_print_list();
}

static w_err_t cmd_tbmodel_detail(w_int32_t argc,char **argv)
{
    tb_model_s *tbmodel;
    if(argc == 2)
        wind_tbmodel_print_all();
    else if(argc >= 3)
    {
        tbmodel = wind_tbmodel_get(argv[2]);
        WIND_ASSERT_RETURN(tbmodel != W_NULL,W_ERR_NO_OBJ);
        return wind_tbmodel_print(tbmodel);
    }
    return W_ERR_FAIL;
}


COMMAND_DISC(tbmodel)
{
    wind_printf("to operate tbmodel system.\r\n");
}

COMMAND_USAGE(tbmodel)
{
    wind_printf("tbmodel list:--to show DB list.\r\n");
    wind_printf("tbmodel detail [modelname]:--to show tbmodel details.\r\n");
}

COMMAND_MAIN(tbmodel,argc,argv)
{
    WIND_ASSERT_RETURN(argc >= 2,W_ERR_INVALID);
    if(wind_strcmp(argv[1],"list") == 0)
        return cmd_tbmodel_list();
    else if(wind_strcmp(argv[1],"detail") == 0)
        return cmd_tbmodel_detail(argc,argv);
    return W_ERR_OK;
}

COMMAND_DEF(tbmodel);
#endif