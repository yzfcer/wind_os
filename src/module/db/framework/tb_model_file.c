/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: tb_model_file.c
**创   建   人: Jason Zhou
**最后修改日期: 2020.3.9
**描        述: 数据表模型框架序列化功能函数即
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 
** 版  本: v1.0
** 日　期: 2020.3.9
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 2020.3.9
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_type.h"
#include "db_if.h"
#include "wind_debug.h"

w_err_t tbmodel_file_init(void);
w_err_t tbmodel_file_load(char *filepath);
w_err_t tbmodel_file_load_all(char *dirpath);

w_err_t tbmodel_file_save(char *filepath);
w_err_t tbmodel_file_save_all(char *dirpath);


