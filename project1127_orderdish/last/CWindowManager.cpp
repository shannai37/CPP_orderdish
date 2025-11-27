#include "CWindowManager.h"
#include <stdio.h>

/*
函数名称：jumpToWindow
函数功能：
	统一处理窗口跳转，避免在每个窗口都重复写清屏、提示、跳转的代码
	"跳转助手" -> 负责完成跳转的所有准备工作
参数列表：
	WindowFunc targetWindow : 目标窗口的函数指针
		如果是 NULL -> 表示用户点击了"退出"按钮，需要退出程序
		如果不是 NULL -> 表示要跳转到某个具体窗口

函数返回值：无

*/
void jumpToWindow(WindowFunc targetWindow) 
{
    if(targetWindow != NULL)  // 跳转到其他窗口(并非退出程序)
	{
        
        system("cls");                     // 清屏 
        printf("\n\n 正在跳转...\n\n");    
        Sleep(1000);                        // 等待1秒，让用户看到提示 
        system("cls");                     // 再次清屏，准备显示新界面 
        
		//例如：如果targetWindow = CLoginWin_init（函数地址）
		//	    这里就等价于调用 CLoginWin_init(); 从而跳转到登录界面
        targetWindow();  // 通过函数指针调用目标函数
        
    } 
	else // targetWindow为NULL，表示退出程序 
	{
        
        system("cls");
        printf("\n\n 感谢使用！再见！\n\n");
        Sleep(2000);                       // 等待2秒
        exit(0);                           // 终止程序 
    }
}
