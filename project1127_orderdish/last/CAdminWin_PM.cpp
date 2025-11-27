#include "CAdminWin_PM.h"

int nowPage = 1; //当前页码 

/*
 管理员界面下的人员管理界面
*/
void CAdminWin_PM() 
{
    int pageSize = 3;
    int AllPage;
    
	int uCount = New_List_getSize(userList);  // userList链表总长度即为总用户数量 

	if(uCount == 0) // 如果一个用户都没，那也要显示为 1 / 1
	{  
    	AllPage = 1;
	} 
	else 			// 有用户
	{
    	if(uCount % pageSize == 0) // 能整除，不用多开一页 
		{  
        	AllPage = uCount / pageSize;
   		} 
		else // 不能整除，多开一页
		{
        	AllPage = uCount / pageSize + 1;
    	}
	}
    
    // 动态生成页码文字
    // sprintf 把格式化的内容写入字符串(不是像printf打印到题目，只是生成了字符串) 
    char pageText[20];
    sprintf(pageText, " %d / %d ", nowPage, AllPage); 
    
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
	FillTable(nowPage, AllPage, pageSize); // 传入当前页面 
    
    
    // 运行窗口
    winRun(&win);
    
    // 上一页
    if(win.flag == 0) 
	{
        if(nowPage > 1) 
		{
            nowPage--;
            system("cls");
            CAdminWin_PM();  // 递归调用
        } 
		else 
		{
            gotoxy(30, 28);
            printf("已经是第1页");
            Sleep(1500);
            system("cls");
            CAdminWin_PM();  // 刷新界面
        }
    }
    // 下一页
    else if(win.flag == 2) 
	{
        if(nowPage < AllPage) 
		{
        	nowPage++;
            system("cls");
            CAdminWin_PM();
        } 
		else 
		{
            gotoxy(30, 28);
            printf("已经是最后一页");
            Sleep(1500);
            system("cls");
            CAdminWin_PM();
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
 用来绘制菜谱管理界面的表格 
*/
void FillTable(int currentPage, int AllPage, int pageSize) 
{
    int i;
    
    // 1.画表格边框
    printTable(13, 5, 64, 16, 4, 4);
    
    // 2.绘制表头
   	gotoxy(17, 7);   printf("序号");     
    gotoxy(33, 7);   printf("账号");     
    gotoxy(49, 7);   printf("密码");     
    gotoxy(65, 7);   printf("角色");
    
    // 3. 获取起始位置
    int startIndex = (currentPage - 1) * pageSize;
    
    // 4. 跳到起始位置 (第一页是0,第二页是3) 
    LIST *p = userList -> pnext; // 第一个有效数据 
    int count = 0;
    while(p != NULL && count < startIndex) 
	{
        p = p -> pnext;
        count++;
    }
    
    // 5. 显示当前页的数据
    int row = 0;
    while(p != NULL && row < pageSize) {
        USER *u = (USER*)p->data;
        int dataY = 7 + 4 + (row * 4);
        
        // 显示序号
        gotoxy(17, dataY);   printf("%d", startIndex + row + 1);
        
        // 显示账号
        gotoxy(33, dataY);   printf("%s", u -> account);  
        
        // 显示密码
        gotoxy(49, dataY);   printf("%s", u -> password);  
        
        // 显示角色
        gotoxy(65, dataY);
        if(u->role == 1) printf("管理员");
        else if(u->role == 2) printf("经理");
        else if(u->role == 3) printf("服务员");
        
        p = p -> pnext;
        row++;
    }
}
