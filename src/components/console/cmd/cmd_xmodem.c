/****************************************Copyright (c)**************************************************
**                                       ��  ��  ��  ��
** ��   ��   ��: cmd_xmodem.c
** ��   ��   ��: Jason Zhou
** ����޸�����: 2015/1/24 20:24:37
** ��        ��: xmodemЭ�鴫������
**  
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: Jason Zhou
** ��  ��: v1.0
** �ա���: 2015/1/24 20:24:37
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�----------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
** ���ļ���C����Դ�ļ�ģ���������ɡ�------------��纣����Ʒ��������Ʒ��------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "wind_heap.h"
#include "xmodem.h"
#if WIND_XMODEM_SUPPORT
#include "treefs.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************ͷ�ļ�����***********************************************/

#if (WIND_CONSOLE_SUPPORT && CMD_XMODEM_SUPPORT)

/********************************************�ڲ���������**********************************************/




/********************************************�ڲ���������*********************************************/
extern w_int32_t xmodem_send(w_uint8_t *src, w_int32_t srcsz);
extern w_int32_t xmodem_recv_bak(w_uint8_t *dest, w_int32_t destsz);

static w_err_t cmd_xmodem_get(int argc,char **argv)
{
    w_err_t err = W_ERR_OK;
    w_int32_t len;
    treefile_s *file;
    w_uint8_t *buff;
    if(argv[2][0] != '/')
    {
        wind_error("unknown file path.");
        return W_ERR_INVALID;
    }
    xmodem_recv_start();
    buff = wind_malloc(4096);
    file = treefile_open(argv[2],TF_FMODE_CRT | TF_FMODE_W);
    for(;;)
    {
        wind_memset(buff,0,4096);
        len = xmodem_recv_data(buff,4096);
        if(len < 0)
        {
            wind_error("xmodem receive failed.");
            err = W_ERR_FAIL;
            break;
        }
        if(len == 0)
        {
            break;
        }
        treefile_write(file,buff,len);
    }
    xmodem_recv_end();
    treefile_close(file);
    wind_free(buff);
    return err;
}

static w_err_t cmd_xmodem_put(int argc,char **argv)
{
    w_int32_t len;
    treefile_s *file;
    w_uint8_t *buff;
    if(argv[2][0] != '/')
    {
        wind_error("unknown file path.");
        return W_ERR_INVALID;
    }
    file = treefile_open(argv[2],TF_FMODE_R);
    if(file == W_NULL)
    {
        wind_error("file is NOT exist.");
        return W_ERR_NOFILE;
    }
    buff = wind_malloc(file->filelen);
    wind_memset(buff,0,file->filelen);
    len = treefile_read(file,buff,file->filelen);
    len = xmodem_send(buff,len);
    treefile_close(file);
    wind_free(buff);
    return W_ERR_OK;
}

/********************************************ȫ�ֱ�������**********************************************/



/********************************************ȫ�ֺ�������**********************************************/
COMMAND_DISC(xmodem)
{
    console_printf("to translate file data via xmodem protocol.\r\n");
}

COMMAND_USAGE(xmodem)
{
    console_printf("xmodem get <localfile>:to receive a file save as localfile.\r\n");
    console_printf("xmodem put <localfile>:to send localfile to remote host via xmodem.\r\n");
}

COMMAND_MAIN(xmodem,argc,argv)
{
    WIND_ASSERT_RETURN(argc >= 3,W_ERR_INVALID);
    if(wind_strcmp(argv[1],"get") == 0)
        return cmd_xmodem_get(argc,argv);
    if(wind_strcmp(argv[1],"put") == 0)
        return cmd_xmodem_put(argc,argv);
    return W_ERR_OK;
}

COMMAND_DEF(xmodem);

#endif
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif