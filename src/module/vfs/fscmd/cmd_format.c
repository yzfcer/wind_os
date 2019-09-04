/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: cmd_format.c
** 创   建   人: Jason Zhou
** 最后修改日期: 2018/5/13 20:24:37
** 描        述: 文件系统格式化命令
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2018/5/13 20:24:37
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
//#include "wind_heap.h"
//#include "wind_string.h"
#include "wind_fs.h"
#include "wind_fsops.h"
#include "wind_blkdev.h"


#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************头文件定义***********************************************/

#if (CMD_FS_SUPPORT)
#include "wind_file.h"
/********************************************内部变量定义**********************************************/


/********************************************内部函数定义*********************************************/

static w_err_t cmd_format(w_int32_t argc,char **argv)
{
    w_err_t err;
    w_fsops_s *ops;
    w_vfs_s *vfs;
    w_blkdev_s *blkdev;
    do
    {
        err = W_ERR_OK;
        ops = wind_fsops_get(argv[2]);
        WIND_ASSERT_BREAK(ops != W_NULL,W_ERR_INVALID,"get fstype failed");
        WIND_ASSERT_BREAK(ops->format != W_NULL,W_ERR_INVALID,"can not format fs");
        vfs = wind_vfs_get_free();
        WIND_ASSERT_BREAK(ops != W_NULL,W_ERR_INVALID,"get fsobj failed");
        blkdev = wind_blkdev_get(argv[1]);
        WIND_ASSERT_BREAK(blkdev != W_NULL,W_ERR_INVALID,"blkdev is not exist");
        err = wind_blkdev_open(blkdev);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"open blkdev failed");
        vfs->blkdev = blkdev;
        err = ops->format(vfs);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"format fs failed");
        wind_blkdev_close(blkdev);
    }while(0);
    if(blkdev && IS_F_BLKDEV_OPEN(blkdev))
        wind_blkdev_close(blkdev);
    return err;
}

/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/
COMMAND_DISC(format)
{
    wind_printf("to format file system.\r\n");
}

COMMAND_USAGE(format)
{
    wind_printf("format <dev> <fstype>:--to format  a file system.\r\n");
    wind_printf("     fstype : file system type,should be treefs or listfs.\r\n");
    wind_printf("     blkdev : block device name,can find it as command \"list blkdev\".\r\n");
}

COMMAND_MAIN(format,argc,argv)
{
    WIND_ASSERT_RETURN(argc >= 3,W_ERR_INVALID);
    if(wind_strcmp(argv[0],"format") == 0)
        return cmd_format(argc,argv);
    return W_ERR_OK;
}

COMMAND_DEF(format);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
