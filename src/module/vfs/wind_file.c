/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: wind_file.c
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
#include "wind_file.h"
#include "wind_fs.h"
#include "wind_pool.h"
#include "wind_debug.h"
#include "wind_mutex.h"
#include "wind_string.h"
#include "wind_heap.h"
#include "wind_core.h"
#include "wind_dlist.h"
#include "wind_board_port.h"

#if WIND_MODULE_VFS_SUPPORT
#define NODE_TO_FILE(dnode) (w_file_s*)(((w_uint8_t*)(dnode))-((w_uint32_t)&(((w_file_s*)0)->filenode)))
static w_dlist_s filelist;
WIND_POOL(filepool,WIND_FILE_MAX_NUM,sizeof(w_file_s));

static w_file_s *file_malloc(void)
{
    return wind_pool_malloc(filepool);
}

static w_err_t file_free(w_file_s *file)
{
    return wind_pool_free(filepool,file);
}

w_err_t _wind_file_mod_init(void)
{
    w_err_t err;
    DLIST_INIT(filelist);
    err = wind_pool_create("file",filepool,sizeof(filepool),sizeof(w_file_s));
    return err;
}


w_file_s *wind_file_get(w_vfs_s *fs,const char *path)
{
    w_file_s *file;
    w_dnode_s *dnode;
    wind_disable_switch();
    foreach_node(dnode,&filelist)
    {
        file = NODE_TO_FILE(dnode);
        if((wind_strcmp(path,file->path) == 0) &&
            (file->vfs == fs))
        {
            wind_enable_switch();
            return file;
        }
    }
    wind_enable_switch();
    return W_NULL;
}

w_bool_t wind_file_exist(const char *path)
{
    w_err_t err;
    w_file_s *file;
    w_uint32_t isdir;
    w_bool_t exist = W_FALSE;
    WIND_ASSERT_RETURN(path != W_NULL,W_FALSE);
    wind_debug("wind_file_exist:%s",path);
    err = wind_filepath_check_valid(path);
    WIND_ASSERT_RETURN(err == W_ERR_OK,W_FALSE);
    if(wind_file_get_bypath(path) != W_NULL)
        return W_TRUE;
    isdir = path[wind_strlen(path)-1]=='/'?1:0;
    file = wind_fopen(path,FMODE_R);
    if((file != W_NULL)&&(file->isdir==isdir))
    {
        exist = W_TRUE;
        wind_fclose(file);
    }
    return exist;
}

w_file_s *wind_file_get_bypath(const char *path)
{
    w_file_s *file;
    w_vfs_s *fs;
    w_int32_t len;
    WIND_ASSERT_RETURN(path != W_NULL,W_NULL);
    wind_debug("open file:%s",path);
    len = wind_strlen(path);
    WIND_ASSERT_RETURN(len > 0,W_NULL);
    fs = wind_vfs_get_bypath(path);
    if(fs == W_NULL)
    {
        wind_error("path:%s NOT exsit.",path);
        return W_NULL;
    }
    file = wind_file_get(fs,path);
    return file;

}

static w_file_s *wind_file_create(w_vfs_s *fs,const char *realpath,w_uint16_t fmode,w_uint8_t isdir)
{
    w_err_t err;
    w_int32_t realpathlen;
    w_file_s *file = W_NULL;
    do
    {
        err = W_ERR_OK;
        file = file_malloc();
        WIND_ASSERT_BREAK(file != W_NULL,W_ERR_MEM,"file_malloc failed");
        wind_memset(file,0,sizeof(w_file_s));
        file->mutex = W_NULL;
        file->path = W_NULL;
        file->mutex = wind_mutex_create(W_NULL);
        WIND_ASSERT_BREAK(file->mutex != W_NULL,W_ERR_MEM,"create mutex failed");

        realpathlen = wind_strlen(realpath);
        file->path = wind_malloc(realpathlen+1);
        WIND_ASSERT_BREAK(file->path != W_NULL,W_ERR_MEM,"malloc file path failed");
        wind_strcpy(file->path,realpath);
        file->path[realpathlen] = 0;
        file->filename = wind_filepath_get_filename(file->path);
        WIND_ASSERT_BREAK(file->filename != W_NULL,W_ERR_INVALID,"filename is invalid");
        file->subfile = W_NULL;
        DNODE_INIT(file->filenode);
        file->fmode = fmode;
        file->isdir = isdir;
        file->vfs = fs;
        file->fileobj = W_NULL;
        file->offset = 0;
        err = file->vfs->ops->open(file,file->fmode);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"open real file failed");
        wind_disable_switch();
        dlist_insert_tail(&filelist,&file->filenode);
        wind_enable_switch();
    }while(0);


    if(err != W_ERR_OK)
    {
        if(file->path != W_NULL)
            wind_free(file->path);
        if(file->filename != W_NULL)
            wind_free(file->filename);
        if(file->mutex != W_NULL)
            wind_mutex_destroy(file->mutex);
        file_free(file);
        file = W_NULL;
    }
    return file;
    
}

static w_err_t wind_file_destroy(w_file_s *file)
{
    WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(file->mutex != W_NULL,W_ERR_PTR_NULL);
    wind_disable_switch();
    dlist_remove(&filelist,&file->filenode);
    wind_enable_switch();
    if(file->path != W_NULL)
        wind_free(file->path);
    if(file->filename != W_NULL)
        wind_free(file->filename);
    if(file->mutex != W_NULL)
        wind_mutex_destroy(file->mutex);
    if(file->subfile != W_NULL)
        wind_file_destroy(file->subfile);
    file_free(file);
    return W_ERR_OK;
}

w_file_s* wind_fopen(const char *path,w_uint16_t fmode)
{
    w_err_t err;
    w_file_s *file;
    w_vfs_s *fs;
    w_uint8_t isdir;
    w_int32_t pathlen,len1;
    WIND_ASSERT_RETURN(path != W_NULL,W_NULL);
    err = wind_filepath_check_valid(path);
    WIND_ASSERT_RETURN(err == W_ERR_OK,W_NULL);
    wind_debug("open file:%s",path);
    file = wind_file_get_bypath(path);
    if(file != W_NULL)
    {
        wind_error("file has been opened.");
        return W_NULL;
    }
    
    pathlen = wind_strlen(path);
    WIND_ASSERT_RETURN(pathlen > 0,W_NULL);
    fs = wind_vfs_get_bypath(path);
    if(fs == W_NULL)
    {
        wind_error("path:%s NOT exsit.",path);
        return W_NULL;
    }
    len1 = wind_strlen(fs->mount_path);
    isdir = path[pathlen-1] == '/'?1:0;
    file = wind_file_create(fs,(const char*)&path[len1-1],fmode, isdir);
    return file;
}

w_err_t wind_fclose(w_file_s *file)
{
    w_err_t err = W_ERR_FAIL;
    WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
    wind_debug("close file:%s.",file->path);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->close)
        err = file->vfs->ops->close(file);
    wind_mutex_unlock(file->mutex);
    wind_file_destroy(file);
    return err;
}

w_err_t wind_fremove(const char *path)
{
    w_err_t err = W_ERR_FAIL;
    w_file_s *file;
    err = wind_filepath_check_valid(path);
    WIND_ASSERT_RETURN(err == W_ERR_OK,err);
    file = wind_file_get_bypath(path);
    if(file == W_NULL)
        file = wind_fopen(path,FMODE_R);
    if(file == W_NULL)
    {
        wind_warn("file %s is NOT exist.",path);
        return W_ERR_OK;
    }
    if(wind_strcmp(path,file->vfs->mount_path) == 0)
    {
        wind_error("can not remove fs \"%s\" root directory",wind_obj_name(&file->vfs->obj));
        wind_fclose(file);
        return W_ERR_FAIL;
    }
    
    if(file->vfs->ops->close)
        file->vfs->ops->close(file);

    wind_debug("remove file:%s",file->path);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->remove)
        file->vfs->ops->remove(file);
    wind_mutex_unlock(file->mutex);
    wind_file_destroy(file);
    return W_ERR_OK;
}

w_err_t wind_fsub(w_file_s *dir,w_file_s *sub)
{
    w_err_t err = W_ERR_FAIL;
    WIND_ASSERT_RETURN(dir != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(sub != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(dir->isdir != 0,W_ERR_INVALID);
    if(dir->subfile == W_NULL)
    {
        wind_memset(sub,0,sizeof(w_file_s));
    }
        
    wind_debug("get subfile of %s",dir->path);
    wind_mutex_lock(dir->mutex);
    if(dir->vfs->ops->subfile)
        err = dir->vfs->ops->subfile(dir,sub);
    wind_mutex_unlock(dir->mutex);
    return err;
}

w_err_t wind_fseek(w_file_s *file,w_int32_t offset)
{
    w_err_t err = W_ERR_FAIL;
    WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(offset >= 0,W_ERR_INVALID);
    WIND_ASSERT_RETURN(!file->isdir,W_ERR_INVALID);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->seek)
        err = file->vfs->ops->seek(file,offset);
    if(err == W_ERR_OK)
        file->offset = offset;
    wind_mutex_unlock(file->mutex);
    return err;
}
    
w_err_t wind_frename(w_file_s *file,char *newname)
{
    w_err_t err = W_ERR_FAIL;
    WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(newname != W_NULL,W_ERR_PTR_NULL);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->rename)
        err = file->vfs->ops->rename(file,newname);
    wind_mutex_unlock(file->mutex);
    return err;
}

w_int32_t wind_ftell(w_file_s *file)
{
    w_int32_t offset = -1;
    WIND_ASSERT_RETURN(file != W_NULL,-1);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->ftell)
        offset = file->vfs->ops->ftell(file);
    wind_mutex_unlock(file->mutex);
    return offset;
}

w_int32_t wind_fread(w_file_s *file,w_uint8_t *buff, w_int32_t size)
{
    w_int32_t len = -1;
    WIND_ASSERT_RETURN(file != W_NULL,-1);
    WIND_ASSERT_RETURN(buff != W_NULL,-2);
    WIND_ASSERT_RETURN(size > 0,-3);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->read)
        len = file->vfs->ops->read(file,buff,size);
    wind_mutex_unlock(file->mutex);
    return len;
}

w_int32_t wind_fwrite(w_file_s *file,w_uint8_t *buff, w_int32_t size)
{
    w_int32_t len = -1;
    WIND_ASSERT_RETURN(file != W_NULL,-1);
    WIND_ASSERT_RETURN(buff != W_NULL,-2);
    WIND_ASSERT_RETURN(size > 0,-3);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->write)
        len = file->vfs->ops->write(file,buff,size);
    wind_mutex_unlock(file->mutex);
    return len;
}

w_err_t wind_fgets(w_file_s *file,char *buff, w_int32_t maxlen)
{
    w_int32_t len = -1;
    WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(buff != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(maxlen > 0,W_ERR_INVALID);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->fgets)
        len = file->vfs->ops->fgets(file,buff,maxlen);
    wind_mutex_unlock(file->mutex);
    return len > 0?W_ERR_OK:W_ERR_FAIL;
}

w_err_t wind_fputs(w_file_s *file,char *buff)
{
    w_int32_t len = -1;
    WIND_ASSERT_RETURN(file != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(buff != W_NULL,W_ERR_PTR_NULL);
    wind_mutex_lock(file->mutex);
    if(file->vfs->ops->fputs)
        len = file->vfs->ops->fputs(file,buff);
    wind_mutex_unlock(file->mutex);
    return len > 0?W_ERR_OK:W_ERR_FAIL;
}

#endif
