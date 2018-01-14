/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: console_framework.h
**创   建   人: 周江村
**最后修改日期: 2012.09.26
**描        述: 系统的控制台入口
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2013.06.26
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 周江村
** 日　期: 2012.06.26
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

#ifndef WIND_CONSOLE_H__
#define WIND_CONSOLE_H__
#include "wind_config.h"
#include "wind_type.h"
#include "wind_debug.h"
#include "console_framework.h"
#ifdef __cplusplus
extern "C" {
#endif

#define console_printf(fmt,...) wind_printf(fmt,##__VA_ARGS__)

#define COMMAND_DISC(cmdname) static void cmd_##cmdname##_disc(void)
#define COMMAND_USAGE(cmdname) static void cmd_##cmdname##_help(void)
#define COMMAND_MAIN(cmdname,argc,argv) static w_err_t cmd_##cmdname##_main(w_int32_t argc,char **argv)
#define COMMAND_DEF(cmdname) cmd_s g_cmd_##cmdname = { \
NULL,#cmdname,cmd_##cmdname##_disc,\
cmd_##cmdname##_help,cmd_##cmdname##_main}

#define CMD_DECLARE(cmdname) extern cmd_s g_cmd_##cmdname
#define COMMAND(cmdname) &g_cmd_##cmdname




#endif//ifndef WIND_CONSOLE_H__
#ifdef __cplusplus
}
#endif

