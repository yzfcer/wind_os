/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: test_heap.c
** 创   建   人: 周江村
** 最后修改日期: 2017/10/22 16:29:55
** 描        述: 
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2017/10/22 16:29:55
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 单元测试用例的测试模板
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/*********************************************头文件定义***********************************************/
#include "cut.h"
#include "wind_heap.h"
#include "wind_string.h"
/********************************************内部变量定义**********************************************/




/********************************************内部函数定义*********************************************/


/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/


CASE_SETUP(heapinfo)
{

}

CASE_TEARDOWN(heapinfo)
{

}

CASE_FUNC(heapinfo)
{
    w_int32_t res;
    w_err_t err;
    w_uint8_t *buff;
    buff = (w_uint8_t*)wind_heap_alloc_default(64);
    EXPECT_NE(buff,NULL);
    wind_memset(buff,0,64);
    wind_strcpy((char*)buff,"heap test start.");
    res = wind_strcmp((char*)buff,"heap test start.");
    EXPECT_EQ(res,0);
    err = wind_heap_free(buff);
    EXPECT_EQ(err,ERR_OK);
}

CASE_SETUP(heapfunc)
{

}

CASE_TEARDOWN(heapfunc)
{

}

CASE_FUNC(heapfunc)
{
}

CASE_SETUP(heapmulti)
{
    
}

CASE_TEARDOWN(heapmulti)
{

}

CASE_FUNC(heapmulti)
{
}


SUITE_SETUP(test_heap)
{

}

SUITE_TEARDOWN(test_heap)
{

}


TEST_CASES_START(test_heap)
TEST_CASE(heapinfo)
TEST_CASE(heapfunc)
TEST_CASE(heapmulti)
TEST_CASES_END
TEST_SUITE(test_heap)


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
