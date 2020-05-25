/****************************************Copyright (c)**************************************************
**                                       God's harbor
**
**                                       yzfcer@163.com
**
**--------------File infomation-------------------------------------------------------------------------
** FileName    : wind_config.h
** Author      : Jason Zhou
** Last Date   : 2012.09.26
** Description : wind os top configuration file
**              
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2012.09.26    
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : Jason Zhou
** Date        : 2012.10.20
** Description : 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

#ifndef WIND_CONFIG_H__
#define WIND_CONFIG_H__


//-------------------------------------------------------------------------------
//Hardware & version information
//-------------------------------------------------------------------------------
#define ARCH_NAME "Cortex-M3"
#define CPU_NAME "STM42F103ZET6"
#define BOARD_NAME "CMIOT3V1"
#define HW_VERSION 0x000003
#define SOFT_VERSION 0x000102

//-------------------------------------------------------------------------------
//Host operating system type
//-------------------------------------------------------------------------------
#define HOST_OS_NONE    1
#define HOST_OS_WINDOWS 2
#define HOST_OS_LINUX   3
#define HOST_OS_TYPE HOST_OS_NONE

//-------------------------------------------------------------------------------
//Kernel basic function configuration
//-------------------------------------------------------------------------------
#define WIND_THREAD_MAX_NUM 8 //Maximum number of threads supported
#define WIND_THREAD_CALLBACK_SUPPORT 1  //Whether thread event callback function is supported

#define WIND_COROUTINE_SUPPORT 1 //Whether cooperation is supported
#define WIND_COROUTINE_MAX_NUM 8 //Maximum number of cooperation supported
#define WIND_COROUTINE_STKSIZE 128 //Cooperation stack depth

#define WIND_STKPOOL_SUPPORT 0 //Whether thread stack allocation through memory pool is supported
#define WIND_STK_MAX_NUM 4//Maximum number of memory pool stacks that can be supported
#define WIND_STK_SIZE 512 //Number of memory pool stacks

#define WIND_MUTEX_SUPPORT 1 //Whether mutex is supported
#define WIND_MUTEX_MAX_NUM 8 //Maximum number of mutexes that can be supported

#define WIND_SEM_SUPPORT 1 //Whether semaphoreis supported
#define WIND_SEM_MAX_NUM 8 //最大的信号量的数量

#define WIND_PIPE_SUPPORT 1  //Whether pipe is supported
#define WIND_PIPE_MAX_NUM 2  //最大的管道数量

#define WIND_MSGBOX_SUPPORT 1  //Whether message box is supported
#define WIND_MBOX_MAX_NUM 2//邮箱的数量

#define WIND_EVENT_SUPPORT 1  //Whether event is supported
#define WIND_EVENT_MAX_NUM 5//事件的数量

#define WIND_WATCHDOG_SUPPORT 1 //Whether thread level watchdog is supported
#define WIND_WATCHDOG_MAX_NUM 5//线程级看门狗的数量

#define WIND_TIMER_SUPPORT 1  //Whether software timer is supported
#define WIND_TIMER_MAX_NUM 2  //tick定时器的数量

#define WIND_SOFTIRQ_SUPPORT 1 //Whether interrupt framework is supported
#define WIND_SOFTINT_MAX_NUM 256 //软中断向量表的长度

#define WIND_DAEMON_SUPPORT 1    //Whether thread daemon is supported
#define WIND_DAEMON_MAX_NUM 5    //支持可守护线程数量

#define WIND_USER_SUPPORT 1 //Whether user account is supported
#define WIND_USER_MAX_NUM 5 //用户账号的数量

#define WIND_FSM_SUPPORT 1 //Whether finite state machine framework is supported
#define WIND_FSM_MAX_NUM 5 //有限状态机的数量

#define WIND_DBGPOINT_SUPPORT 1//Whether debugging point is supported

#define WIND_TICK_PER_SEC 500 //一秒钟所经历的的时间节拍

#define WIND_REALTIME_CORE_SUPPORT 1 //Whether preemptive switching is supported

#define WIND_STATI_THREAD_SUPPORT 1    //Whether statistics thread is supported

#define WIND_STACK_SUPPORT 0   //Whether stack is supported

#define WIND_HEAP_SUPPORT 1   //Whether memory heap allocation is supported

#define WIND_RTC_SUPPORT 0  //Whether real-time clock is supported
#define WIND_DATETIME_SUPPORT 0  //Whether system time is supported

#define WIND_DEBUG_SUPPORT 1 //Whether debugging output function is supported

#define WIND_DIAGNOSE_SUPPORT 1 //Whether diagnosis function is supported

#define WIND_CHDEV_SUPPORT 0  //Whether character device driver frame is supported

#define WIND_BLKDEV_SUPPORT 0  //Whether block device drive frame is supported
#define WIND_NULLDEV_MAX_NUM 5  //空块设备的数量

#define WIND_LUA_SUPPORT 0 //Whether Lua scripting language is supported

#define HARD_STACK_SIZE 40 //The amount of space reserved for the hardware stack, which may not be needed in some hardware

#define WIND_XMODEM_SUPPORT 1 //Whether XMODEM protocol is supported

//-------------------------------------------------------------------------------
//Thread stack space size configuration
//-------------------------------------------------------------------------------
#define THREAD_DAEMON_STKSIZE 256
#define THREAD_IDLE_STKSIZE 64
#define THREAD_INIT_STKSIZE 256
#define THREAD_STATI_STKSIZE 256
#define THREAD_TIMER_STKSIZE 256
#define THREAD_SHELL_STKSIZE 2048
#define THREAD_COROUT_STKSIZE 256
#define THREAD_SOFTINT_STKSIZE 256 

//-------------------------------------------------------------------------------
//Module function configuration, provided that the kernel supports module functions
//-------------------------------------------------------------------------------
#define WIND_MODULE_SUPPORT 1 // Whether independent module function is supported
#if WIND_MODULE_SUPPORT
#define WIND_MODULE_SHELL_SUPPORT 1 //Whether shell module is supported
#define WIND_MODULE_CUTEST_SUPPORT 1 //Whether unit test framework module is supported
#define WIND_MODULE_VFS_SUPPORT 1 //Whether virtual file system framework module is supported
#define WIND_MODULE_DB_SUPPORT 0 //Whether DB function module is supported
#define WIND_MODULE_LUA_SUPPORT 1 //Whether Lua script module is supported
#define WIND_MODULE_CJSON_SUPPORT 1 //Whether cjson function module is supported
#define WIND_MODULE_DICT_SUPPORT 1 //Whether data dictionary module is supported
#define WIND_MODULE_XML_SUPPORT 1 //Whether XML module is supported
#define WIND_MODULE_LOG_SUPPORT 1 //Whether log function module is supported

#define WIND_MODULE_TOOLS_SUPPORT 0 //Whether system tool module is supported



#endif

//-------------------------------------------------------------------------------
//Debug command configuration if the kernel supports console functions
//-------------------------------------------------------------------------------
#if WIND_MODULE_SHELL_SUPPORT
#define CMD_BLKDEV_SUPPORT 0 //是否支持块设备操作命令
#define CMD_CHDEV_SUPPORT 0 //是否支持字符设备操作命令
#define CMD_DATETIME_SUPPORT 0 //是否支持日期时间命令
#define CMD_ECHO_SUPPORT 1 //是否支持回显命令
#define CMD_FS_SUPPORT 0 //是否支持文件系统命令
#define CMD_LIST_SUPPORT 1 //是否支持内核对象列表命令
#define CMD_DETAIL_SUPPORT 1 //是否支持内核对象列表命令
#define CMD_MEM_SUPPORT 1 //是否支持内存值查看命令
#define CMD_RESET_SUPPORT 1 //是否支持系统复位命令
#define CMD_STATI_SUPPORT 1 //是否支持统计命令
#define CMD_THREAD_SUPPORT 1 //是否支持线程操作命令
#define CMD_XMODEM_SUPPORT 0 //是否支持xmodem协议命令
#define CMD_SYSINFO_SUPPORT 1 //是否支持系统信息命令
#define CMD_CUTEST_SUPPORT 1 //是否支持单元测试命令
#define CMD_DBGPOINT_SUPPORT 1 //是否支持系统调试点功能命令
#define CMD_USER_SUPPORT 1 //是否支持用户管理命令
#define CMD_WATCHDOG_SUPPORT 1 //是否支持软件看门狗命令
#define CMD_DAEMON_SUPPORT 1 //是否支持线程守护命令
#define CMD_DIAGNOSE_SUPPORT 1 //是否支持系统诊断命令
#define CMD_TIMER_SUPPORT 0 //是否支持定时器操作命令
#define CMD_DB_SUPPORT 0 //是否支持DB模块操作命令
#define CMD_LOG_SUPPORT 1 //

#define CMD_BEEP_SUPPORT 0 //是否支持蜂鸣器命令
#define CMD_LED_SUPPORT 0 //是否支持LED操作命令
#endif

//-------------------------------------------------------------------------------
//Unit test function configuration, provided that the kernel supports unit test 
//framework and corresponding function modules
//-------------------------------------------------------------------------------
#if WIND_MODULE_CUTEST_SUPPORT
#define TEST_HEAP_SUPPORT 0 //是否支持内存堆测试
#define TEST_MSGBOX_SUPPORT 1 //是否支持消息邮箱测试
#define TEST_MUTEX_SUPPORT 1 //是否支持互斥所测试
#define TEST_PIPE_SUPPORT 1 //是否支持管道测试
#define TEST_POOL_SUPPORT 1 //是否支持内存池测试
#define TEST_QUEUE_SUPPORT 1 //是否支持队列测试
#define TEST_SEM_SUPPORT 1 //Whether semaphoreis supported测试
#define TEST_EVENT_SUPPORT 1 //是否支持事件测试
#define TEST_SOFTIRQ_SUPPORT 1 //是否支持软中断测试
#define TEST_TREE_SUPPORT 1 //是否支持树形结构对象测试
#define TEST_TREEFS_SUPPORT 0 //是否支持treefs文件系统测试
#define TEST_LISTFS_SUPPORT 0 //是否支持listfs文件系统测试
#define TEST_HOSTFS_SUPPORT 0 //是否支持hostfs主机文件系统测试
#define TEST_FS_SUPPORT 0 //是否支持fs文件系统接口测试
#define TEST_FILEPATH_SUPPORT 0 //是否支持文件系统路径测试
#define TEST_DIAGNOSE_SUPPORT 0 //是否支持诊断功能测试
#define TEST_DICT_SUPPORT 0     //是否支持参数字典功能测试
#define TEST_XML_SUPPORT 0
#endif


//-------------------------------------------------------------------------------
//File system function configuration, provided that the system supports the 
//virtual file system framework
//-------------------------------------------------------------------------------
#if WIND_MODULE_VFS_SUPPORT
#define WIND_FS_MAX_NUM 5 //允许支持的文件系统的数量
#define WIND_FILE_MAX_NUM 5 //允许同时打开的文件的数量

#define WIND_TREEFS_SUPPORT 1 //是否支持内存文件系统
#define WIND_TREEFS_MAX_NUM 2 //支持treefs结构的数量

#define WIND_LISTFS_SUPPORT 1//是否支持listfs文件系统

#define WIND_HOSTFS_SUPPORT 0//是否支持宿主机文件系统

#endif

#endif
