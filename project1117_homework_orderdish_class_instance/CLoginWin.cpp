#include "CLoginWin.h"


/// 无参构造函数
/// 功能: 初始化登录窗口,创建所有控件
/// 控件列表:
///   arr[0] - 用户名标签 "用户名:"
///   arr[1] - 用户名编辑框 
///   arr[2] - 密码标签 "密码:"
///   arr[3] - 密码编辑框 
///   arr[4] - 确定按钮
///   arr[5] - 取消按钮
CLoginWin::CLoginWin()
    : CWindow(15,5,50,15)  // 调用父类有参构造函数,设置窗口位置和大小
{
    // 1. 用户名标签和编辑框
    CLabel* lab1 = new CLabel(Label, 20, 8, 0, 0, "用户名:");
    this->addControl(lab1);
    
    CEdit* edit1 = new CEdit(EDIT, 32, 8, 25, 3, "", 20, 2, 1);  // 2 字母+数字,1 明文
    this->addControl(edit1);
    
    // 2. 密码标签和编辑框
    CLabel* lab2 = new CLabel(Label, 20, 12, 0, 0, "密  码:");
    this->addControl(lab2);
    
    CEdit* edit2 = new CEdit(EDIT, 32, 12, 25, 3, "", 20, 2, 0);  // 2 字母+数字,0 密文
    this->addControl(edit2);
    
    // 3. 确定和取消按钮
    CButton* btn1 = new CButton(BUTTON, 25, 16, 12, 3, "确定");
    this->addControl(btn1);
    
    CButton* btn2 = new CButton(BUTTON, 43, 16, 12, 3, "取消");
    this->addControl(btn2);
}

/// 析构函数
/// 功能: 释放所有控件的内存
CLoginWin::~CLoginWin()
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

/// 处理业务逻辑
/// 功能:
///   根据flag的值执行不同的操作
///   flag == 4: 确定按钮 - 验证用户名和密码,根据角色跳转
///   flag == 5: 取消按钮 - 返回初始窗口
///   flag == -1: ESC键 - 返回初始窗口
/// 验证步骤:
///   1. 获取用户输入的用户名和密码
///   2. 调用用户管理器验证
///   3. 验证失败 - 显示错误提示,重新显示登录窗口
///   4. 验证成功 - 根据角色跳转到对应窗口
void CLoginWin::handle()
{
    if(this->flag == 4)  // 确定按钮
    {
        //  1. 获取用户输入的数据 
        char* username = this->arr[1]->getContext();  // 用户名 (arr[1])
        char* password = this->arr[3]->getContext();  // 密码 (arr[3])
        
        // 2. 获取用户管理器实例 
        CUserManager* userMgr = CUserManager::getInstance();
        
        //  3. 验证用户名和密码 
        // 返回值: -1=验证失败, 1=管理员, 2=经理, 3=服务员
        int role = userMgr->verifyUser(username, password);
        
        //  4. 根据验证结果处理 
        
        if(role == -1)  // 验证失败
        {
            system("cls");
            printf("\n\n 用户名或密码错误!\n\n");
            Sleep(1500);
            system("cls");
            
            // 重新显示登录窗口
            this->show();
            this->run();
            this->handle();
            return;
        }
        
        // 验证成功,根据角色跳转到对应窗口
        
        if(role == 1)  // 管理员
        {
            system("cls");
            CAdminWin* adminWin = new CAdminWin();
            adminWin->show();
            adminWin->run();
            adminWin->handle();
            delete adminWin;
        }
        else if(role == 2)  // 经理
        {
            system("cls");
            CManagerWin* managerWin = new CManagerWin();
            managerWin->show();
            managerWin->run();
            managerWin->handle();
            delete managerWin;
        }
        else if(role == 3)  // 服务员
        {
            system("cls");
            CWaiterWin* waiterWin = new CWaiterWin();
            waiterWin->show();
            waiterWin->run();
            waiterWin->handle();
            delete waiterWin;
        }
    }
    else if(this->flag == 5 || this->flag == -1)  // 取消按钮或ESC键
    {
        system("cls");
        
        // 返回初始窗口
        CInitWin* initWin = new CInitWin();
        initWin->show();
        initWin->run();
        initWin->handle();
        delete initWin;
    }
}
