#include "CAdminWin_DM.h"


int nowPage1 = 1; // 当前页数 

void CAdminWin_DM()
{
	int pageSize = 3; // 每页三条数据 
	int AllPage; //总页数 
	
	int mCount = New_List_getSize(menuList);  // 链表总长度即为总用户数量 
	
	if(mCount == 0) // 一个菜也没有的时候 也要显示 1 / 1 
	{
		AllPage = 1; 
	}
	else
	{ 
		if(mCount % pageSize == 0) 	  // 能整除，不用多开一页 
		{
			 AllPage = mCount / pageSize; 	
		}
		else		// 不能整除，多开一页
		{
			AllPage = mCount / pageSize + 1;	
		} 
	}
	
	
	// 动态生成页码文字
    // sprintf 把格式化的内容写入字符串(不是像printf打印到题目，只是生成了字符串)
	char pageText[20];
	sprintf(pageText, " %d / %d ", nowPage1 , AllPage);
	
	// 窗口
    CWIN win = {10, 2, 70, 26, 0, 0};
    
    // 控件
    CONTROL btn1 = {BUTTON, 18, 23, 14, 3, "上一页"};
    CONTROL page = {LABEL, 35, 24, 0, 0, ""};
    strcpy(page.context, pageText);  // 设置页码
    CONTROL btn2 = {BUTTON, 50, 23, 14, 3, "下一页"};
    
    // 添加控件
    addControl(&win, &btn1);   // 索引0 上一页按钮 
    addControl(&win, &page);   // 索引1 页码 
    addControl(&win, &btn2);   // 索引2 下一页按钮 
    
    // 绘制 
	printWindow(&win);
	FillTable_DM(nowPage1, AllPage, pageSize); // 传入当前页面 
    
    
    // 运行窗口
    winRun(&win);
    
    if(win.flag == 0) // 上一页 
	{
		if(nowPage1 > 1) 
		{
            nowPage1--;
            system("cls");
            CAdminWin_DM();  // 递归调用
        } 
		else 
		{
            gotoxy(30, 28);
            printf("已经是第1页");
            Sleep(1500);
            system("cls");
            CAdminWin_DM();  // 刷新界面
        }
	} 
	
	if(win.flag == 2) // 下一页 
	{
		if(nowPage1 < AllPage) 
		{
            nowPage1++;
            system("cls");
            CAdminWin_DM();  // 递归调用
        } 
		else 
		{
            gotoxy(30, 28);
            printf("已经是最后一页");
            Sleep(1500);
            system("cls");
            CAdminWin_DM();  // 刷新界面
        }
	} 
	
	if(win.flag == -1) //返回逻辑 
	{
		system("cls");                     // 清屏 
        printf("\n\n 正在跳转...\n\n");    
        Sleep(1000);                        // 等待1秒，让用户看到提示 
        system("cls");                     // 再次清屏，准备显示新界面 
		CAdminWin_init();
	}
}

/*
 用来绘制人员管理界面的表格 
*/
void FillTable_DM(int nowPage1, int AllPage, int pageSize)
{
	int i;
	
	// 1.画表格边框
	printTable(13, 5, 64, 16, 4, 4); 
	
	// 2.绘制表头	
    gotoxy(17, 7);   printf("菜编号");     
    gotoxy(33, 7);   printf("菜名");     
    gotoxy(49, 7);   printf("价格");     
    gotoxy(65, 7);   printf("份数");
	
	 // 3. 获取起始位置
    int startArrIndex = (nowPage1 - 1) * pageSize;
    
    // 4. 跳到起始位置 (第一页是0,第二页是3) 
    LIST *p = menuList -> pnext; // 第一个有效数据 
    int count = 0;
    while(p != NULL && count < startArrIndex) 
	{
        p = p -> pnext;
        count++;
    }
    
    // 5. 显示当前页的数据
    int row = 0;
    while(p != NULL && row < pageSize) 
	{
        MENU *m = (MENU*)p->data;
        int dataY = 7 + 4 + (row * 4);
        
        // 显示菜编号 
        gotoxy(17, dataY);   printf("%d", m -> menuID);
        
        // 显示菜名 
        gotoxy(33, dataY);   printf("%s", m -> menuName);  
        
        // 显示价格 
        gotoxy(49, dataY);   printf("%.2f", m -> price);  
        
        // 显示数量 
        gotoxy(65, dataY);
        printf("%d", m -> num);
        
        p = p -> pnext;
        row++;
    }
}
