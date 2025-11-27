#include "CAdminWin.h"


/*
函数名称：CAdminWin_init
函数功能：显示管理员主界面
*/
void CAdminWin_init()
{
	// 创建窗口
	CWIN win = {15, 3, 60, 25, 0, 0};
	
	// 按钮配置数组 
	ButtonConfig buttons[] = {
		{"台桌管理", 30, 10, 20, 3, NULL},         
		{"菜谱管理", 30, 14, 20, 3, CAdminWin_DM},         
		{"人员管理", 30, 18, 20, 3, CAdminWin_PM},   // 跳转人员管理
		{"注销",     25, 23, 12, 3, CLoginWin_init}, // 返回登录
		{"退出",     43, 23, 12, 3, CStartWin_init}  // 返回主菜单
	};
	int buttonCount = 5; // 维护按钮数量，后面我们会根据按钮数量去遍历创建按钮和处理跳转 
	
	// 添加标题
	CONTROL title = {LABEL, 35, 6, 0, 0, "=== 管理员界面 ==="};
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
	
	// 绘制和运行
	printWindow(&win);
	winRun(&win);
	
	// 处理按钮点击
	if(win.flag >= 1 && win.flag <= buttonCount) 
	{
		int btnIndex = win.flag - 1;
		
		// 特殊处理：第一个按钮功能还没写 
		if(btnIndex == 0) 
		{
			system("cls");
			printf("\n\n 功能开发中...\n\n");
			Sleep(1500);
			system("cls");
			CAdminWin_init();  // 返回本界面
		} 
		else 
		{
			// 其他按钮正常跳转
			jumpToWindow(buttons[btnIndex].jump);
		}
	}
}
