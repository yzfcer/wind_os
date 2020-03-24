/*********************************************************************************
  *Copyright(C),2017-2020,yzfcer@163.com
  *FileName:    wind_xml.h
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
#ifndef WIND_XML_H__
#define WIND_XML_H__
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#define MAX_XNODE_LEVEL 15
#define TREE_TO_XNODE(tree) (w_xmlnode_s*)(((w_uint8_t*)(tree))-((w_addr_t)&(((w_xmlnode_s*)0)->tree)))
#define NODE_TO_XATTR(node) (w_xmlattr_s*)(((w_uint8_t*)(node))-((w_addr_t)&(((w_xmlattr_s*)0)->node)))

//XML node attribution struct
typedef struct
{
    w_dnode_s node;  //xml-node attribution 
    char *attr_name; //xml-node attribution name
    char *attr_value;//xml-node attribution value
}w_xmlattr_s;



//XML node struct
typedef struct
{
    w_tree_s tree;      //xml node tree struct
    char *name;         //xml node name
    char *value;        //xml node value,sometimes null if has children
    w_uint8_t attr_cnt; //xml node attribution count
    w_uint8_t node_cnt; //tree child node count
    w_uint8_t level;    //tree node level
    w_dlist_s attrlist; //xml node attribution list,see w_xmlattr_s
}w_xmlnode_s;


//xml tree infomation struct
typedef struct
{
    w_xmlnode_s *version; //
    w_xmlnode_s *root;
    
}w_xml_s;

w_err_t wind_xml_parse(w_xmlnode_s *xnode,char *xmlstr,w_int32_t len);
w_err_t wind_xml_print(w_xmlnode_s *xnode);

w_xmlnode_s *wind_xmlnode_create(char *name);
w_err_t      wind_xmlnode_destroy(w_xmlnode_s *xnode);
w_xmlnode_s *wind_xmlnode_get_parent(w_xmlnode_s *xnode);
w_xmlnode_s *wind_xmlnode_get_child(w_xmlnode_s *xnode);
w_xmlnode_s *wind_xmlnode_get_next(w_xmlnode_s *xnode);
w_xmlnode_s *wind_xmlnode_get_prev(w_xmlnode_s *xnode);
w_err_t      wind_xmlnode_insert(w_xmlnode_s *parent,w_xmlnode_s *child);
w_err_t      wind_xmlnode_remove(w_xmlnode_s *parent,w_xmlnode_s *child);

w_xmlattr_s *wind_xmlnode_get_attr(w_xmlnode_s *xnode,char *attr_name);
w_err_t      wind_xmlnode_insert_attr(w_xmlnode_s *xnode,char *attr_name,char *attr_value);
w_err_t      wind_xmlnode_modify_attr(w_xmlnode_s *xnode,char *attr_name,char *attr_value);
w_err_t      wind_xmlnode_delete_attr(w_xmlnode_s *xnode,char *attr_name);


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif //#ifndef WIND_XML_H__
