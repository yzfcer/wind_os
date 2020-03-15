/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: test_diagnose.c
** 创   建   人: Jason Zhou
** 最后修改日期: 2017/10/22 16:29:55
** 描        述: 诊断功能测试
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
#include "wind_diagnose.h"
#if (WIND_MODULE_CUTEST_SUPPORT && TEST_DIAGNOSE_SUPPORT)
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/********************************************内部变量定义**********************************************/






/********************************************内部函数定义*********************************************/


/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/



CASE_SETUP(func) FUNC_EMPTY
CASE_TEARDOWN(func) FUNC_EMPTY
CASE_FUNC(func)
{
    w_err_t err;
    err = wind_diagnose_check();
    EXPECT_EQ(err,W_ERR_OK);
}



SUITE_SETUP(diagnose) FUNC_EMPTY
SUITE_TEARDOWN(diagnose) FUNC_EMPTY

TEST_CASES_START(diagnose)
TEST_CASE(func)
TEST_CASES_END
TEST_SUITE(diagnose)

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif
