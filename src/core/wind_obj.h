/****************************************Copyright (c)**************************************************
**                                       God's harbor
**
**                                       yzfcer@163.com
**
**--------------File infomation-------------------------------------------------------------------------
** FileName    : wind_obj.h
** Author      : Jason Zhou
** Last Date   : 2019.01.28
** Description : Kernel object common abstraction
**              
**--------------History---------------------------------------------------------------------------------
** Author      : Jason Zhou
** Version     : v1.0
** Date        : 2019.01.28
** Description : First version
**
**--------------Cureent version-------------------------------------------------------------------------
** Modify      : Jason Zhou
** Date        : 2019.01.28
** Description : 
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifndef WIND_OBJ_H__
#define WIND_OBJ_H__
#include "wind_type.h"
#include "wind_dlist.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

//init an object struct
#define WIND_OBJ(magic,flag,name) {(~magic),0,flag,{(w_dnode_s*)W_NULL,(w_dnode_s*)W_NULL},name}

//Basic object information structure
typedef struct _wind_obj
{
    w_uint32_t magic;  //magic code
    w_uint16_t key;    //Key value, used to speed up object search
    w_uint16_t flag;   //Object attribute tag
    w_dnode_s objnode; //Object list node
    char *name;        //Object name
}w_obj_s;


const char *wind_obj_name(void *obj);
w_obj_s *wind_obj_get(const char *name,w_dlist_s *list);
w_err_t wind_obj_init(w_obj_s *obj,w_uint32_t magic,const char *name,w_dlist_s *list);
w_err_t wind_obj_deinit(w_obj_s *obj,w_uint32_t magic,w_dlist_s *list);
w_err_t wind_obj_register(w_obj_s *obj,w_dlist_s *dlist);
w_err_t wind_obj_unregister(w_obj_s *obj,w_dlist_s *dlist);
w_err_t wind_obj_print_list(w_dlist_s *dlist);

#ifdef __cplusplus
}
#endif
#endif// #ifndef WIND_OBJ_H__

