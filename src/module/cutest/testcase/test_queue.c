/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: test_queue.c
** 创   建   人: Jason Zhou
** 最后修改日期: 2018/01/09 16:29:55
** 描        述: FIFO队列单元测试
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2017/10/22 16:29:55
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
/*********************************************头文件定义***********************************************/
#include "wind_cut.h"
#include "wind_queue.h"
#include "wind_string.h"
#include "wind_queue.h"
#if (WIND_CUTEST_SUPPORT && TEST_QUEUE_SUPPORT)
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/********************************************内部变量定义**********************************************/

w_uint8_t queuebuf[128];


/********************************************内部函数定义*********************************************/



/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/


CASE_SETUP(queueinfo)
{

}

CASE_TEARDOWN(queueinfo)
{

}

CASE_FUNC(queueinfo)
{
    w_err_t err;
    w_queue_s *q = (w_queue_s *)queuebuf;
    err = wind_queue_create(queuebuf,sizeof(queuebuf),sizeof(w_int32_t));
    EXPECT_NE(err,W_ERR_OK);
    EXPECT_EQ(q->magic,WIND_QUEUE_MAGIC);
    EXPECT_EQ(q->rd,q->buf);
    EXPECT_EQ(q->wr,q->buf);
    EXPECT_EQ(q->itemsize,sizeof(w_int32_t));
    EXPECT_EQ(q->count,0);
    EXPECT_EQ(q->capacity,(sizeof(queuebuf) - (w_uint32_t)(((w_queue_s *)0)->buf)) / q->itemsize);
    EXPECT_EQ(q->end,q->buf + q->capacity * q->itemsize);
    err = wind_queue_destory(q);
    EXPECT_EQ(W_ERR_OK,err);

}

CASE_SETUP(queuefunc)
{

}

CASE_TEARDOWN(queuefunc)
{

}

CASE_FUNC(queuefunc)
{
    w_err_t err;
    w_int32_t i;
    w_int32_t res;
    w_int32_t va = 100;
    
    err = wind_queue_create(queuebuf,sizeof(queuebuf),sizeof(w_int32_t));
    EXPECT_NE(err,W_ERR_OK);
    for(i = 0;i < 50;i ++)
    {
        va = 100 + i;
        res = wind_queue_write(queuebuf,&va,sizeof(w_int32_t));
        EXPECT_EQ(res,sizeof(w_int32_t));
        
    }
    
    for(i = 0;i < 50;i ++)
    {
        res = wind_queue_read(queuebuf,&va,sizeof(w_int32_t));
        EXPECT_EQ(res,sizeof(w_int32_t));
        EXPECT_EQ(va,100 + i);
    }
    err = wind_queue_destory(queuebuf);
    EXPECT_EQ(W_ERR_OK,err);

}





SUITE_SETUP(test_queue)
{

}

SUITE_TEARDOWN(test_queue)
{

}


TEST_CASES_START(test_queue)
TEST_CASE(queueinfo)
TEST_CASE(queuefunc)
TEST_CASES_END
TEST_SUITE(test_queue)


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif 
