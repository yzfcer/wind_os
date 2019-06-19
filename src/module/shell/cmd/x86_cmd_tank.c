/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: cmd_tank.c
** 创   建   人: Jason Zhou
** 最后修改日期: 2015/1/24 20:24:37
** 描        述: 坦克大战游戏
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
#include "wind_cmd.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************头文件定义***********************************************/

#if (CMD_ECHO_SUPPORT)

/********************************************内部变量定义**********************************************/




/********************************************内部函数定义*********************************************/



/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/
COMMAND_DISC(tank)
{
    wind_printf("to play tanks war game.\r\n");
}

COMMAND_USAGE(tank)
{
    wind_printf("tank:--to start tanks war game.\r\n");
}
extern int tank_main(int argc,char **argv);
COMMAND_MAIN(tank,argc,argv)
{
    char ch;
    tank_main(argc,argv);
    while(wind_std_input((w_uint8_t *)&ch,1));
    return W_ERR_OK;
}

COMMAND_DEF(tank);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
