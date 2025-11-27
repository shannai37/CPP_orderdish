#include "CAdminWin.h"


// CAdminWin 类
// 管理员窗口类,继承自 CWindow
// 功能:显示管理员菜单,包含台面管理、菜单管理、人员管理、注销、退出按钮

// 无参构造函数
// 创建管理员窗口,添加标题和5个按钮
CAdminWin::CAdminWin() 
    : CWindow(15, 3, 60, 25)  // 窗口位置和大小
{
    // 1. 标题
    CLabel* title = new CLabel(Label, 35, 6, 0, 0, " 管理员界面 ");
    this->addControl(title);
    
    // 2. 台面管理按钮
    CButton* btn1 = new CButton(BUTTON, 30, 10, 20, 3, "台桌管理");
    this->addControl(btn1);
    
    // 3. 菜单管理按钮
    CButton* btn2 = new CButton(BUTTON, 30, 14, 20, 3, "菜单管理");
    this->addControl(btn2);
    
    // 4. 人员管理按钮
    CButton* btn3 = new CButton(BUTTON, 30, 18, 20, 3, "人员管理");
    this->addControl(btn3);
    
    // 5. 注销按钮
    CButton* btn4 = new CButton(BUTTON, 25, 23, 12, 3, "注销");
    this->addControl(btn4);
    
    // 6. 退出按钮
    CButton* btn5 = new CButton(BUTTON, 43, 23, 12, 3, "退出");
    this->addControl(btn5);
}

// 析构函数
// 释放所有控件的内存
CAdminWin::~CAdminWin()
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
// flag == 1: 台面管理按钮 - 功能未实现
// flag == 2: 菜单管理按钮 - 跳转到菜单管理窗口
// flag == 3: 人员管理按钮 - 跳转到人员管理窗口
// flag == 4: 注销按钮 - 返回登录窗口
// flag == 5: 退出按钮 - 返回初始窗口
// flag == -1: ESC键 - 返回初始窗口
void CAdminWin::handle()
{
	
	if(this->flag == 2)  // 菜品管理按钮
    {
        this->result = 2;
    }
    else if(this->flag == 3)  // 人员管理按钮
    {
        this->result = 3;
    }
    else if(this->flag == 1)  // 台桌管理按钮
    {
        this->result = 1;
    }
    else if(this->flag == 5 || this->flag == -1)  // 退出按钮或ESC
    {
        this->result = 0;    // 返回初始窗口
    }
    else if(this->flag == 4)  // 注销按钮
	{
    	this->result = 4;    // 返回登录窗口
	}
    
//    if(this->flag == 1) {  // 台桌管理按钮
//      
//        CAdminWin_Table* tbWin = new CAdminWin_Table();
//        tbWin->show();
//        tbWin->run();
//        tbWin->handle();
//        delete tbWin;
//    }
//    else if(this->flag == 2) {  // 菜单管理按钮
//         // 跳转到菜单管理窗口
//         CAdminWin_DM* dmWin = new CAdminWin_DM();
//         dmWin->show();
//         dmWin->run();
//         dmWin->handle();
//         delete dmWin;        
//    }
//    else if(this->flag == 3) {  // 人员管理按钮
//        // 跳转到人员管理窗口
//         CAdminWin_PM* pmWin = new CAdminWin_PM();
//         pmWin->show();
//         pmWin->run();
//         pmWin->handle();
//         delete pmWin;
//    }
//    else if(this->flag == 4) {  // 注销按钮
//    
//    
//    	 system("cls");
//         CLoginWin* loginWin = new CLoginWin();
//         loginWin->show();
//         loginWin->run();
//         loginWin->handle();
//         delete loginWin;
//    }
//    else if(this->flag == 5 || this->flag == -1) {  // 退出按钮或ESC键
//        
//         system("cls");
//         CInitWin* initWin = new CInitWin();
//         initWin->show();
//         initWin->run();
//         initWin->handle();
//         delete initWin;
//    }
}
