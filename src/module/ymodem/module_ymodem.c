/****************************************Copyright (c)**************************************************
**                                       God's harbor
** FileName    : module_ymodem.c
** Author      : Jason Zhou
** Last Date   : 2015/1/24 20:24:37
** Description : YMODEM module entry
**  
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2020/05/11 00:24:37
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : 
** Date        : 
** Description : 
** 
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_module.h"
#include "wind_cmd.h"
#include "wind_ymodem.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus
#if WIND_MODULE_YMODEM_SUPPORT
COMMAND_DECLARE(ymodem);



MODULE_INIT(ymodem)
{
    w_err_t err;
    err = wind_cmd_register(COMMAND(ymodem));
    return err;//_wind_ymodem_mod_init();
}

MODULE_EXIT(ymodem)
{
    w_err_t err;
    err = wind_cmd_unregister(COMMAND(ymodem));
    return err;//_wind_ymodem_mod_init();
}

MODULE_DEF(ymodem, 0x0100,"");

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
