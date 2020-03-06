/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: module_db.c
** 创   建   人: Jason Zhou
** 最后修改日期: 2015/1/24 20:24:37
** 描        述: db模块入口
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2015/1/24 20:24:37
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_module.h"
#include "wind_debug.h"
#include "db_if.h"
#include "wind_cmd.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************头文件定义***********************************************/

#if (WIND_MODULE_DB_SUPPORT)

/********************************************内部变量定义**********************************************/




/********************************************内部函数定义*********************************************/



/********************************************全局变量定义**********************************************/
#if CMD_DB_SUPPORT
COMMAND_DECLARE(db);
COMMAND_DECLARE(tbmodel);
#endif


/********************************************全局函数定义**********************************************/

MODULE_INIT(db)
{
    w_err_t err;
#if CMD_DB_SUPPORT
    err = wind_cmd_register(COMMAND(db));
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
    err = wind_cmd_register(COMMAND(tbmodel));
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
#endif
    err = _wind_db_mod_init();
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
    return err;
}

MODULE_EXIT(db)
{
    w_err_t err;
#if CMD_DB_SUPPORT
    err = wind_cmd_unregister(COMMAND(db));
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
    err = wind_cmd_unregister(COMMAND(tbmodel));
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
#endif
    return W_ERR_OK;
}

MODULE_DEF(db, 0x0100,"");

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
