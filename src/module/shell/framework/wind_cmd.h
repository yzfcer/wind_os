/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: wind_cmd.h
** 创   建   人: Jason Zhou
** 最后修改日期: 2015/1/24 20:24:37
** 描        述: 提供给命令对象使用的符号定义
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

#ifndef WIND_CONSOLE_H__
#define WIND_CONSOLE_H__
#include "wind_config.h"
#include "wind_type.h"
#include "wind_debug.h"
#include "shell_framework.h"
#if WIND_MODULE_SHELL_SUPPORT
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char *keyword;
    w_err_t (*exec)(w_int32_t argc,char **argv);
}w_cmd_handle_s;

#define COMMAND_DISC(cmdname) static void cmd_##cmdname##_disc(void)
#define COMMAND_USAGE(cmdname) static void cmd_##cmdname##_help(void)
#define COMMAND_MAIN(cmdname,argc,argv) static w_err_t cmd_##cmdname##_main(w_int32_t argc,char **argv)
#define COMMAND_DEF(cmdname) w_cmd_s g_cmd_##cmdname = { \
{W_NULL,W_NULL},#cmdname,cmd_##cmdname##_disc,\
cmd_##cmdname##_help,cmd_##cmdname##_main}

#define COMMAND_DECLARE(cmdname) extern w_cmd_s g_cmd_##cmdname
#define COMMAND(cmdname) &g_cmd_##cmdname

#ifdef __cplusplus
}
#endif
#endif
#endif//ifndef WIND_CONSOLE_H__

