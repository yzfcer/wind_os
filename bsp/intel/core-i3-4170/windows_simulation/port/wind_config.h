/*********************************************************************************
  *Copyright(C),2017-2020,yzfcer@163.com
  *FileName:  
  *Author:      Jason Zhou
  *Version:     1.0
  *Date:        2017/04/08
  *Description:  
  *Others:  
  *History:  
     1.Date:
       Author:
       Modification:
**********************************************************************************/
#ifndef WIND_CONFIG_H__
#define WIND_CONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------
//设备信息
//-------------------------------------------------------------------------------
#define ARCH_NAME "x86_x64"
#define CPU_NAME "core-i3-4170"
#define BOARD_NAME "windows_simulation"
#define HW_VERSION 0x000003
#define SOFT_VERSION 0x000102


//-------------------------------------------------------------------------------
//boot相关参数定制
//-------------------------------------------------------------------------------
#define BOOT_SIZE 0xE000    //bootloader程序区
#define PARAM1_SIZE 0x1000  //bootloader参数区
#define PARAM2_SIZE 0x1000  //bootloader参数备份区
#define IMG1_SIZE 0x10000   //系统程序存储区
#define IMG2_SIZE 0x10000   //系统程序备份区
#define IMG_PARA_SIZE 0x1000  //系统程序参数区
#define FS_SIZE 0x20000     //文件系统分区

#define SHARE_SIZE 0x1000   //boot和系统共享参数区
#define CACHE_SIZE 0x40000  //系统程序下载/升级缓存区
#define SYSRUN_SIZE 0x10000 //系统程序运行区(ROM或RAM)

#define BOOT_DEBUG_ENABLE 0 //使能debug信息打印功能
#define BOOT_TEST_ENABLE 1 //测试功能使能

//加密方式
#define ENCRYPT_NONE 0
#define ENCRYPT_RC4 1
#define ENCRYPT_AES 2
#define ENCRYPT_DES 3
#define ENCRYPT_TYPE ENCRYPT_RC4//ENCRYPT_NONE//

//iamge文件加密密钥
#define ENCRYPT_KEY {0x23,0x34,0x56,0x78,0x90,0xab,0xcd,0xef,0x01,0x23,0x45,0x67}

//芯片锁定使能
#define MCU_LOCK_ENABLE 0

//等待键盘输入时间秒数
#define WAIT_KEY_SEC 2

//运行位置
#define RUN_IN_RAM 1
#define RUN_IN_ROM 2
#define RUN_SPACE_TYPE RUN_IN_RAM

//物理存储器的数量
#define MEDIA_COUNT 4

//存储器逻辑分区的数量
#define PART_COUNT 12

//用于数据拷贝的缓存buf大小
#define COMMBUF_SIZE 4096





//-------------------------------------------------------------------------------
//操作系统内核基本功能定制
//-------------------------------------------------------------------------------
#define WIND_THREAD_MAX_NUM 8 //需要的线程总数,建议根据需要来定义
#define WIND_THREAD_CALLBACK_SUPPORT 1  //是否支持线程事件毁回调函数

#define WIND_STKPOOL_SUPPORT 0 //是否支持线程堆栈通过内存池分配
#define WIND_STK_MAX_NUM 4//堆栈的数量
#define WIND_STK_SIZE 512 //堆栈大小

#define WIND_MUTEX_SUPPORT 1 //是否支持互斥锁
#define WIND_MUTEX_MAX_NUM 10 //互斥锁的数量

#define WIND_SEM_SUPPORT 1 //是否支持信号量
#define WIND_SEM_MAX_NUM 8 //最大的信号量的数量

#define WIND_PIPE_SUPPORT 1  //是否支持管道机制
#define WIND_PIPE_MAX_NUM 2  //最大的管道数量

#define WIND_MSGBOX_SUPPORT 1  //是否支持消息机制
#define WIND_MBOX_MAX_NUM 2//邮箱的数量

#define WIND_EVENT_SUPPORT 1  //是否支持事件机制
#define WIND_EVENT_MAX_NUM 5//事件的数量

#define WIND_WATCHDOG_SUPPORT 1 //是否支持线程级看门狗
#define WIND_WATCHDOG_MAX_NUM 5//线程级看门狗的数量

#define WIND_TIMER_SUPPORT 1  //是否支持软件定时器
#define WIND_TIMER_MAX_NUM 2  //tick定时器的数量

#define WIND_SOFTIRQ_SUPPORT 1 //是否支持软中断功能
#define WIND_SOFTINT_MAX_NUM 256 //软中断向量表的长度

#define WIND_USER_SUPPORT 0 //是否支持用户账号功能
#define WIND_USER_MAX_NUM 5 //用户账号的数量

#define WIND_FS_SUPPORT 1 //是否支持内存文件系统
#define WIND_FS_MAX_NUM 2 //允许支持的文件系统的数量
#define WIND_FILE_MAX_NUM 5 //允许打开的文件的数量

#define WIND_DBGPOINT_SUPPORT 1//是否支持调试点文件系统

#define WIND_TICK_PER_SEC 500 //一秒钟所经历的的时间街节拍

#define WIND_REALTIME_CORE_SUPPORT 1 //是否支持实时内核，即抢占式切换

#define WIND_DAEMON_THREAD_SUPPORT 1    //是否支持守护线程

#define WIND_STATI_THREAD_SUPPORT 1    //是否支持统计线程

#define WIND_STACK_SUPPORT 0   //是否支持堆栈

#define WIND_HEAP_SUPPORT 1   //是否支持内存堆的分配

#define WIND_RTC_SUPPORT 0  //是否支持实时时间
#define WIND_DATETIME_SUPPORT 0  //是否支持系统时间

#define WIND_DEBUG_SUPPORT 1 //是否支持调试输出模块

#define WIND_DRVFRAME_SUPPORT 0  //是否字符驱动框架

#define WIND_BLK_DRVFRAME_SUPPORT 1  //是否块驱动框架

#define WIND_LUA_SUPPORT 0 //是否支持lua脚本语言

#define HARD_STACK_SIZE 40 //为硬件堆栈保留的空间大小，在某些硬件里可以不需要



//-------------------------------------------------------------------------------
//调试命令定制，前提是内核支持控制台功能
//-------------------------------------------------------------------------------
#define WIND_CONSOLE_SUPPORT 1 //是否支持控制台模块

#define CMD_BLKDEV_SUPPORT 0 //是否支持块设备操作命令
#define CMD_DATETIME_SUPPORT 0 //是否支持日期时间命令
#define CMD_ECHO_SUPPORT 1 //是否支持回显命令
#define CMD_FS_SUPPORT 0 //是否支持文件系统命令
#define CMD_LIST_SUPPORT 0 //是否支持内核对象列表命令
#define CMD_LUA_SUPPORT 0 //是否支持lua脚本命令
#define CMD_MEM_SUPPORT 0 //是否支持内存值查看命令
#define CMD_RESET_SUPPORT 0 //是否支持系统复位命令
#define CMD_STATI_SUPPORT 0 //是否支持统计命令
#define CMD_THREAD_SUPPORT 0 //是否支持线程操作命令
#define CMD_XMODEM_SUPPORT 0 //是否支持xmodem协议命令
#define CMD_SYSINFO_SUPPORT 0 //是否支持系统信息命令
#define CMD_CUTEST_SUPPORT 0 //是否支持单元测试命令
#define CMD_MKFS_SUPPORT 1 //是否支持创建文件系统镜像命令
#define CMD_DBGPOINT_SUPPORT 0 //是否支持系统调试点功能命令
#define CMD_USER_SUPPORT 0 //是否支持用户管理命令

#define CMD_BEEP_SUPPORT 0 //是否支持蜂鸣器命令
#define CMD_LED_SUPPORT 0 //是否支持LED操作命令


//-------------------------------------------------------------------------------
//单元测试功能定制，前提是内核支持单元测试框架,并且支持对应的功能模块
//-------------------------------------------------------------------------------
#define WIND_CUTEST_SUPPORT 1 //是否支持单元测试框架

#define TEST_HEAP_SUPPORT 0 //是否支持内存堆测试
#define TEST_MSGBOX_SUPPORT 1 //是否支持消息邮箱测试
#define TEST_MUTEX_SUPPORT 1 //是否支持互斥所测试
#define TEST_PIPE_SUPPORT 1 //是否支持管道测试
#define TEST_POOL_SUPPORT 1 //是否支持内存池测试
#define TEST_QUEUE_SUPPORT 1 //是否支持队列测试
#define TEST_SEM_SUPPORT 1 //是否支持信号量测试
#define TEST_EVENT_SUPPORT 1 //是否支持事件测试
#define TEST_SOFTIRQ_SUPPORT 1 //是否支持软中断测试
#define TEST_TREE_SUPPORT 1 //是否支持树形结构对象测试
#define TEST_TREEFS_SUPPORT 1 //是否支持treefs文件系统测试
#define TEST_FS_SUPPORT 1 //是否支持fs文件系统接口测试



#ifdef __cplusplus
}
#endif
#endif

