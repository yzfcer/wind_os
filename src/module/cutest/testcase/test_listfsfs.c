/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
** ��   ��   ��: test_listfs.c
** ��   ��   ��: Jason Zhou
** ����޸�����: 2017/10/22 16:29:55
** ��        ��: listfs�ļ�ϵͳ��Ԫ����
**  
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2017/10/22 16:29:55
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
** ���ļ���C����Դ�ļ�ģ���������ɡ�------------��纣����Ʒ��������Ʒ��------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cut.h"
#include "wind_string.h"
#if (WIND_CUTEST_SUPPORT && TEST_LISTFS_SUPPORT)
#include "listfs.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

listfs_s g_lfs;
CASE_SETUP(listfs_create)
{

}


CASE_TEARDOWN(listfs_create)
{

}

CASE_FUNC(listfs_create)
{
    w_err_t err;
    listfile_s *file;
    file = listfile_open(W_NULL,"/test.txt",LF_FMODE_CRT);
    EXPECT_NE(file,W_NULL);
    err = listfile_close(file);
    EXPECT_EQ(err,W_ERR_OK);
    err = listfile_remove(file);
    EXPECT_EQ(err,W_ERR_OK);
    file = listfile_open(W_NULL,"/test1.txt",LF_FMODE_CRT);
    EXPECT_NE(file,W_NULL);
    err = listfile_close(file);
    EXPECT_EQ(err,W_ERR_OK);
    err = listfile_remove(file);
    EXPECT_EQ(err,W_ERR_OK);
    file = listfile_open(W_NULL,"/test2.txt",LF_FMODE_CRT);
    EXPECT_NE(file,W_NULL);
    err = listfile_close(file);
    EXPECT_EQ(err,W_ERR_OK);
    err = listfile_remove(file);
    EXPECT_EQ(err,W_ERR_OK);
}


CASE_SETUP(listfs_readwrite)
{
}

CASE_TEARDOWN(listfs_readwrite)
{
    
}

static w_uint8_t buff[32];
CASE_FUNC(listfs_readwrite)
{
    w_int32_t len;
    w_err_t err;
    listfile_s *file;
    char *str = "this is a file test string.";
    file = listfile_open(W_NULL,"/test.txt",LF_FMODE_CRT | LF_FMODE_W);
    EXPECT_NE(file,W_NULL);
    len = listfile_write(file,(w_uint8_t*)str,wind_strlen(str));
    EXPECT_EQ(len,wind_strlen(str));
    err = listfile_close(file);
    EXPECT_EQ(err,W_ERR_OK);

    wind_memset(buff,0,32);
    file = listfile_open(W_NULL,"/test.txt",LF_FMODE_R);
    EXPECT_NE(file,W_NULL);
    len = listfile_read(file,buff,32);
    EXPECT_EQ(len,wind_strlen(str));
    len = wind_strcmp(str,(char*)buff);
    EXPECT_EQ(len,0);
    err = listfile_close(file);
    EXPECT_EQ(err,W_ERR_OK);
    err = listfile_remove(file);
    EXPECT_EQ(err,W_ERR_OK);
    
}


CASE_SETUP(listfs_format)
{
}

CASE_TEARDOWN(listfs_format)
{
    
}

CASE_FUNC(listfs_format)
{
    w_err_t err;
    w_blkdev_s *blkdev;
    blkdev = wind_blkdev_get("disk");
    if(blkdev == W_NULL)
        return;
    wind_blkdev_open(blkdev);
    err = listfs_format(&g_lfs,blkdev);
    EXPECT_EQ(err,W_ERR_OK);
    wind_blkdev_close(blkdev);
}

SUITE_SETUP(test_listfs)
{
}

SUITE_TEARDOWN(test_listfs)
{

}



TEST_CASES_START(test_listfs)
TEST_CASE(listfs_format)
TEST_CASE(listfs_create)
TEST_CASE(listfs_readwrite)
TEST_CASES_END
TEST_SUITE(test_listfs)

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif