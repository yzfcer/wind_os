/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_fs.c
**创   建   人: Jason Zhou
**最后修改日期: 
**描        述: 文件系统标准化API接口
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 
** 版  本: v1.0
** 日　期: 
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_config.h"
#include "wind_fs.h"
#include "wind_fsops.h"
#include "wind_file.h"
#include "wind_pool.h"
#include "wind_debug.h"
#include "wind_mutex.h"
#include "wind_string.h"
#include "wind_heap.h"
#include "wind_core.h"
#include "wind_dlist.h"
#include "wind_fsops.h"
#include "wind_dbgpoint.h"
#include "wind_board_port.h"
#include "treefs.h"

#if WIND_MODULE_VFS_SUPPORT
#define NODE_TO_FS(dnode) (w_vfs_s*)(((w_uint8_t*)(dnode))-((w_addr_t)&(((w_vfs_s*)0)->obj.objnode)))

static w_dlist_s fslist;
static char *fsname[] = {"fs0","fs1","fs2","fs3","fs4"};
WIND_POOL(fspool,WIND_FS_MAX_NUM,sizeof(w_vfs_s));


w_vfs_s *wind_vfs_obj_init(char *name)
{
    w_err_t err;
    w_vfs_s *vfs;
    WIND_ASSERT_RETURN(name != W_NULL,W_NULL);
    vfs = wind_pool_malloc(fspool);
    WIND_ASSERT_RETURN(vfs != W_NULL,W_NULL);
    wind_memset(vfs,0,sizeof(w_vfs_s));
    err = wind_obj_init(&vfs->obj,WIND_VFS_MAGIC,name,&fslist);
    WIND_ASSERT_RETURN(err == W_ERR_OK,W_NULL);
    return vfs;    
}


static w_err_t vfs_all_vfs_objs_init(void)
{
    w_int32_t i;
    w_vfs_s *vfs;
    WIND_ASSERT_RETURN(sizeof(fsname)/sizeof(char *) >=  WIND_FS_MAX_NUM,W_ERR_FAIL);
    for(i = 0;i < WIND_FS_MAX_NUM;i ++)
    {
        vfs = wind_vfs_obj_init(fsname[i]);
    }
    return W_ERR_OK;
}

static w_bool_t is_dev_match(w_vfs_s *vfs,char *blkdev_name)
{
    if((vfs->blkdev != W_NULL) && 
        (vfs->blkdev->obj.name != W_NULL) && 
        (wind_strcmp(blkdev_name,vfs->blkdev->obj.name) == 0))
        return W_TRUE;
    return W_FALSE;
}

static w_err_t check_dir_path_valid(char *path)
{
    w_err_t err;
    w_file_s *file = W_NULL;
    do
    {
        err = W_ERR_OK;
        if((path[0] == '/') && (path[1] == 0))
            break;
        file = wind_fopen(path,FMODE_R);
        WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
        WIND_ASSERT_RETURN(file->isdir != 0,W_ERR_FAIL);        
    }while(0);
    if(file != W_NULL)
        wind_fclose(file);
    return  err;
}

static w_err_t mount_param_check(char *fsname,char *fstype,char *blkname,char *path)
{
    w_vfs_s *vfs;
    w_fsops_s *ops;
    w_dnode_s *dnode;
    w_int32_t len;
    w_bool_t is_match;
    w_err_t err;
    WIND_ASSERT_RETURN(fsname != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(fstype != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(blkname != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(path != W_NULL,W_ERR_PTR_NULL);
    vfs = wind_vfs_get(fsname);
    WIND_ASSERT_RETURN(vfs != W_NULL,W_ERR_REPEAT);
    ops = wind_fsops_get(fstype);
    WIND_ASSERT_RETURN(vfs != W_NULL,W_ERR_REPEAT);
    len = wind_strlen(path);
    WIND_ASSERT_MSG_RETURN(len < FS_MOUNT_PATH_LEN,W_ERR_INVALID,"mount path is too long");
    err = check_dir_path_valid(path);
    WIND_ASSERT_MSG_RETURN(err == W_ERR_OK,W_ERR_INVALID,"dir path is invalid");
    len = wind_strlen(fsname);
    WIND_ASSERT_MSG_RETURN(len < WFS_NAME_LEN,W_ERR_INVALID,"vfs name is too long");

    
    foreach_node(dnode,&fslist)
    {
        vfs = NODE_TO_FS(dnode);
        is_match = ((vfs->mount_path != 0)&&(wind_strcmp(path,vfs->mount_path) == 0));
        WIND_ASSERT_MSG_RETURN(!is_match,W_ERR_REPEAT,"mount path %s has been used",path);
        if(blkname == W_NULL)
            continue;
        is_match = is_dev_match(vfs,blkname);
        WIND_ASSERT_MSG_RETURN(!is_match,W_ERR_REPEAT,"block device %s has been used",blkname);
    }
    return W_ERR_OK;
}


w_err_t _wind_vfs_mod_init(void)
{
    w_err_t err;
    DLIST_INIT(fslist);
    err = wind_pool_create("vfs",fspool,sizeof(fspool),sizeof(w_vfs_s));
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
    err = vfs_all_vfs_objs_init();
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
    
    _wind_file_mod_init();
    wind_fsops_init();
    
    _wind_fs_mount_init();
    wind_filepath_set_current(FS_CUR_PATH);
    _wind_vfs_register_fs_cmd();
    return W_ERR_OK;
}

w_vfs_s *wind_vfs_get(char *name)
{
    return (w_vfs_s *)wind_obj_get(name,&fslist);
}

w_vfs_s *wind_vfs_get_free(void)
{
    w_vfs_s *vfs,*retfs = W_NULL;
    w_dnode_s *dnode;
    wind_disable_switch();
    foreach_node(dnode,&fslist)
    {
        vfs = NODE_TO_FS(dnode);
        if(!IS_F_VFS_MOUNT(vfs))
        {
            retfs = vfs;
            break;
        }
    }
    wind_enable_switch();
    return retfs;
}

w_vfs_s *wind_vfs_get_byidx(w_int32_t index)
{
    WIND_ASSERT_RETURN(index < WIND_FS_MAX_NUM,W_NULL);
    WIND_ASSERT_RETURN(index >= 0,W_NULL);
    return wind_vfs_get(fsname[index]);    
}



w_vfs_s *wind_vfs_get_bypath(const char *path)
{
    w_vfs_s *vfs,*retfs = W_NULL;
    w_dnode_s *dnode;
    w_int32_t len;
    wind_disable_switch();
    foreach_node(dnode,&fslist)
    {
        vfs = NODE_TO_FS(dnode);
        if(!IS_F_VFS_MOUNT(vfs))
            continue;
        len = wind_strlen(vfs->mount_path);
        if(wind_memcmp(path,vfs->mount_path,len) == 0)
        {
            if((retfs == W_NULL)||(wind_strlen(retfs->mount_path) < len))
                retfs = vfs;
        }
    }
    wind_enable_switch();
    return retfs;
}

w_err_t wind_vfs_print(void)
{
    w_dnode_s *dnode;
    w_vfs_s *vfs;
    w_dlist_s *list = &fslist;
    wind_printf("\r\n\r\nfs mount list:\r\n");
    wind_disable_switch();
    foreach_node(dnode,list)
    {
        vfs = NODE_TO_FS(dnode);
        
        wind_printf("mount %s ",wind_obj_name(&vfs->obj));
        wind_printf("%s ",vfs->fstype?vfs->fstype:"    ");
        if(wind_strcmp(vfs->fstype,"hostfs") != 0)
            wind_printf("%s ",vfs->blkdev?wind_obj_name(&vfs->blkdev->obj):"    ");
        else
            wind_printf("%s ",vfs->usr_arg?(char*)vfs->usr_arg:"    ");
        wind_printf("%s\r\n",vfs->mount_path?vfs->mount_path:"    ");
    }
    wind_enable_switch();
    return W_ERR_OK;
}


w_err_t wind_vfs_mount(char *fsname,char *fstype,char *blkname,char *path)
{
    w_err_t err;
    w_blkdev_s *blkdev;
    w_vfs_s *vfs;
    w_int32_t len;
    w_fsops_s *ops;
    wind_notice("mount %s type %s dev %s path %s",fsname,fstype,blkname,path);
    err = mount_param_check(fsname,fstype,blkname,path);
    WIND_ASSERT_RETURN(err == W_ERR_OK,W_ERR_INVALID);
    do
    {
        err = W_ERR_OK;
        vfs = wind_vfs_get(fsname);
        WIND_ASSERT_BREAK(vfs != W_NULL,W_ERR_MEM,"vfs is NOT exist");
        WIND_ASSERT_BREAK(!IS_F_VFS_MOUNT(vfs),W_ERR_INVALID,"vfs has been mounted");
        ops = wind_fsops_get(fstype);
        WIND_ASSERT_BREAK(ops != W_NULL,W_ERR_MEM,"ops is NOT exist");
        blkdev = wind_blkdev_get(blkname);
        //WIND_ASSERT_BREAK(blkdev != W_NULL,W_ERR_MEM,"blkdev is NOT exist");
        if(wind_strcmp(fstype,"hostfs") == 0)
        {
            vfs->usr_arg = wind_salloc(blkname,HP_ALLOCID_VFS);
            WIND_ASSERT_BREAK(vfs->usr_arg != W_NULL,W_ERR_MEM,"malloc usr_arg failed");
        }
        
        //len = wind_strlen(path)+1;
        //vfs->mount_path = wind_alloc(len,HP_ALLOCID_VFS);
        //WIND_ASSERT_BREAK(vfs->mount_path != W_NULL,W_ERR_MEM,"malloc mount_path failed");
        //wind_strcpy(vfs->mount_path,path);
        vfs->mount_path = wind_filepath_to_directory(path);
        WIND_ASSERT_BREAK(vfs->mount_path != W_NULL,W_ERR_MEM,"malloc mount_path failed");

        len = wind_strlen(fstype)+1;
        vfs->fstype = wind_alloc(len,HP_ALLOCID_VFS);

        WIND_ASSERT_BREAK(vfs->fstype != W_NULL,W_ERR_MEM,"malloc fstype failed");
        wind_strcpy(vfs->fstype,fstype);
        
        vfs->fsobj = W_NULL;
        vfs->blkdev = blkdev;
        vfs->ops = ops;
        if(vfs->ops->init)
            vfs->fsobj = vfs->ops->init(vfs);
        else
            break;
        if(vfs->fsobj == W_NULL)
        {
            wind_error("init vfs %s failed", wind_obj_name(&vfs->obj));
            if(vfs->ops->format != W_NULL)
            {
                err = vfs->ops->format(vfs);
                WIND_ASSERT_BREAK(err == W_ERR_OK,err,"vfs format failed");
                if(vfs->ops->init)
                    vfs->fsobj = vfs->ops->init(vfs);
                WIND_ASSERT_BREAK(vfs->fsobj != W_NULL, W_ERR_FAIL, "vfs error");
            }
        }
        
        SET_F_VFS_MOUNT(vfs);
    }while(0);
    if(err != W_ERR_OK)
        wind_vfs_unmount(fsname);
    return err;
}

w_err_t wind_vfs_unmount(char *fsname)
{
    w_vfs_s *vfs;
    WIND_ASSERT_RETURN(fsname != W_NULL,W_ERR_PTR_NULL);
    vfs = wind_vfs_get(fsname);
    WIND_ASSERT_RETURN(vfs != W_NULL,W_ERR_INVALID);
    wind_notice("umount %s",fsname);
    CLR_F_VFS_MOUNT(vfs);
    if(vfs->mount_path != W_NULL)
        wind_free(vfs->mount_path);
    vfs->mount_path = W_NULL;
    if(vfs->fstype != W_NULL)
        wind_free(vfs->fstype);
    vfs->fstype = W_NULL;
    if(vfs->usr_arg != W_NULL)
        wind_free(vfs->usr_arg);
    vfs->usr_arg = W_NULL;
    vfs->blkdev = W_NULL;
    vfs->ops = W_NULL;
    return W_ERR_OK;
}

w_err_t wind_vfs_format(w_vfs_s *vfs)
{
    w_err_t err = W_ERR_OK;
    WIND_ASSERT_RETURN(vfs != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(vfs->ops != W_NULL,W_ERR_PTR_NULL);
    if(vfs->ops->format != W_NULL)
        err = vfs->ops->format(vfs);
    return err;
}

#endif
