#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <stdio.h> 
#include <stdlib.h>
#include "DataList.h"
#include <string.h> // sprintf 

// 保存菜单链表到文件 
void saveMenuList(LIST * head,char *filename);

// 从文件中加载出菜单链表
LIST* getMenuList(char *filename); 


// 保存用户链表到文件 
void saveUserList(LIST * head,char *filename);

// 从文件中加载出用户链表
LIST* getUserList(char *filename); 

#endif
