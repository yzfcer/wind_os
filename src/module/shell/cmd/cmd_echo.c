/****************************************Copyright (c)**************************************************
**                                       God's harbor
** FileName    : cmd_echo.c
** Author      : Jason Zhou
** Last Date   : 2015/1/24 20:24:37
** Description : Echo output command
**  
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2015/1/24 20:24:37
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : 
** Date        : 
** Description : 
** 
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#if CMD_ECHO_SUPPORT


COMMAND_DISC(echo)
{
    wind_printf("to display echo string that you input.\r\n");
}

COMMAND_USAGE(echo)
{
    wind_printf("echo <str>:--to show str on your std displaying device.\r\n");
}

COMMAND_MAIN(echo,argc,argv)
{
    char *str;
    WIND_ASSERT_RETURN(argc >= 2,W_ERR_INVALID);
    str = argv[1];
    wind_printf("%s",str);
    return W_ERR_OK;
}

COMMAND_DEF(echo);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
