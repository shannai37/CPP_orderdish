#ifndef DATALIST_H
#define DATALIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 菜单结构体 做为数据
typedef struct menu
{
	int menuID;
	char menuName[20];
	double price;
	int num;	
}MENU;

typedef struct user
{
	char account[20];
	char password[20];
	int role;	
}USER;

//// 链表的结点结构体
//typedef struct list
//{
//	MENU data; // 数据域 : 菜单结构体变量
//	struct list * pnext; // 指针域 ：指向下一个节点的指针
//		
//}LIST; 

// 通用链表的结点结构体 
typedef struct list
{
	void * data; // 数据域 : 任意数据地址 
	struct list * pnext; // 指针域 ：指向下一个节点的指针
		
}LIST; 

// 创建链表： 创建一个头结点 
LIST *  New_List_Init();
// 尾部添加节点 
void New_List_pushback(LIST * head, void *pdata,int length); 
// 获取链表长度 
int New_List_getSize(LIST * head); 
//
// 给定序号 获取单个节点
LIST * New_getNodeByPos(LIST * head,int position); 
//
// 从链表中删除指定节点 
int New_deleteNodeByPos(LIST * head,int position);
//
// 在指定位置插入节点 
int New_List_insert(LIST *head,void *pdata,int length,int position); 
//
// 清空链表(保留头节点) 
void New_List_clear(LIST *head);
//
// 摧毁链表(不保留头节点)
void New_List_destroy(LIST **head); 
#endif 

