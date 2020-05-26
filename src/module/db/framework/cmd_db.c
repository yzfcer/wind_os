/****************************************Copyright (c)**************************************************
**                                       God's harbor
**
**                                       yzfcer@163.com
**
**--------------File infomation-------------------------------------------------------------------------
** FileName    : cmd_DB.c
** Author      : Jason Zhou
** Last Date   : 
** Description : DB模块操作命令
**              
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : 
** Date        : 
** Description : 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "wind_cmd.h"
#include "db_entry.h"
#if (CMD_DB_SUPPORT)

static w_err_t cmd_db_list(w_int32_t argc,char **argv)
{
    return db_entry_print_all();
}

static w_err_t cmd_db_detail(w_int32_t argc,char **argv)
{
    w_db_s *db;
    char *dbname = argv[2];
    db = db_get_byname(dbname);
    WIND_ASSERT_RETURN(db != W_NULL,W_ERR_NO_OBJ);
    return db_entry_print_data(db);
}

static w_err_t cmd_db_create(w_int32_t argc,char **argv)
{
    char *dbname = argv[2];
    return db_entry_create(dbname,DB_ATTR_DEFAULT_ITEM);
}

static w_err_t cmd_db_delete(w_int32_t argc,char **argv)
{
    char *dbname = argv[2];
    w_db_s *entry = db_get_byname(dbname);
    return db_entry_destroy(entry);
}

static w_cmd_handle_s cmd_hanlde_list[] = 
{
    {"list",cmd_db_list},
    {"detail",cmd_db_detail},
    {"create",cmd_db_create},
    {"delete",cmd_db_delete},
};


COMMAND_DISC(db)
{
    wind_printf("to operate db system.\r\n");
}

COMMAND_USAGE(db)
{
    wind_printf("db list:--to show DB list.\r\n");
    wind_printf("db detail <dbname>:--to show DB list.\r\n");
    wind_printf("db create <dbname>:--to create DB model.\r\n");
    wind_printf("db delete <dbname>:--to delete DB model.\r\n");
}

COMMAND_MAIN(db,argc,argv)
{
    w_int32_t i;
    WIND_ASSERT_RETURN(argc >= 2,W_ERR_INVALID);
    for(i = 0;i < sizeof(cmd_hanlde_list)/sizeof(w_cmd_handle_s);i ++)
    {
        if(wind_strcmp(argv[1],cmd_hanlde_list[i].keyword) == 0)
        {
            if(cmd_hanlde_list[i].exec != W_NULL)
                return cmd_hanlde_list[i].exec(argc,argv);
        }
    }
    return W_ERR_OK;
}

COMMAND_DEF(db);
#endif
