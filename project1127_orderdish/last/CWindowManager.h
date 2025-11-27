#ifndef CWINDOWMANAGER_H
#define CWINDOWMANAGER_H

#include <stdlib.h>
#include <windows.h>

/* 
  函数指针类型定义
  WindowFunc 是一个类型名，是一个指向无参数无返回值函数的指针
 作用：用来存储界面函数的地址，比如：
 CLoginWin_init 的地址  	登录 
 CRegisterWin_init 的地址	注册 
 CAdminWin_init 的地址		管理员 
*/ 
typedef void (*WindowFunc)();

// WindowFunc jump1;   // 等价于 void (*jump1)();

/* 
	按钮配置结构体 
	整体逻辑中，只有按钮是具有跳转逻辑的。
	我们可以对按钮进行配置，把 按钮的所有信息 打包在一起 
    包括 文字、左上角坐标、尺寸、点击后跳转至哪个函数（jump） 
	注意！！！！容易混淆 这里只是按钮配置结构体，不是真正的控件
 	真正的控件是 CONTROL，逻辑是 从按钮配置结构体读取信息，然后去生成真正的CONTROL控件 
*/ 
typedef struct {
    char text[20];      // 按钮显示的文字
    int x, y;           // 按钮左上角坐标
    int width, height;  // 按钮的宽度和高度
    WindowFunc jump; 	// 点击按钮后要跳转的函数（函数指针）
} ButtonConfig;

/*
	窗口跳转函数 
	进行之间重复的清屏、提示、跳转到目标窗口的函数
	参数：targetWindow -> 要跳转到的窗口函数的地址
*/
	void jumpToWindow(WindowFunc targetWindow);

#endif
