#ifndef CLOGINWIN_H
#define CLOGINWIN_H

#include "CWindow.h"
#include "CButton.h"
#include "CEdit.h"
#include "CLabel.h"


#include "CButton.h"
#include "CEdit.h"
#include "CLabel.h"
#include "CUserManager.h"  // 引入用户管理器

#include "CInitWin.h"
#include "CAdminWin.h"
#include "CManagerWin.h"
#include "CWaiterWin.h"

#include <windows.h>
/// CLoginWin 类
/// 登录窗口,继承自 CWindow
/// 功能:
///   - 显示登录界面(用户名、密码)
///   - 处理用户登录逻辑
///   - 验证用户名和密码
///   - 根据角色跳转到对应窗口(管理员/经理/服务员)
class CLoginWin : public CWindow {
public:
    /// 无参构造函数
    /// 功能: 初始化登录窗口,创建所有控件
    CLoginWin();
    
    /// 析构函数
    /// 功能: 释放所有控件的内存
    ~CLoginWin();
    
    /// 处理业务逻辑
    /// 功能: 验证用户名和密码,根据角色跳转到对应窗口
    /// 实现父类的纯虚函数 handle()
    virtual void handle();
    
    
    int getUserRole();    // 获取登录角色
private:
	int userRole;    // 登录成功后的用户角色  
	 
};

#endif
