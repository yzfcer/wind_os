#include "listfs.h"
#include "wind_conv.h"
#include "wind_heap.h"
#include "wind_debug.h"
#include "wind_string.h"
#include "wind_crc32.h"
#include "listfs_bitmap.h"
#if WIND_FS_SUPPORT


#define NODE_TO_LISTFILE(node) (listfile_s*)(((w_uint8_t*)(node))-((w_uint32_t)&(((listfile_s*)0)->tree.treenode)))
static listfile_s *listfile_rootnode = W_NULL;

void *listfs_malloc(w_int32_t size)
{
    void *ptr = wind_malloc(size);
    return ptr;
}

w_err_t listfs_free(void *ptr)
{
    if(ptr == W_NULL)
        return W_ERR_OK;
    return wind_free(ptr);
}

listfile_s *listfile_create(const char *path)
{
    return W_NULL;
}

w_err_t listfile_rm(listfile_s *file)
{
    return W_ERR_FAIL;
}

w_err_t listfs_format(w_blkdev_s *blkdev)
{
    w_int32_t i;
    w_uint32_t crc;
    lfs_info_s *lfs;
    w_uint8_t *blk;
    WIND_ASSERT_RETURN(blkdev != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(blkdev->obj.magic == WIND_BLKDEV_MAGIC,W_ERR_INVALID);
    blk = listfs_malloc(blkdev->blksize);
    WIND_ASSERT_RETURN(blk != W_NULL,W_ERR_MEM);
    wind_memset(blk,0,blkdev->blksize);
    lfs = (lfs_info_s*)blk;
    lfs->magic = LISTFS_MAGIC;
    lfs->blkcount = blkdev->blkcnt;
    lfs->unit_size = blkdev->blksize;
    lfs->blksize = blkdev->blksize;
    lfs->reserve_blk = 1;
    lfs->attr = 0;
    lfs->bitmap1 = lfs->reserve_blk + 1;
    lfs->bitmap_cnt = (blkdev->blkcnt - lfs->bitmap1) / (lfs->unit_size + 1) + 1;
    lfs->bitmap2 = lfs->bitmap1 + lfs->bitmap_cnt;
    lfs->root_addr = lfs->bitmap2 + lfs->bitmap_cnt;
    crc = wind_crc32(blk,blkdev->blksize-4,0xffffffff);
    wind_from_uint32(&blk[blkdev->blksize-4],crc);
    
    wind_blkdev_write(blkdev,0,blk,1);
    wind_memset(blk,0,blkdev->blksize);
    blk[0] = 1;
    wind_blkdev_write(blkdev,lfs->bitmap1,blk,1);
    wind_blkdev_write(blkdev,lfs->bitmap2,blk,1);
    blk[0] = 0;
    for(i = 1;i < lfs->bitmap_cnt; i ++)
        wind_blkdev_write(blkdev,lfs->bitmap1+i,blk,1);
    for(i = 1;i < lfs->bitmap_cnt; i ++)
        wind_blkdev_write(blkdev,lfs->bitmap2+i,blk,1);
    wind_printf("write root dir here\r\n");
    listfs_free(blk);
    return W_ERR_OK;
}

static w_err_t load_listfs(listfs_s *lfs,w_blkdev_s *blkdev)
{
    w_int32_t cnt;
    w_uint8_t *blk;
    lfs_info_s *info;
    w_uint32_t crc,calc_crc;
    blk = listfs_malloc(blkdev->blksize);
    WIND_ASSERT_RETURN(blk != W_NULL,W_ERR_MEM);
    wind_blkdev_read(blkdev,0,blk,1);
    WIND_ASSERT_TODO_RETURN(cnt > 0,listfs_free(blk),W_ERR_FAIL);
    info = (lfs_info_s*)blk;
    WIND_ASSERT_TODO_RETURN(info->magic == LISTFS_MAGIC,listfs_free(blk),W_ERR_FAIL);
    
    calc_crc = wind_crc32(blk,blkdev->blksize-4,0xffffffff);
    wind_to_uint32(&blk[blkdev->blksize-4],&crc);
    WIND_ASSERT_TODO_RETURN(calc_crc == crc,listfs_free(blk),W_ERR_CRC);
    wind_memcpy(&lfs->lfs_info,info,sizeof(lfs_info_s));
    listfs_free(blk);
    return W_ERR_OK;
}

w_err_t listfs_mount(listfs_s *lfs,w_blkdev_s *blkdev,const char *path)
{
    w_err_t err;
    w_int32_t len;
    WIND_ASSERT_RETURN(lfs != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(blkdev != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(path != W_NULL,W_ERR_PTR_NULL);
    len = wind_strlen(path);
    lfs->path = listfs_malloc(len+1);
    WIND_ASSERT_RETURN(lfs->path != W_NULL,W_ERR_MEM);
    wind_memcpy(lfs->path,path,len);
    lfs->path[len] = 0;
    lfs->blkdev = blkdev;
    err = load_listfs(lfs,blkdev);
    WIND_ASSERT_TODO_RETURN(err == W_ERR_OK,listfs_free(lfs->path),err);
        
    listfs_bitmap_init(lfs);
    return W_ERR_OK;
}

w_err_t listfs_unmount(listfs_s *lfs)
{
    WIND_ASSERT_RETURN(lfs != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(lfs->lfs_info.magic == LISTFS_MAGIC,W_ERR_INVALID);
    lfs->blkdev = W_NULL;
    if(lfs->path)
        listfs_free(lfs->path);
    lfs->lfs_info.magic = (~LISTFS_MAGIC);
    return W_ERR_OK;
}



listfile_s* listfile_open(listfs_s *lfs,const char *path,w_uint16_t mode)
{
    WIND_ASSERT_RETURN(lfs != W_NULL,W_NULL);
    WIND_ASSERT_RETURN(path != W_NULL,W_NULL);
    
    return W_NULL;
}

w_err_t listfile_close(listfile_s* file)
{
    return W_ERR_FAIL;
}

w_bool_t listfile_existing(const char *path)
{
    return W_FALSE;
}

w_err_t listfile_seek(listfile_s* file,w_int32_t offset)
{
    return W_ERR_FAIL;
}

w_int32_t listfile_ftell(listfile_s* file)
{
    return -1;
}

w_int32_t listfile_read(listfile_s* file,w_uint8_t *buff, w_int32_t size)
{
    return 0;
}

w_int32_t listfile_write(listfile_s* file,w_uint8_t *buff, w_int32_t size)
{
    return 0;
}

listfile_s *listfile_readdir(listfile_s* file,w_int32_t index)
{
    return W_NULL;
}


w_err_t listfile_fgets(listfile_s* file,char *buff, w_int32_t maxlen)
{
    return W_ERR_FAIL;
}
w_err_t listfile_fputs(listfile_s* file,char *buff)
{
    return W_ERR_FAIL;
}

#endif

