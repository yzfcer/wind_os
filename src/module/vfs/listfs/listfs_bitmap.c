/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: listfs_bitmap.c
**创   建   人: Jason Zhou
**最后修改日期: 2019.04.05
**描        述: 文件系统对块位图的操作接口
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2019.04.05
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: Jason Zhou
** 日　期: 2019.04.05
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "listfs.h"
#include "listfs_bitmap.h"
#include "wind_tree.h"
#include "wind_heap.h"
#include "wind_debug.h"
#include "wind_string.h"
#if WIND_FS_SUPPORT

static w_int32_t bm_get_free_byteidx(w_uint8_t *blk,w_int32_t blksize)
{
    w_int32_t i,j,cnt;
    w_uint32_t *ptr;
    ptr = (w_uint32_t *)blk;
    cnt = (blksize >> 2);
    for(i = 0;i < cnt;i ++)
    {
        if(ptr[i] != 0x01010101)
        {
            blk = (w_uint8_t *)&ptr[i];
            for(j = 0;j < 4;j ++)
                if(blk[i] == 0)
                    return (i << 4);
        }
    }
    return -1;
}

static w_int32_t bm_alloc_blk(lfs_bitmap_s *bm,w_addr_t *addr,w_int32_t cnt)
{
    w_int32_t i;
    w_int32_t alloc_cnt = 0;
    
    for(i = bm->cur_byteidx;i < bm->blkdev->blksize;i ++)
    {
        if(bm->blk[i] == 0)
        {
            addr[alloc_cnt] = bm->data_addr + (bm->cur_blkidx*bm->blkdev->blksize) + bm->cur_byteidx;
            bm->blk[i] = BITMAP_USED;
            alloc_cnt ++;
            if(alloc_cnt >= cnt)
                break;
        }
    }
    return alloc_cnt;
}

static w_int32_t bm_free_blk(lfs_bitmap_s *bm,w_addr_t *addr,w_int32_t cnt)
{
    w_int32_t i,free_cnt = 0;
    w_int32_t byteidx;
    
    for(i = 0;i < cnt;i ++)
    {
        byteidx = addr[i] - bm->data_addr - (bm->cur_blkidx*bm->blkdev->blksize);
        if((byteidx >= 0)&&(byteidx < bm->blkdev->blksize))
        {
            addr[i] = 0;
            bm->blk[byteidx] = 0;
            free_cnt ++;
        }
    }
    return free_cnt;
}

static w_err_t bm_read_blk(lfs_bitmap_s *bm)
{
    w_int32_t cnt;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->cur_blkidx >= 0,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->cur_blkidx < bm->bmblk_cnt,W_ERR_INVALID);
    
    cnt = wind_blkdev_read(bm->blkdev,bm->addr1 + bm->cur_blkidx,bm->blk,1);
    if(cnt != 1)
        cnt = wind_blkdev_read(bm->blkdev,bm->addr2 + bm->cur_blkidx,bm->blk,1);
    WIND_ASSERT_RETURN(cnt == 1,W_ERR_HARDFAULT);
    return W_ERR_OK;
}

static w_err_t bm_write_blk(lfs_bitmap_s *bm)
{
    w_int32_t cnt;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->cur_blkidx >= 0,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->cur_blkidx < bm->bmblk_cnt,W_ERR_INVALID);
    
    cnt = wind_blkdev_write(bm->blkdev,bm->addr1 + bm->cur_blkidx,bm->blk,1);
    WIND_ASSERT_RETURN(cnt > 0,W_ERR_HARDFAULT);
    cnt = wind_blkdev_write(bm->blkdev,bm->addr2 + bm->cur_blkidx,bm->blk,1);
    WIND_ASSERT_RETURN(cnt > 0,W_ERR_HARDFAULT);
    return W_ERR_OK;
}


static w_err_t bm_check_free_bitmap(lfs_bitmap_s *bm)
{
    w_int32_t byteidx;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_PTR_NULL);
    byteidx = bm_get_free_byteidx(bm->blk,bm->blkdev->blksize);
    if(byteidx >= 0)
    {
        bm->cur_byteidx = byteidx;
        wind_notice("set free bitmap:%d,%d",bm->cur_blkidx,bm->cur_byteidx);
        return W_ERR_OK;
    }
    return W_ERR_FAIL;
}


w_err_t listfs_bitmap_init(lfs_bitmap_s *bm,w_addr_t start_addr,w_int32_t blk_cnt,w_blkdev_s *blkdev)
{
    w_err_t err;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(blkdev != W_NULL,W_ERR_PTR_NULL);
    wind_notice("listfs_bitmap_init,blkdev:%s",wind_obj_name(&blkdev->obj));
    do
    {
        err = W_ERR_OK;
        bm->magic = LISTFS_BITMAP_MAGIC;
        bm->addr1 = start_addr;
        bm->addr2 = start_addr + blk_cnt;
        bm->bmblk_cnt = blk_cnt;
        bm->data_addr = bm->addr2 + blk_cnt;
        bm->cur_blkidx = 0;
        bm->cur_byteidx = 0;
        bm->blkdev = blkdev;
        bm->blk = lfs_malloc(blkdev->blksize);
        WIND_ASSERT_BREAK(bm->blk != W_NULL,W_ERR_MEM,"malloc blk failed");
        err = bm_read_blk(bm);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"read blk failed");
    }while(0);
    
    if(err != W_ERR_OK)
    {
        bm->magic = 0;
        if(bm->blk != W_NULL)
            lfs_free(bm->blk);
    }
    return err;
}

w_err_t listfs_bitmap_deinit(lfs_bitmap_s *bm)
{
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    bm->magic = 0;
    bm->bmblk_cnt = 0;
    if(bm->blk != W_NULL)
    {
        lfs_free(bm->blk);
        bm->blk = W_NULL;
    }
    return W_ERR_OK;
}



w_err_t listfs_bitmap_update_freeidx(lfs_bitmap_s *bm)
{
    w_uint32_t i;
    w_err_t err;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_INVALID);
    for(i = 0;i < bm->bmblk_cnt;i ++)
    {
        err = bm_check_free_bitmap(bm,i);
        if(err == W_ERR_OK)
            return err;
        bm->cur_blkidx ++;
        if(bm->cur_blkidx >= bm->bmblk_cnt)
            bm->cur_blkidx = 0;
        err = bm_read_blk(bm);
        WIND_ASSERT_BREAK(err == W_ERR_OK,W_ERR_HARDFAULT,"read blk failed");
    }

    bm->cur_blkidx = 0;
    bm->cur_byteidx = 0;
    wind_notice("set free bitmap failed");
    return W_ERR_FAIL;
}

#if 0
w_err_t listfs_bitmap_set(lfs_bitmap_s *bm,w_addr_t addr,w_uint8_t bitflag)
{
    w_int32_t byte_idx;
    w_uint8_t *blk = W_NULL;
    w_addr_t addr_idx,addr_start;
    
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_PTR_NULL);
    addr_start = bm->addr2 + bm->bmblk_cnt;
    WIND_ASSERT_RETURN(addr >= addr_start,W_ERR_INVALID);
    addr_idx = (addr - addr_start) / bm->blkdev->blksize;
    byte_idx = addr % bm->blkdev->blksize;
    blk = lfs_malloc(bm->blkdev->blksize);
    WIND_ASSERT_RETURN(blk != W_NULL,W_ERR_MEM);
    
    wind_blkdev_read(bm->blkdev,bm->addr1+addr_idx,blk,1);
    blk[byte_idx] = bitflag;
    wind_blkdev_write(bm->blkdev,bm->addr1+addr_idx,blk,1);
    wind_blkdev_write(bm->blkdev,bm->addr2+addr_idx,blk,1);
    lfs_free(blk);
    return W_ERR_OK;
}
#endif

w_err_t listfs_bitmap_alloc_blk(lfs_bitmap_s *bm,w_addr_t *addr,w_int32_t addr_cnt)
{
    w_int32_t i,cnt,alloc_cnt;
    w_err_t err;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(addr != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(addr_cnt > 0,W_ERR_OVERFLOW);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_PTR_NULL);
    
    if((bm->cur_blkidx == 0) && (bm->cur_byteidx == 0))
        listfs_bitmap_update_freeidx(bm);
    wind_memset(addr,0,sizeof(w_addr_t)*addr_cnt);
    alloc_cnt = 0;
    err = W_ERR_OK;
    //此处应该优化，可以记录当前已经分配的数据块，这样就可以提前分析是否有足够的数据块供分配
    for(i = 0;i < bm->bmblk_cnt;i ++)
    {
        err = bm_read_blk(bm);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"read bitmap failed");
        cnt = bm_alloc_blk(bm,&addr[alloc_cnt],addr_cnt - alloc_cnt);
        if(cnt > 0)
        {
            bm_write_blk(bm);
            alloc_cnt += cnt;
            if(alloc_cnt >= addr_cnt)
                break;
        }
        bm->cur_blkidx ++;
        if(bm->cur_blkidx >= bm->bmblk_cnt)
            bm->cur_blkidx = 0;
    }
    
    if((err != W_ERR_OK) || (alloc_cnt < addr_cnt))
    {
        listfs_bitmap_free_blk(bm,addr,addr_cnt);
        return W_ERR_FAIL;
    }
    return W_ERR_OK;
}

w_err_t listfs_bitmap_free_blk(lfs_bitmap_s *bm,w_addr_t *addr,w_int32_t addr_cnt)
{
    w_int32_t i,cnt,free_cnt;
    w_err_t err;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(addr != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(addr_cnt > 0,W_ERR_OVERFLOW);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_PTR_NULL);
    
    err = W_ERR_OK;
    free_cnt = 0;
    for(i = 0;i < addr_cnt;i ++)
    {
        if(addr[i] != 0)
        {
            err = bm_read_blk(bm);
            WIND_ASSERT_BREAK(err == W_ERR_OK,err,"read bitmap failed");
            cnt = bm_free_blk(bm->blk,&addr[i],addr_cnt - i);
            if(cnt > 0)
            {
                free_cnt += cnt;
                bm_write_blk(bm);
                if(free_cnt >= addr_cnt)
                    break;
            }
        }
    }
    return err;
}


w_err_t listfs_bitmap_clear(lfs_bitmap_s *bm)
{
    w_int32_t i;
    w_blkdev_s *blkdev;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_PTR_NULL);
    wind_notice("listfs_bitmap_clear");
    blkdev = bm->blkdev;
    wind_memset(bm->blk,0,blkdev->blksize);
    for(i = 1;i < bm->bmblk_cnt; i ++)
        wind_blkdev_write(blkdev,bm->addr1+i,bm->blk,1);
    for(i = 1;i < bm->bmblk_cnt; i ++)
        wind_blkdev_write(blkdev,bm->addr2+i,bm->blk,1);
    bm->cur_blkidx = 0;
    bm->cur_byteidx = 0;
    return W_ERR_OK;
}

static w_uint32_t bm_calc_blkused(w_uint8_t *blk,w_int32_t blksize)
{
    w_int32_t i;
    w_uint32_t blkused = 0;
    for(i = 0;i < blksize;i ++)
    {
        if(blk[i] != 0)
            blkused ++;
    }
    return blkused;
}

w_int32_t listfs_bitmap_calc_usedblk(lfs_bitmap_s *bm)
{
    w_int32_t i,cnt;
    w_uint8_t *blk = W_NULL;
    w_blkdev_s *blkdev;
    w_uint32_t blkused = 0;
    WIND_ASSERT_RETURN(bm != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(bm->magic == LISTFS_BITMAP_MAGIC,W_ERR_INVALID);
    WIND_ASSERT_RETURN(bm->blkdev != W_NULL,W_ERR_PTR_NULL);
    blkdev = bm->blkdev;
    blk = lfs_malloc(blkdev->blksize);
    WIND_ASSERT_RETURN(blk != W_NULL,W_ERR_MEM);
    for(i = 1;i < bm->bmblk_cnt; i ++)
    {
        cnt = wind_blkdev_read(blkdev,bm->addr1+1,blk,1);
        WIND_ASSERT_TODO_RETURN(cnt == 1,lfs_free(blk),0xffffffff);
        blkused += bm_calc_blkused(blk,blkdev->blksize);
    }
    return blkused;    
}

#endif

