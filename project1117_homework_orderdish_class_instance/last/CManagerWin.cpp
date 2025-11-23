#include "CManagerWin.h"

void CManagerWin_init()
{
	//创建窗口
	CWIN win = {15, 3, 60, 20, 0, 0};
	
	// 按钮配置表      文字   ,  x  , y ,  宽 , 高 ,  跳转函数
	ButtonConfig buttons[] = {
		
		{"营收汇总", 30, 10, 20, 3, NULL},         // 功能未开发
		{"注销",     25, 15, 12, 3, CLoginWin_init}, // 返回登录界面
		{"退出",     43, 15, 12, 3, CStartWin_init}  // 返回主菜单
	};
	
	int buttonCount = 3; // 维护按钮数量，后面我们会根据按钮数量去遍历创建按钮和处理跳转 
	
	//创建标题标签
	CONTROL title = {LABEL, 35, 6, 0, 0, "=== 经理界面 ==="};
	addControl(&win, &title);

	
	// 循环创建按钮
	int i;
	for(i = 0; i < buttonCount; i++) 
	{
		CONTROL btn = {BUTTON, 
		               buttons[i].x, 
		               buttons[i].y, 
		               buttons[i].width, 
		               buttons[i].height, 
		               ""};
		strcpy(btn.context, buttons[i].text);
		addControl(&win, &btn);
	}
	
	//底部提示信息
	CONTROL tip = {LABEL, 28, 21, 0, 0, "Press any key to continue"};
	addControl(&win, &title);

	
	//绘制整个窗口
	printWindow(&win);
	
	// 运行窗口
	winRun(&win);
	
	// 对应关系：
	// win.arr[0] = 标题
	// win.arr[1] = 营收汇总按钮 → flag = 1 → buttons[0]
	// win.arr[2] = 注销按钮     → flag = 2 → buttons[1]
	// win.arr[3] = 退出按钮     → flag = 3 → buttons[2]
	// win.arr[4] = 底部提示
	if(win.flag >= 1 && win.flag <= buttonCount) 
	{
		int btnIndex = win.flag - 1;
		
		// 特殊处理：营收汇总功能未开发
		if(btnIndex == 0) 
		{
			system("cls");
			printf("\n\n 功能开发中...\n\n");
			Sleep(1500);
			system("cls");
			CManagerWin_init();  // 返回本界面
		} 
		else 
		{
			// 注销和退出：正常跳转
			jumpToWindow(buttons[btnIndex].jump);
		}
	}
	
	
}
