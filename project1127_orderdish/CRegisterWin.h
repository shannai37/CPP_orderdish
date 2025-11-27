#ifndef CREGISTER_H
#define CREGISTER_H

#include "CWindow.h"
#include "CButton.h"
#include "CEdit.h"
#include "CLabel.h"

#include "CUserManager.h"  // 引入用户管理器
#include "CInitWin.h"      // 引入初始窗口
#include <stdlib.h>
#include <windows.h>
/// CRegisterWin 类
/// 注册窗口,继承自 CWindow
/// 功能:
///   显示注册界面(账号、密码、重复密码、角色)
///   处理用户注册逻辑
///   验证输入数据
///   调用用户管理器注册新用户
class CRegisterWin : public CWindow {
public:
    /// 无参构造函数
    /// 功能: 初始化注册窗口,创建所有控件
    CRegisterWin();
    
    /// 析构函数
    ~CRegisterWin();
    
    /// 显示窗口
    /// 功能: 清屏,显示边框,显示所有控件,显示角色说明
    /// 重写父类的 show() 方法
    void show();
    
    /// 处理业务逻辑
    /// 功能: 验证输入,调用用户管理器注册用户,显示结果
    /// 实现父类的纯虚函数 handle()
    virtual void handle();
    
    //  获取用户角色 
    int getUserRole(); 
    
private:
    int userRole;         // 用户角色  
}; 

#endif
