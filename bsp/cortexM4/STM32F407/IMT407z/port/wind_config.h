/****************************************Copyright (c)**************************************************
**                                       God's harbor
**
**                                       yzfcer@163.com
**
**--------------File infomation-------------------------------------------------------------------------
** FileName    : wind_config.h
** Author      : Jason Zhou
** Last Date   : 2012.09.26
** Description : wind-os top configuration file
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
#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus


//-------------------------------------------------------------------------------
//Hardware & version information
//-------------------------------------------------------------------------------
#define ARCH_NAME "Cortex-M4"
#define CPU_NAME "STM32F407ZGT6"
#define BOARD_NAME "IMT407Z"
#define HW_VERSION 0x000201
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

#define WIND_STKPOOL_SUPPORT 1 //Whether thread stack allocation through memory pool is supported
#define WIND_STK_MAX_NUM 4//Maximum number of memory pool stacks that can be supported
#define WIND_STK_SIZE 512 //Number of memory pool stacks

#define WIND_MUTEX_SUPPORT 1 //Whether mutex is supported
#define WIND_MUTEX_MAX_NUM 20 //Maximum number of mutexes that can be supported

#define WIND_SEM_SUPPORT 1 //Whether semaphoreis supported
#define WIND_SEM_MAX_NUM 10 //Maximum number of semaphores

#define WIND_PIPE_SUPPORT 1  //Whether pipe is supported
#define WIND_PIPE_MAX_NUM 10  //Maximum number of pipes

#define WIND_MSGBOX_SUPPORT 1  //Whether message box is supported
#define WIND_MBOX_MAX_NUM 5//Maximum number of message boxes

#define WIND_EVENT_SUPPORT 1  //Whether event is supported
#define WIND_EVENT_MAX_NUM 5//Maximum number of events

#define WIND_WATCHDOG_SUPPORT 1 //Whether thread level watchdog is supported
#define WIND_WATCHDOG_MAX_NUM 5//Maximum number of watchdogs

#define WIND_TIMER_SUPPORT 1  //Whether software timer is supported
#define WIND_TIMER_MAX_NUM 10  //Maximum number of software timers

#define WIND_SOFTIRQ_SUPPORT 1 //Whether software interrupt framework is supported
#define WIND_SOFTINT_MAX_NUM 256 //Maximum number of software interrupts

#define WIND_DAEMON_SUPPORT 1    //Whether thread daemon is supported
#define WIND_DAEMON_MAX_NUM 5    //Maximum number of thread daemons

#define WIND_USER_SUPPORT 1 //Whether user account is supported
#define WIND_USER_MAX_NUM 5 //Maximum number of user accounts

#define WIND_FSM_SUPPORT 1 //Whether finite state machine framework is supported
#define WIND_FSM_MAX_NUM 5 //Maximum number of finite state machines

#define WIND_DBGPOINT_SUPPORT 1//Whether debugging point is supported

#define WIND_TICK_PER_SEC 500 //The number of tick beats in a second

#define WIND_REALTIME_CORE_SUPPORT 1 //Whether preemptive switching is supported

#define WIND_STATI_THREAD_SUPPORT 1    //Whether statistics thread is supported

#define WIND_STACK_SUPPORT 1   //Whether stack is supported

#define WIND_HEAP_SUPPORT 1   //Whether memory heap allocation is supported

#define WIND_RTC_SUPPORT 0  //Whether real-time clock is supported
#define WIND_DATETIME_SUPPORT 1  //Whether system time is supported

#define WIND_DEBUG_SUPPORT 1 //Whether debugging output function is supported

#define WIND_DIAGNOSE_SUPPORT 1 //Whether diagnosis function is supported

#define WIND_CHDEV_SUPPORT 1  //Whether character device driver frame is supported

#define WIND_BLKDEV_SUPPORT 1  //Whether block device drive frame is supported
#define WIND_NULLDEV_MAX_NUM 5  //Maximum number of block devices

#define WIND_LUA_SUPPORT 1 //Whether Lua scripting language is supported

#define HARD_STACK_SIZE 40 //The amount of space reserved for the hardware stack, which may not be needed in some hardware

#define WIND_XMODEM_SUPPORT 1 //Whether XMODEM protocol is supported

//-------------------------------------------------------------------------------
//Thread stack space size configuration
//-------------------------------------------------------------------------------
#define THREAD_DAEMON_STKSIZE    256
#define THREAD_IDLE_STKSIZE      64
#define THREAD_INIT_STKSIZE      256
#define THREAD_STATI_STKSIZE     256
#define THREAD_TIMER_STKSIZE     256
#define THREAD_SHELL_STKSIZE     2048
#define THREAD_COROUT_STKSIZE    256
#define THREAD_SOFTINT_STKSIZE   256 

//-------------------------------------------------------------------------------
//Module function configuration, provided that the kernel supports module functions
//-------------------------------------------------------------------------------
#define WIND_MODULE_SUPPORT 1 // Whether independent module function is supported
#if WIND_MODULE_SUPPORT
#define WIND_MODULE_SHELL_SUPPORT   1 //Whether shell module is supported
#define WIND_MODULE_CUTEST_SUPPORT  1 //Whether unit test framework module is supported
#define WIND_MODULE_VFS_SUPPORT     1 //Whether virtual file system framework module is supported
#define WIND_MODULE_DB_SUPPORT      0 //Whether DB function module is supported
#define WIND_MODULE_LUA_SUPPORT     1 //Whether Lua script module is supported
#define WIND_MODULE_CJSON_SUPPORT   1 //Whether cjson function module is supported
#define WIND_MODULE_DICT_SUPPORT    1 //Whether data dictionary module is supported
#define WIND_MODULE_XML_SUPPORT     1 //Whether XML module is supported
#define WIND_MODULE_LOG_SUPPORT     1 //Whether log function module is supported
#define WIND_MODULE_XMODEM_SUPPORT  1 //Whether xmodem protocol module is supported
#define WIND_MODULE_NET_SUPPORT     0 //Whether TCP/IP NET protocol module is supported

#define WIND_MODULE_TOOLS_SUPPORT   0 //Whether system tool module is supported



#endif

//-------------------------------------------------------------------------------
//Debug command configuration if the kernel supports console functions
//-------------------------------------------------------------------------------
#if WIND_MODULE_SHELL_SUPPORT
#define CMD_BLKDEV_SUPPORT    1 //Whether block device operation command is supported
#define CMD_CHDEV_SUPPORT     0 //Whether character device operation command is supported
#define CMD_DATETIME_SUPPORT  1 //Whether datetime command is supported
#define CMD_ECHO_SUPPORT      1 //Whether echo command is supported
#define CMD_LIST_SUPPORT      1 //Whether kernel object list command is supported
#define CMD_DETAIL_SUPPORT    1 //Whether kernel object detail command is supported
#define CMD_MEM_SUPPORT       1 //Whether memory value viewing command is supported
#define CMD_RESET_SUPPORT     1 //Whether system reset command is supported
#define CMD_STATI_SUPPORT     1 //Whether statistics command is supported
#define CMD_THREAD_SUPPORT    1 //Whether thread operation command is supported
#define CMD_XMODEM_SUPPORT    1 //Whether XMODEM command is supported
#define CMD_SYSINFO_SUPPORT   1 //Whether system information command is supported
#define CMD_CUTEST_SUPPORT    1 //Whether unit test command is supported
#define CMD_DBGPOINT_SUPPORT  1 //Whether the system debugging point function command is supported
#define CMD_USER_SUPPORT      1 //Whether user management command is supported
#define CMD_WATCHDOG_SUPPORT  1 //Whether the software watchdog command is supported
#define CMD_DAEMON_SUPPORT    1 //Whether thread daemon command is supported
#define CMD_DIAGNOSE_SUPPORT  1 //Whether system diagnostic command is supported
#define CMD_TIMER_SUPPORT     0 //Whether timer operation command is supported
#define CMD_DB_SUPPORT        0 //Whether DB module operation command is supported
#define CMD_LOG_SUPPORT       1 //Whether log operation command is supported

#define CMD_BEEP_SUPPORT 1 //Whether beep command is supported
#define CMD_LED_SUPPORT 1 //Whether LED operation command is supported
#endif

#if WIND_MODULE_TOOLS_SUPPORT
#define CMD_MKFS_SUPPORT      0 //Whether the command of creating file system image is supported,pc
#define CMD_PACK_SUPPORT      0 //Whether the command to package firmware is supported,pc
#define CMD_RCP_SUPPORT       0 //Whether the command to copy files between the host and wind-os is supported,pc
#define CMD_EDSRC_SUPPORT     1 //Whether the command to edit source file and aligning is supported,pc
#endif

//-------------------------------------------------------------------------------
//Unit test function configuration, provided that the kernel supports unit test 
//framework and corresponding function modules
//-------------------------------------------------------------------------------
#if WIND_MODULE_CUTEST_SUPPORT
#define TEST_HEAP_SUPPORT     1 //Whether memory heap test is supported
#define TEST_MSGBOX_SUPPORT   1 //Whether message mailbox test is supported
#define TEST_MUTEX_SUPPORT    1 //Whether mutual exclusion test is supported
#define TEST_PIPE_SUPPORT     1 //Whether pipeline testing is supported
#define TEST_POOL_SUPPORT     1 //Whether memory pool test is supported
#define TEST_QUEUE_SUPPORT    1 //Whether queue test is supported
#define TEST_SEM_SUPPORT      1 //Whether semaphore test is supported
#define TEST_EVENT_SUPPORT    1 //Whether event test is supported
#define TEST_SOFTIRQ_SUPPORT  1 //Whether soft interrupt test is supported
#define TEST_TREE_SUPPORT     1 //Whether tree structure  test is supported
#define TEST_TREEFS_SUPPORT   1 //Whether treefs file system  test is supported
#define TEST_LISTFS_SUPPORT   1 //Whether listfs file system  test is supported
#define TEST_HOSTFS_SUPPORT   0 //Whether hostfs file system  test is supported
#define TEST_FS_SUPPORT       0 //Whether file system interface test is supported
#define TEST_FILEPATH_SUPPORT 0 //Whether file path function test is supported
#define TEST_DIAGNOSE_SUPPORT 0 //Whether diagnostic function test is supported
#define TEST_DICT_SUPPORT     0 //Whether parameter dictionary function test is supported
#define TEST_XML_SUPPORT      1 //Whether XML function test is supported
#endif


//-------------------------------------------------------------------------------
//File system function configuration, provided that the system supports the 
//virtual file system framework
//-------------------------------------------------------------------------------
#if WIND_MODULE_VFS_SUPPORT
#define WIND_VFS_MAX_NUM    5 //Maximum number of file system objects allowed
#define WIND_FILE_MAX_NUM   5 //Maximum number of files allowed to open at the same time

#define WIND_TREEFS_SUPPORT 1 //Whether memory file system treefs is supported
#define WIND_TREEFS_MAX_NUM 2 //Maximum number of treefs objects supported

#define WIND_LISTFS_SUPPORT 1 //Whether listfs is supported

#define WIND_HOSTFS_SUPPORT 0 //Whether hostfs is supported

#define CMD_FS_SUPPORT      1 //Whether file system command is supported
#define CMD_MOUNT_SUPPORT   1
#define CMD_UMOUNT_SUPPORT  1
#define CMD_WRITE_SUPPORT   1
#define CMD_CAT_SUPPORT     1
#define CMD_CD_SUPPORT      1
#define CMD_FORMAT_SUPPORT  1
#define CMD_LS_SUPPORT      1
#define CMD_MKDIR_SUPPORT   1
#define CMD_PWD_SUPPORT     1
#define CMD_RM_SUPPORT      1
#define CMD_TOUCH_SUPPORT   1

#endif



//-------------------------------------------------------------------------------
//TCP/IP net protocol stack configuration, provided that the system supports the 
//net protocol stack
//-------------------------------------------------------------------------------
#if WIND_MODULE_NET_SUPPORT
#define WIND_NET_ETHER_SUPPORT  1
#define WIND_NET_VLAN_SUPPORT   1
#define WIND_NET_ARP_SUPPORT    1
#define WIND_NET_ICMP_SUPPORT   1
#define WIND_NET_IGMP_SUPPORT   1
#define WIND_NET_IP_SUPPORT     1
#define WIND_NET_TCP_SUPPORT    1
#define WIND_NET_UDP_SUPPORT    1
#define WIND_NET_DHCP_SUPPORT   1
#define WIND_NET_DNS_SUPPORT    1
#define WIND_NET_TFTP_SUPPORT   1

#define CMD_IFCONFIG_SUPPORT    1
#define CMD_ROUTE_SUPPORT       1   
#define CMD_NETNODE_SUPPORT     1
#define CMD_ARP_SUPPORT         1
#define CMD_FDB_SUPPORT         1

#define WIND_FDB_MAX_NUM        32
#define WIND_ARP_TB_MAX_NUM     32
#define WIND_ROUTE_TB_MAX_NUM   16
#define WIND_NETDEV_MAX_NUM     8
#endif

#ifdef __cplusplus
}
#endif //#ifdef __cplusplus
#endif //#ifndef WIND_CONFIG_H__


