#ifndef CADMINWIN_DM
#define CADMINWIN_DM


#include "CTool.h" 	 // printTable() 菜名的结构体数组 
#include "CWindow.h" // 窗口结构体 
#include <string.h>  // strcpy
#include "CAdminWin.h" // 调用CAdminWin_init() 
void CAdminWin_DM();

void FillTable_DM(int nowPage, int AllPage, int pageSize);	
#endif
