/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
** ��   ��   ��: test_framework.h / test_framework.c
** ��   ��   ��: Jason Zhou
** ����޸�����: 2015/1/24 15:42:27
** ��        ��: wind_os��ϵͳ�Ĳ��Կ���ļ����ڿ���¼̳��˸��ֹ��ܵĵ�Ԫ����
**  
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2015/1/24 15:42:27
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
** ���ļ���C����Դ�ļ�ģ���������ɡ�------------��纣����Ʒ��������Ʒ��------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef __TEST_FRAMEWORK_H__
#define __TEST_FRAMEWORK_H__
/*********************************************ͷ�ļ�����***********************************************/
#include "wind_config.h"
#include "wind_debug.h"
//#include "test_port.h"
#if WIND_CUTEST_SUPPORT
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus



/***********************************************�궨��*************************************************/
#define TEST_CASE_NAME_LEN 24
#define TEST_SUITE_NAME_LEN 24
#define TEST_FAIL_LIST_CNT 100
extern void test_suite_err(w_uint32_t line);

#define FAIL_EXPECT_FALSE_OUT(x,res) test_printf("failed expection:FUNCTION:%s,LINE:%d:which expected "#x"is %s\r\n",__FUNCTION__,__LINE__,res)

#define FAIL_EXPECT_OUT(x,y,than) test_printf("failed expection:FUNCTION:%s,LINE:%d:which expected "#x" %s "#y"\r\n",__FUNCTION__,__LINE__,than)


//#define EXPECT_EQ(x,y) test_printf("FILE:%s,LINE:%d,expected %s,in fact %s\r\n",__FILE__,__LINE__,#x,#y)

/**********************************************ö�ٶ���************************************************/


#ifndef W_NULL
#define W_NULL (void*)0
#endif
#define err_t w_uint32_t
#define ERR_OK 0
#define ERR_FAIL -1
#define TEST_ASSERT_RETURN(x,y)
#define test_printf wind_printf

/*********************************************�ṹ�嶨��***********************************************/
//ȫ�ֵ�test suite�б�
typedef struct __w_test_case_s w_test_case_s;
typedef struct __w_test_suite_s w_test_suite_s;
typedef struct __w_suite_list_s w_suite_list_s;
typedef struct __w_test_stati_s w_test_stati_s;
typedef struct __w_fail_info_s w_fail_info_s;
typedef struct __w_stati_info_s w_stati_info_s;

//���������ṹ
struct __w_test_case_s
{
    char name[TEST_CASE_NAME_LEN];
    void (*setup)(void);
    void (*teardown)(void);
    void (*test)(void);
};

//�����׽ṹ
struct __w_test_suite_s
{
    char name[TEST_SUITE_NAME_LEN];
    w_uint32_t case_cnt;//��������������
    w_test_case_s *tcase;
    //void (*init)(void);
    void (*setup)(void);
    void (*teardown)(void);
    w_test_suite_s *next;
};


struct __w_suite_list_s
{
    w_test_suite_s *head;
    w_test_suite_s *tail;
    w_uint32_t cnt;
};

//ִ��ʧ�ܵ���Ϣ
struct __w_fail_info_s
{
    w_test_suite_s *suite;
    w_test_case_s *tcase;
    w_uint32_t line;
    w_fail_info_s *next;
};

//����ִ�н��ͳ����Ϣ
struct __w_test_stati_s
{
    w_uint32_t tot_suite;
    w_uint32_t tot_case;
    w_uint32_t passed_suite;
    w_uint32_t failed_suite;
    w_uint32_t passed_case;
    w_uint32_t failed_case;
    w_fail_info_s fail_obj[TEST_FAIL_LIST_CNT];
};




struct __w_stati_info_s
{
    //ͳ����Ϣ
    w_test_stati_s stat;

    //������Ϣ�б�
    w_fail_info_s *failhead;
    w_fail_info_s *lastfail;
    w_uint32_t failcnt;

    //��ǰ������Ϣ
    w_test_suite_s *suite;
    w_test_case_s *tcase;
    w_uint32_t case_err;
    w_uint32_t suite_err;
};

/********************************************ȫ�ֱ�������**********************************************/



/********************************************ȫ�ֺ�������**********************************************/
static w_int32_t stringlenth(char *str);
w_int32_t stringcmp(const char *cs,const char *ct);


err_t test_suite_register(w_test_suite_s *test_suite);
void show_test_suites(void);
w_err_t cutest_main(w_int32_t argc,char **argv);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif 
#endif 