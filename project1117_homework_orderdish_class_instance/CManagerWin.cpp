#include "CManagerWin.h"


#include "CManagerWin.h"
#include "CButton.h"
#include "CLabel.h"

// CManagerWin 类
// 经理窗口类,继承自 CWindow
// 功能:显示经理菜单,包含营业汇总、注销、退出按钮

// 无参构造函数
// 创建经理窗口,添加标题和3个按钮
CManagerWin::CManagerWin() 
    : CWindow(15, 3, 60, 20)  // 窗口位置和大小
{
    // 1. 标题
    CLabel* title = new CLabel(Label, 35, 6, 0, 0, " 经理界面 ");
    this->addControl(title);
    
    // 2. 营业汇总按钮
    CButton* btn1 = new CButton(BUTTON, 30, 10, 20, 3, "营业汇总");
    this->addControl(btn1);
    
    // 3. 注销按钮
    CButton* btn2 = new CButton(BUTTON, 25, 15, 12, 3, "注销");
    this->addControl(btn2);
    
    // 4. 退出按钮
    CButton* btn3 = new CButton(BUTTON, 43, 15, 12, 3, "退出");
    this->addControl(btn3);
}

// 析构函数
// 释放所有控件的内存
CManagerWin::~CManagerWin()
{
    // 释放所有控件
    for(int i = 0; i < this->count; i++) 
	{
        if(this->arr[i] != NULL) 
		{
            delete this->arr[i];
            this->arr[i] = NULL;
        }
    }
}

// 处理业务逻辑
// 根据用户点击的按钮执行不同的操作
// flag == 1: 营业汇总按钮 - 功能未实现
// flag == 2: 注销按钮 - 返回登录窗口
// flag == 3: 退出按钮 - 返回初始窗口
// flag == -1: ESC键 - 返回初始窗口
void CManagerWin::handle()
{
    if(this->flag == 1) {  // 营业汇总按钮
        // 营业汇总功能未实现
        system("cls");
        printf("\n\n 功能开发中...\n\n");
        Sleep(1500);
        system("cls");
        
        // 返回经理窗口
        CManagerWin* managerWin = new CManagerWin();
        managerWin->show();
        managerWin->run();
        managerWin->handle();
        delete managerWin;
    }
    else if(this->flag == 2) {  // 注销按钮
         system("cls");
		 // 返回登录窗口
         CLoginWin* loginWin = new CLoginWin();
         loginWin->show();
         loginWin->run();
         loginWin->handle();
         delete loginWin;
    }
    else if(this->flag == 3 || this->flag == -1) {  // 退出按钮或ESC键
         system("cls");
		 // 返回初始窗口
         CInitWin* initWin = new CInitWin();
         initWin->show();
         initWin->run();
         initWin->handle();
         delete initWin;
    }
}
