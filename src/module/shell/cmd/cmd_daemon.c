/****************************************Copyright (c)**************************************************
**                                       God's harbor
** FileName    : cmd_daemon.c
** Author      : Jason Zhou
** Last Date   : 2019/1/29 21:45:25
** Description : Daemon object operation command
**  
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2019/1/29 21:45:25
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
#include "wind_string.h"
#include "wind_heap.h"
#include "wind_daemon.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#if (CMD_DAEMON_SUPPORT)



COMMAND_DISC(daemon)
{
    wind_printf("to set a daemon object status.\r\n");
}

COMMAND_USAGE(daemon)
{
    wind_printf("daemon list:--to set a daemon status via str.\r\n");
    wind_printf("daemon enable <daemonname>:--to enable a daemon object.\r\n");
    wind_printf("daemon disable <daemonname>:--to disable a daemon object.\r\n");
}

COMMAND_MAIN(daemon,argc,argv)
{
    w_daemon_s *daemon;
    WIND_ASSERT_RETURN(argc >= 2,W_ERR_INVALID);
    if(wind_strcmp(argv[1],"list") == 0)
    {
        wind_daemon_print_list();
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"enable") == 0)
    {
        WIND_ASSERT_RETURN(argc == 3,W_ERR_INVALID);
        daemon = wind_daemon_get(argv[2]);
        WIND_ASSERT_RETURN(daemon != W_NULL,W_ERR_INVALID);
		wind_obj_setflag(&daemon->obj,F_OBJ_ENABLE);
        return W_ERR_OK;
    }
    else if(wind_strcmp(argv[1],"disable") == 0)
    {
        WIND_ASSERT_RETURN(argc == 3,W_ERR_INVALID);
        daemon = wind_daemon_get(argv[2]);
        WIND_ASSERT_RETURN(daemon != W_NULL,W_ERR_INVALID);
		wind_obj_clrflag(&daemon->obj,F_OBJ_ENABLE);
        return W_ERR_OK;
    }
    return W_ERR_FAIL;
}

COMMAND_DEF(daemon);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
