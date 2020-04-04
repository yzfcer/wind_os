/*********************************************************************************
  *Copyright(C),2017-2020,yzfcer@163.com
  *FileName:    wind_xml.c
  *Author:      Jason Zhou
  *Version:     1.0
  *Date:        2020/03/24
  *Description: 
  *Others:      An external mutex is required when used in a multithreaded environment,
  *History:  
     1.Date:
       Author:
       Modification:
**********************************************************************************/
#include "wind_xml.h"
#include "wind_debug.h"
#include "wind_macro.h"
#include "wind_heap.h"
#include "wind_string.h"
#include "wind_dlist.h"
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus
#define NODE_TO_XNODE(node) (w_xmlnode_s *)(((w_uint8_t*)(node))-((w_addr_t)&(((w_xmlnode_s*)0)->tree.treenode)))
static w_bool_t is_xml_name_valid(char *name)
{
    w_int32_t i;
    WIND_ASSERT_RETURN(name != W_NULL,W_FALSE);

    for(i = 0;name[i] != 0;i ++)
    {
        if(IS_ALPHABET(name[i]))
            continue;
        else if(IS_DECIMAL(name[i]))
            continue;
        else if(name[i] == '_')
            continue;
        else
            return W_FALSE;
    }
    return W_TRUE;
}

static w_err_t xattr_destroy(w_xmlattr_s *attr)
{
    WIND_CHECK_RETURN(attr != W_NULL,W_ERR_PTR_NULL);
    if(attr->attr_name)
        wind_free(attr->attr_name);
    if(attr->attr_value)
        wind_free(attr->attr_value);
    wind_free(attr);
    return W_ERR_OK;
}


w_err_t wind_xml_parse(w_xmlnode_s *xnode,char *xmlstr,w_int32_t len)
{
    //w_int32_t len;
    //xml_fsm_s *fsm;
    return W_ERR_FAIL;
}

w_err_t wind_xml_print(w_xmlnode_s *xnode)
{
    w_int32_t i;
    w_err_t err;
    w_dnode_s *dnode;
    w_xmlattr_s *attr;
    //w_tree_s *tree;
    w_xmlnode_s *tmp_xndoe;
    char prefix[MAX_XNODE_LEVEL+1];
    WIND_ASSERT_RETURN(xnode != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(xnode->name != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(xnode->level < MAX_XNODE_LEVEL,W_ERR_FAIL);
    err = W_ERR_OK;
    wind_memset(prefix,0,sizeof(prefix));
    for(i = 0;i < xnode->level;i ++)
        prefix[i] = '\t';
    wind_printf(prefix);
    wind_printf("<%s ",xnode->name);
    foreach_node(dnode,&xnode->attrlist)
    {
        attr = NODE_TO_XATTR(dnode);
        wind_printf("\"%s\"=\"%s\" ",attr->attr_name,attr->attr_value);
    }
    wind_printf(">");
    if(xnode->is_leaf)
        wind_printf("%s",xnode->value);
    else if(dlist_head(&xnode->tree.child_list))
    {
        wind_printf("\r\n");
        foreach_node(dnode,&xnode->tree.child_list)
        {
            //tree = NODE_TO_XNODE(dnode);
            tmp_xndoe = NODE_TO_XNODE(dnode);
            err = wind_xml_print(tmp_xndoe);
            WIND_ASSERT_BREAK(err == W_ERR_OK,err,"print child xnode failed");
        }
        wind_printf("\r\n");
    }
    wind_printf("</%s>\r\n",xnode->name);
    return W_ERR_OK;
}


w_xmlnode_s *wind_xmlnode_create(char *name,w_uint8_t is_leaf)
{
    w_err_t err;
    w_bool_t isvalid;
    w_xmlnode_s *xnode = (w_xmlnode_s *)W_NULL;
    do
    {
        err = W_ERR_OK;
        isvalid = is_xml_name_valid(name);
        WIND_ASSERT_BREAK(isvalid == W_TRUE,W_ERR_INVALID,"node name is invalid");
        xnode = (w_xmlnode_s *)wind_malloc(sizeof(w_xmlnode_s));
        wind_memset(xnode,0,sizeof(w_xmlnode_s));
        xnode->name = (char*)wind_salloc(name,0);
        WIND_ASSERT_BREAK(xnode->name != W_NULL,W_ERR_MEM,"alloc xnode name failed");
        xnode->is_leaf = is_leaf;
    }while(0);
    if(err != W_ERR_OK)
    {
        wind_xmlnode_destroy(xnode);
        xnode = (w_xmlnode_s *)W_NULL;
    }
    return xnode;
}

w_err_t wind_xmlnode_destroy(w_xmlnode_s *xnode)
{
    w_err_t err;
    w_xmlattr_s *attr;
    w_dnode_s *dnode;
    w_xmlnode_s *child;
    WIND_ASSERT_RETURN(xnode != W_NULL,W_ERR_PTR_NULL);
    if(xnode->name != W_NULL)
        wind_free(xnode->name);
    if(xnode->value != W_NULL)
        wind_free(xnode->value);
    foreach_node(dnode,&xnode->attrlist)
    {
        attr = NODE_TO_XATTR(dnode);
        xattr_destroy(attr);
    }
    err = W_ERR_OK;
    for(;;)
    {
        child = wind_xmlnode_get_child(xnode);
        WIND_CHECK_BREAK(child != W_NULL,W_ERR_OK);
        wind_xmlnode_remove(xnode,child);
        err = wind_xmlnode_destroy(child);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"destroy xnode failed");
    }
    return err;
    
}



w_xmlnode_s *wind_xmlnode_get_parent(w_xmlnode_s *xnode)
{
    w_dnode_s *dnode;
    w_xmlnode_s *tmp_xnode;
    WIND_CHECK_RETURN(xnode != W_NULL,(w_xmlnode_s *)W_NULL);
    WIND_CHECK_RETURN(xnode->tree.parent != W_NULL,(w_xmlnode_s *)W_NULL);
    dnode = &xnode->tree.parent->treenode;
    tmp_xnode = NODE_TO_XNODE(dnode);
    return tmp_xnode;
}

w_xmlnode_s *wind_xmlnode_get_child(w_xmlnode_s *xnode)
{
    w_dnode_s *dnode;
    w_xmlnode_s *tmp_xnode;
    WIND_CHECK_RETURN(xnode != W_NULL,(w_xmlnode_s *)W_NULL);
    WIND_CHECK_RETURN(xnode->tree.child_list.head != W_NULL,(w_xmlnode_s *)W_NULL);
    dnode = xnode->tree.child_list.head;
    tmp_xnode = NODE_TO_XNODE(dnode);
    return tmp_xnode;
}

w_xmlnode_s *wind_xmlnode_get_next(w_xmlnode_s *xnode)
{
    w_dnode_s *dnode;
    w_xmlnode_s *tmp_xnode;
    WIND_CHECK_RETURN(xnode != W_NULL,(w_xmlnode_s *)W_NULL);
    WIND_CHECK_RETURN(xnode->tree.treenode.next != W_NULL,(w_xmlnode_s *)W_NULL);
    dnode = xnode->tree.treenode.next;
    tmp_xnode = NODE_TO_XNODE(dnode);
    return tmp_xnode;
}

w_xmlnode_s *wind_xmlnode_get_prev(w_xmlnode_s *xnode)
{
    w_dnode_s *dnode;
    w_xmlnode_s *tmp_xnode;
    WIND_CHECK_RETURN(xnode != W_NULL,(w_xmlnode_s *)W_NULL);
    WIND_CHECK_RETURN(xnode->tree.treenode.prev != W_NULL,(w_xmlnode_s *)W_NULL);
    dnode = xnode->tree.treenode.prev;
    tmp_xnode = NODE_TO_XNODE(dnode);
    return tmp_xnode;
}

w_err_t wind_xmlnode_modify(w_xmlnode_s *xnode,char *node_value)
{
    WIND_ASSERT_RETURN(xnode != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(xnode->is_leaf,W_ERR_INVALID);
    if(xnode->value != W_NULL)
        wind_free(xnode->value);
    xnode->value = (char*)W_NULL;
    if(node_value != W_NULL)
        xnode->value = (char*)wind_salloc(node_value,0);
    return W_ERR_OK;
}

w_err_t wind_xmlnode_insert(w_xmlnode_s *parent,w_xmlnode_s *child)
{
    w_err_t err;
    WIND_ASSERT_RETURN(parent != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(child != W_NULL,W_ERR_PTR_NULL);
    do
    {
        WIND_ASSERT_BREAK(parent->level < MAX_XNODE_LEVEL - 1,W_ERR_FAIL,"xnode level is too deep");
        err = wind_tree_insert_child(&parent->tree,&child->tree);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"insert child failed");
        child->level = parent->level + 1;
        WIND_ASSERT_BREAK(parent->node_cnt < 255,W_ERR_FAIL,"child node is too many");
        parent->node_cnt ++;
    }while(0);
    return err;
}

w_err_t wind_xmlnode_remove(w_xmlnode_s *parent,w_xmlnode_s *child)
{
    w_err_t err;
    WIND_ASSERT_RETURN(parent != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(child != W_NULL,W_ERR_PTR_NULL);
    do
    {
        err = wind_tree_remove_child(&parent->tree,&child->tree);
        WIND_ASSERT_BREAK(err == W_ERR_OK,err,"remove child failed");
        WIND_ASSERT_BREAK(parent->node_cnt > 0,W_ERR_FAIL,"child node count error");
        parent->node_cnt --;
        child->level = 0;
    }while(0);
    return err;
}



w_err_t wind_xmlnode_insert_attr(w_xmlnode_s *xnode,char *attr_name,char *attr_value)
{
    w_err_t err;
    w_xmlattr_s *attr = (w_xmlattr_s *)W_NULL;
    WIND_ASSERT_RETURN(xnode != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(attr_name != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(attr_value != W_NULL,W_ERR_PTR_NULL);
    do
    {
        err = W_ERR_OK;
        attr = (w_xmlattr_s *)wind_malloc(sizeof(w_xmlattr_s));
        WIND_ASSERT_BREAK(attr != W_NULL,W_ERR_MEM,"alloc attr failed");
        wind_memset(attr,0,sizeof(w_xmlattr_s));
        attr->attr_name = (char*)wind_salloc(attr_name,0);
        WIND_ASSERT_BREAK(attr != W_NULL,W_ERR_MEM,"alloc attr name failed");
        attr->attr_value = (char*)wind_salloc(attr_value,0);
        WIND_ASSERT_BREAK(attr != W_NULL,W_ERR_MEM,"alloc attr value failed");
        dlist_insert_tail(&xnode->attrlist,&attr->attr_node);
        WIND_ASSERT_BREAK(xnode->attr_cnt < 255,W_ERR_FAIL,"attr is too many");
        xnode->attr_cnt ++;
    }while(0);
    if(err != W_ERR_OK)
    {
        xattr_destroy(attr);
    }
    return err;
}

w_err_t    wind_xmlnode_modify_attr(w_xmlnode_s *xnode,char *attr_name,char *attr_value)
{
    w_xmlattr_s *attr;
    WIND_ASSERT_RETURN(xnode != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(attr_name != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(attr_value != W_NULL,W_ERR_PTR_NULL);
    attr = wind_xmlnode_get_attr(xnode,attr_name);
    WIND_ASSERT_RETURN(attr != W_NULL,W_ERR_NO_OBJ);
    if(attr->attr_value != W_NULL)
        wind_free(attr->attr_value);
    attr->attr_value = (char*)wind_salloc(attr_value,0);
    WIND_ASSERT_RETURN(attr->attr_value != W_NULL,W_ERR_MEM);
    return W_ERR_OK;
}

w_xmlattr_s *wind_xmlnode_get_attr(w_xmlnode_s *xnode,char *attr_name)
{
    w_dnode_s *dnode;
    w_xmlattr_s *attr = (w_xmlattr_s *)W_NULL;
    WIND_ASSERT_RETURN(xnode != W_NULL,(w_xmlattr_s *)W_NULL);
    WIND_ASSERT_RETURN(attr_name != W_NULL,(w_xmlattr_s *)W_NULL);
    foreach_node(dnode,&xnode->attrlist)
    {
        attr = NODE_TO_XATTR(dnode);
        if(wind_strcmp(attr->attr_name,attr_name) == 0)
            return attr;
    }
    return (w_xmlattr_s *)W_NULL;
}

w_err_t wind_xmlnode_delete_attr(w_xmlnode_s *xnode,char *attr_name)
{
    w_err_t err;
    w_dnode_s *dnode;
    w_xmlattr_s *attr = (w_xmlattr_s *)W_NULL;
    WIND_ASSERT_RETURN(xnode != W_NULL,W_ERR_PTR_NULL);
    WIND_ASSERT_RETURN(attr_name != W_NULL,W_ERR_PTR_NULL);
    do
    {
        err = W_ERR_OK;
        foreach_node(dnode,&xnode->attrlist)
        {
            attr = NODE_TO_XATTR(dnode);
            if(wind_strcmp(attr->attr_name,attr_name) == 0)
                break;
        }
        WIND_ASSERT_BREAK(dnode != W_NULL,W_ERR_NO_OBJ,"no such a attr:%s",attr_name);
        WIND_ASSERT_BREAK(xnode->attr_cnt > 0,W_ERR_FAIL,"attr count error");
        xnode->attr_cnt --;
        dlist_remove(&xnode->attrlist,&attr->attr_node);
        err = xattr_destroy(attr);
    }while(0);
    return err;
}




#ifdef __cplusplus
}
#endif // #ifdef __cplusplus


