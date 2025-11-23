#include "CWaiterWin.h"

void CWaiterWin_init()
{
	//创建窗口
	CWIN win = {10, 3, 70, 25, 0, 0};
	
	ButtonConfig buttons[] = 
	{
		{"开桌",             28,  8, 24, 3, NULL},         // 功能未开发
		{"点菜",             28, 12, 24, 3, NULL},         // 功能未开发
		{"营业额查询",       28, 16, 24, 3, NULL},         // 功能未开发
		{"已买/未买单查询",  22, 20, 36, 3, NULL},         // 功能未开发
		{"注销",             25, 25, 12, 3, CLoginWin_init}, // 返回登录
		{"退出",             43, 25, 12, 3, CStartWin_init},  // 返回主菜单
	};
	
	int buttonCount = 6; //	维护按钮数量，后面我们会根据flag去跳转对应的buttons
	
	//创建标题标签
	CONTROL title = {LABEL, 32, 5, 0, 0, "=== 服务员界面 ==="};
	addControl(&win, &title);
	
	// 循环创建按钮 
	int i;
	for(i = 0 ; i < buttonCount ; i++)
	{
		CONTROL btn = {BUTTON,
					   buttons[i].x,	
					   buttons[i].y,
					   buttons[i].width,
					   buttons[i].height,
					   ""};	
	
		//复制文字到控件 
		strcpy(btn.context,buttons[i].text);
		
		//添加到窗口
		addControl(&win,&btn); 
	} 
	
	
	
	//绘制整个窗口
	printWindow(&win);
	
	// 运行窗口
	winRun(&win);
	
	//1-"开桌"  2-"点菜" 3-"营业额查询" 4-"已买/未买单查询" 5-"注销" 6-"退出"
	if(win.flag >= 1 && win.flag <= buttonCount)
	{
		int btnIndex = win.flag - 1;
		
		// 特殊处理：前4个按钮功能未开发
		if(btnIndex < 4) 
		{
			system("cls");
			printf("\n\n 功能开发中...\n\n");
			Sleep(1500);
			system("cls");
			CWaiterWin_init();  // 返回本界面
		} 
		else 
		{
			// 注销和退出：正常跳转
			jumpToWindow(buttons[btnIndex].jump);
		}
	}
}
