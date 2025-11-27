#include "CWaiterWin.h"


// CWaiterWin 类
// 服务员窗口类,继承自 CWindow
// 功能:显示服务员菜单,包含点菜、加菜、营业额查询、已结/未结单查询、注销、退出按钮

// 无参构造函数
// 创建服务员窗口,添加标题和6个按钮
CWaiterWin::CWaiterWin() 
    : CWindow(10, 3, 70, 25)  // 窗口位置和大小
{
    // 1. 标题
    CLabel* title = new CLabel(Label, 32, 5, 0, 0, " 服务员界面 ");
    this->addControl(title);
    
    // 2. 点菜按钮
    CButton* btn1 = new CButton(BUTTON, 28, 8, 24, 3, "点菜");
    this->addControl(btn1);
    
    // 3. 加菜按钮
    CButton* btn2 = new CButton(BUTTON, 28, 12, 24, 3, "加菜");
    this->addControl(btn2);
    
    // 4. 营业额查询按钮
    CButton* btn3 = new CButton(BUTTON, 28, 16, 24, 3, "营业额查询");
    this->addControl(btn3);
    
    // 5. 已结/未结单查询按钮
    CButton* btn4 = new CButton(BUTTON, 28, 20, 24, 3, "已结/未结单查询");
    this->addControl(btn4);
    
    // 6. 注销按钮
    CButton* btn5 = new CButton(BUTTON, 25, 24, 12, 3, "注销");
    this->addControl(btn5);
    
    // 7. 退出按钮
    CButton* btn6 = new CButton(BUTTON, 43, 24, 12, 3, "退出");
    this->addControl(btn6);
}

/// 析构函数
/// 释放所有控件的内存
CWaiterWin::~CWaiterWin()
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
// flag == 1: 点菜按钮 - 功能未实现
// flag == 2: 加菜按钮 - 功能未实现
// flag == 3: 营业额查询按钮 - 功能未实现
// flag == 4: 已结/未结单查询按钮 - 功能未实现
// flag == 5: 注销按钮 - 返回登录窗口
// flag == 6: 退出按钮 - 返回初始窗口
// flag == -1: ESC键 - 返回初始窗口
void CWaiterWin::handle()
{
	
	
	if(this->flag == 1)  // 点菜按钮
    {
        this->result = 1;    // 进入台桌选择（点菜）
    }
    else if(this->flag == 2)  // 加菜按钮
    {
        this->result = 2;    // 进入台桌选择（加菜）
    }
    else if(this->flag == 3 || this->flag == 4)  // 营业额查询、已结/未结单（暂未实现）
    {
        // 暂时不跳转
        this->show();
        this->run();
        this->handle();
        return;
    }
    else if(this->flag == 5)  // 注销按钮
    {
        this->result = 5;    // 返回登录窗口
    }
    else if(this->flag == 6 || this->flag == -1)  // 退出按钮或ESC
    {
        this->result = 0;    // 返回初始窗口
    }
	
	
	
//    if(this->flag >= 1 && this->flag <= 4) {  // 前4个按钮:点菜、加菜、营业额查询、已结/未结单查询
//
//		// 先跳转到台桌？ 
//		CAdminWin_Table* tbWin = new CAdminWin_Table();
//        tbWin->show();
//        tbWin->run();
//        tbWin->handle();
//        delete tbWin;
//		 
////        system("cls");
////		// 点菜窗口 
////        COrderWin* orderWin = new COrderWin();
////        orderWin->show();
////        orderWin->run();
////        orderWin->handle();
////        delete orderWin;
//    }
//    else if(this->flag == 5) {  // 注销按钮
//        system("cls");
//		// 返回登录窗口
//         CLoginWin* loginWin = new CLoginWin();
//         loginWin->show();
//         loginWin->run();
//         loginWin->handle();
//         delete loginWin;
//    }
//    else if(this->flag == 6 || this->flag == -1) {  // 退出按钮或ESC键
//        
//         system("cls");
//		 // 返回初始窗口
//         CInitWin* initWin = new CInitWin();
//         initWin->show();
//         initWin->run();
//         initWin->handle();
//         delete initWin;
//    }
}
