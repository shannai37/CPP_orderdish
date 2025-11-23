#include "CRegisterWin.h"


/// 无参构造函数
/// 功能: 初始化注册窗口,创建所有控件
/// 控件列表:
///   arr[0] - 标题标签 "注册窗口"
///   arr[1] - 账号标签 "账号:"
///   arr[2] - 账号编辑框 
///   arr[3] - 密码标签 "密码:"
///   arr[4] - 密码编辑框 
///   arr[5] - 重复密码标签 "重复密码:"
///   arr[6] - 重复密码编辑框 
///   arr[7] - 角色标签 "角色:"
///   arr[8] - 角色编辑框 
///   arr[9] - 注册按钮
CRegisterWin::CRegisterWin()
    : CWindow(10, 3, 60, 25)  // 调用父类有参构造函数,设置窗口位置和大小
{
    // 1. 标题
    CLabel* title = new CLabel(Label, 32, 6, 0, 0, "注册窗口");
    this->addControl(title);
    
    // 2. 账号标签和编辑框
    CLabel* lab1 = new CLabel(Label, 18, 9, 0, 0, "账    号:");
    this->addControl(lab1);
    
    CEdit* edit1 = new CEdit(EDIT, 32, 9, 25, 3, "", 20, 2, 1);  // 2 字母+数字,1 明文
    this->addControl(edit1);
    
    // 3. 密码标签和编辑框
    CLabel* lab2 = new CLabel(Label, 18, 13, 0, 0, "密    码:");
    this->addControl(lab2);
    
    CEdit* edit2 = new CEdit(EDIT, 32, 13, 25, 3, "", 20, 2, 0);  // 2 字母+数字,0 密文 
    this->addControl(edit2);
    
    // 4. 重复密码标签和编辑框
    CLabel* lab3 = new CLabel(Label, 18, 17, 0, 0, "重复密码:");
    this->addControl(lab3);
    
    CEdit* edit3 = new CEdit(EDIT, 32, 17, 25, 3, "", 20, 2, 0);  // 2 字母+数字,0 密文 
    this->addControl(edit3);
    
    // 5. 角色标签和编辑框
    CLabel* lab4 = new CLabel(Label, 18, 21, 0, 0, "角    色:");
    this->addControl(lab4);
    
    CEdit* edit4 = new CEdit(EDIT, 32, 21, 25, 3, "", 1, 0, 1);  // 0 数字,1 明文 
    this->addControl(edit4);
    
    // 6. 注册按钮
    CButton* btn1 = new CButton(BUTTON, 32, 24, 12, 3, "注册");
    this->addControl(btn1);
}

/// 析构函数
/// 功能: 释放所有控件的内存
CRegisterWin::~CRegisterWin()
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

/// 显示窗口
/// 功能:
///   1. 调用父类的 show() 方法 (显示边框和所有控件)
///   2. 显示角色说明
void CRegisterWin::show()
{
    // 1. 调用父类的 show() 方法
    CWindow::show();
    
    // 2. 显示角色说明
    CTool::gotoxy(30, 20);
    printf("角色说明: 1=管理员, 2=经理, 3=服务员");
}

/// 处理业务逻辑
/// 功能:
///   根据flag的值执行不同的操作
///   flag == 9: 注册按钮 - 验证输入并注册用户
///   flag == -1: ESC键 - 返回初始窗口
/// 验证步骤:
///   1. 检查账号和密码是否为空
///   2. 检查两次密码是否一致
///   3. 检查角色是否有效 (1-3)
///   4. 调用用户管理器注册用户
///   5. 根据结果显示提示信息
void CRegisterWin::handle()
{
    if(this->flag == 9)  // 注册按钮
    {
        // ========== 1. 获取用户输入 ==========
        char* account = this->arr[2]->getContext();      // 账号 (arr[2])
        char* password = this->arr[4]->getContext();     // 密码 (arr[4])
        char* repassword = this->arr[6]->getContext();   // 重复密码 (arr[6])
        char* roleStr = this->arr[8]->getContext();      // 角色 (arr[8])
        
        // ========== 2. 验证输入 ==========
        
        // 2.1 检查账号和密码是否为空
        if(strlen(account) == 0 || strlen(password) == 0) 
        {
            system("cls");
            printf("\n\n 账号和密码不能为空!\n\n");
            Sleep(1500);
            system("cls");
            
            // 重新显示注册窗口
            this->show();
            this->run();
            this->handle();
            return;
        }
        
        // 2.2 检查两次密码是否一致
        if(strcmp(password, repassword) != 0) 
        {
            system("cls");
            printf("\n\n 两次密码不一致!\n\n");
            Sleep(1500);
            system("cls");
            
            // 重新显示注册窗口
            this->show();
            this->run();
            this->handle();
            return;
        }
        
        // 2.3 检查角色是否有效 (必须是1、2或3)
        int role = atoi(roleStr);  // 将字符串转换为整数
        if(role < 1 || role > 3) 
        {
            system("cls");
            printf("\n\n 角色必须是 1、2 或 3!\n\n");
            Sleep(1500);
            system("cls");
            
            // 重新显示注册窗口
            this->show();
            this->run();
            this->handle();
            return;
        }
        
        //  3. 调用用户管理器注册用户 
        
        // 获取用户管理器实例 (单例模式)
        CUserManager* userMgr = CUserManager::getInstance();
        
        // 调用registerUser()方法注册用户
        // 返回值: true=注册成功, false=账号已存在
        bool success = userMgr->registerUser(account, password, role);
        
        //  4. 根据结果显示提示信息 
        
        if(success)  // 注册成功
        {
            system("cls");
            printf("\n\n 注册成功!\n\n");
            Sleep(1500);
            system("cls");
            return;  // 返回初始窗口
        }
        else  // 注册失败 (账号已存在)
        {
            system("cls");
            printf("\n\n 账号已存在!\n\n");
            Sleep(1500);
            system("cls");
            
            // 重新显示注册窗口
            this->show();
            this->run();
            this->handle();
        }
    }
    else if(this->flag == -1)  // ESC键 - 取消注册
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
