/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
**
**                                       yzfcer@163.com
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: cmd_mem.c
**创   建   人: Jason Zhou
**最后修改日期: 2017.08.16
**描        述: 查看（打印）系统的内存区域值的命令，也可查看线程栈
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: Jason Zhou
** 版  本: v1.0
** 日　期: 2013.10.19
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: Jason Zhou
** 日　期: 2013.10.19
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "wind_string.h"
#include "wind_thread.h"
#if (CMD_MEM_SUPPORT)

static w_bool_t str2int(const char *str,w_uint32_t *value)
{
    w_uint32_t temp = 0;
    //const char *ptr = str;  //ptr保存str字符串开头
    while(*str != 0)
    {
        if ((*str < '0') || (*str > '9'))  //如果当前字符不是数字
            return W_FALSE;
        temp = temp *10 + (*str - '0'); //如果当前字符是数字则计算数值
        str++;      //移到下一个字符
    }
    *value = temp;
    return W_TRUE;
}

static w_bool_t strh2int(const char *str,w_uint32_t *value)
{
    w_uint32_t temp = 0;
    //const char *ptr = str;  //ptr保存str字符串开头
    while(*str != 0)
    {
        if ((*str >= '0') && (*str <= '9'))  
            temp = temp *16 + (*str - '0');
        else if ((*str >= 'a') && (*str <= 'f'))  
            temp = temp *16 + (*str - 'a' + 10);
        else if ((*str >= 'A') && (*str <= 'F'))  
            temp = temp *16 + (*str - 'A' + 10);
        else
            return W_FALSE;
        str++;     
    }
    *value = temp;
    return W_TRUE;
}


static w_bool_t get_num(char *str,w_uint32_t *value)
{
    if((wind_memcmp(str,"0x",2) == 0) || 
       (wind_memcmp(str,"0X",2) == 0)) 
    {
        return strh2int(&str[2],value);
    }
    else
        return str2int(str,value);
        
}

static void print_mem(w_uint32_t start,w_uint32_t len)
{
    w_uint32_t i,va;
    start = ((start >> 2) << 2);
    len = ((len + 3) >> 2);
    wind_printf("memory 0x%0x %d\r\n",start,len);
    for(i = 0;i < len;i ++)
    {
        if((i & 0x03) == 0)
            wind_printf("0x%08x:  ",start+i*4);
        va = *(w_uint32_t*)((void*)(start+i*4));
        wind_printf("%08x ",va);
        if(((i+1) & 0x03) == 0)
            wind_printf("\r\n");
    }
    wind_printf("\r\n");
}

static w_err_t display_mem(w_int32_t argc,char **argv)
{
    w_uint32_t start,len;
    WIND_ASSERT_RETURN(argc >= 3,W_ERR_INVALID);
    if(!get_num(argv[1],&start))
    {
        return W_ERR_FAIL;
    }
    else if(!get_num(argv[2],&len))
    {
        return W_ERR_FAIL;
    }
    print_mem(start,len);
    return W_ERR_OK;
}

static w_err_t display_stack(w_int32_t argc,char **argv)
{
    w_uint32_t start,end,cur,len,used;
    w_thread_s *thr;
    WIND_ASSERT_RETURN(argc >= 3,W_ERR_INVALID);
    if(wind_strcmp(argv[1],"stack") != 0)
    {
        return W_ERR_FAIL;
    }
    thr = wind_thread_get(argv[2]);
    if(thr == W_NULL)
    {
        return W_ERR_FAIL;
    }
    start = (w_uint32_t)thr->stack_start;
    end = start + thr->stksize*sizeof(w_stack_t);
    cur = (w_uint32_t)thr->stack_cur;
    len = (end - cur);
    used = (end - cur) / sizeof(w_stack_t*);
    
    wind_printf("stack start :0x%08X\r\n",start);
    wind_printf("stack end   :0x%08X\r\n",end);
    wind_printf("stack cur   :0x%08X\r\n",cur);
    wind_printf("stack size  :%d\r\n",thr->stksize);
    wind_printf("stack used  :%d\r\n",used);
    if(len <= 4096)
        print_mem(cur,len);
    return W_ERR_OK;
}



COMMAND_DISC(mem)
{
    wind_printf("to show memory data values.\r\n");
}

COMMAND_USAGE(mem)
{
    wind_printf("--WARNING--:this command is NOT safe for product.\r\n");
    wind_printf("mem <start> <lenth>:--to show thread infomation.\r\n");
    wind_printf("mem stack <threadname>:--to show thread stack infomation.\r\n");
}

COMMAND_MAIN(mem,argc,argv)
{
    if(display_mem(argc,argv) == W_ERR_OK)
        return W_ERR_OK;
    else if(display_stack(argc,argv) == W_ERR_OK)
        return W_ERR_OK;
    wind_printf("command [%s] format error.\r\n",argv[0]);
    return W_ERR_FAIL;
}

COMMAND_DEF(mem);

#endif

