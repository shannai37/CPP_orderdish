#include "CInitWin.h"



// CInitWin 类
// 初始窗口类,继承自 CWindow
// 功能:显示开始菜单,包含注册、登录、退出按钮

// 无参构造函数
// 创建初始窗口,添加标题和3个按钮
CInitWin::CInitWin()
:CWindow(15,3,50,25)  // 赋默认值传给父类构造函数  
{
	// 1.标题
	CLabel * title = new CLabel(Label,25,7,0,0,"欢迎使用点菜系统");
	this->addControl(title);
	
	// 2.注册按钮
	CButton * btn1 = new CButton(BUTTON,32,11,16,3,"注 册");
	this->addControl(btn1);
	
	// 3.登录按钮
	CButton * btn2 = new CButton(BUTTON,32,16,16,3,"登 录");
	this->addControl(btn2);
	
	// 4.退出按钮 
	CButton * btn3 = new CButton(BUTTON,32,21,16,3,"退 出");
	this->addControl(btn3);  
}


//处理业务逻辑
// 根据用户点击的按钮执行不同的操作
// flag == 1: 注册按钮 - 跳转到注册窗口
// flag == 2: 登录按钮 - 跳转到登录窗口
// flag == 3: 退出按钮 - 退出程序
// flag == -1: ESC键 - 退出程序
void CInitWin::handle()
{
	
	// 状态机模式 不会一直 handle()阻塞进入下一个handle() ，栈深度只有一层！ 
	if(this->flag == 1)  // 注册按钮
    {
        this->result = 1;
    }
    else if(this->flag == 2)  // 登录按钮
    {
        this->result = 2;
    }
    else if(this->flag == 3 || this->flag == -1)  // 退出按钮或ESC
    {
        this->result = 0;
    }
//	if(this->flag == 1) // 注册按钮 
//	{
//		
//		system("cls"); // 清屏
//		// 创建注册窗口
//	   	CRegisterWin* registerwin = new CRegisterWin();
//	    
//	    // 显示窗口
//	    registerwin->show();
//	    
//	    // 运行窗口(处理键盘输入)
//	    registerwin->run();
//	    
//	    // 处理业务逻辑
//	    registerwin->handle();
//	    
//	    // 释放内存
//	    delete registerwin;	
//	}
//	else if(this->flag == 2) // 登录按钮 
//	{
//		system("cls"); // 清屏
//		 
//		CLoginWin* loginWin = new CLoginWin();
//		loginWin->show(); 	// 窗口大边框+内部控件 绘制 
//		loginWin->run();  	// 光标移动+按键输入   
//		loginWin->handle();	// CLoginWin窗口的业务逻辑 
//		// 释放内存 会阻塞在“光标移动+按键输入”中，
//		// 直到用户操作完（确定或取消），处理完业务逻辑才会释放内存 
//		delete loginWin;	// 释放内存 
//	}
//	else if(this->flag == 3 || this->flag == -1) // 退出按钮
//	{
//		return;	
//	} 
}

// 析构函数
// 释放所有控件内存
CInitWin::~CInitWin()
{
	for(int i = 0 ; i < this->count ; i++)
	{
		if(this->arr[i] != NULL)
		{
			delete this->arr[i];
			this->arr[i] = NULL;
		}	
	}	
}
