#include <stdio.h>
#include <stdlib.h>
#include "CTool.h" 
#include "CLabel.h"
#include "CButton.h"
#include "CEdit.h"
#include "CControl.h"

#include "CLoginWin.h" 
#include "CInitWin.h"
#include "CRegisterWin.h" 
#include "CAdminWin.h"
#include "CManagerWin.h" 
#include "CWaiterWin.h"

// 引入用户管理器单例类
#include "CUserManager.h"
// 菜品管理器单例类
#include "CDishManager.h" 
// 台桌管理器单例类
#include "CTableManager.h"
/*	CLoginnWin 窗口*/
void demo1()
{
    CLoginWin* loginWin = new CLoginWin();
    loginWin->show();
    loginWin->run();
    loginWin->handle();
    delete loginWin;
}
/*	CInitWin 窗口*/
void demo2()
{
    CInitWin* initWin = new CInitWin();
    initWin->show();
    initWin->run();
    initWin->handle();
    delete initWin;
}
/*	CRegisterWin 窗口*/
void demo3()
{
    CRegisterWin* registerWin = new CRegisterWin();
    registerWin->show();
    registerWin->run();
    registerWin->handle();
    delete registerWin;
}
/*	CAdminWin 窗口*/
void demo4()
{
    CAdminWin* adminWin = new CAdminWin();
    adminWin->show();
    adminWin->run();
    adminWin->handle();
    delete adminWin;
}
/*	CManagerWin 窗口*/
void demo5()
{
    CManagerWin* managerWin = new CManagerWin();
    managerWin->show();
    managerWin->run();
    managerWin->handle();
    delete managerWin;
}
/*	CWaiterWin 窗口*/
void demo6()
{
    CWaiterWin* waiterWin = new CWaiterWin();
    waiterWin->show();
    waiterWin->run();
    waiterWin->handle();
    delete waiterWin;
}


//void demo7()
//{
//    CLabel* label = new CLabel(10, 10, "Hello World");
//    label->showControl();
//    delete label;
//}
//
//void demo8()
//{
//    CButton* button = new CButton(10, 10, "Click Me", 1);
//    button->showControl();
//    delete button;
//}
//
//void demo9()
//{
//    CEdit* edit = new CEdit(10, 10, "Enter text", 1);
//    edit->showControl();
//    delete edit;
//}
//
//void demo10()
//{
//    CControl* arr[3];
//    arr[0] = new CLabel(10, 10, "Label");
//    arr[1] = new CButton(10, 12, "Button", 1);
//    arr[2] = new CEdit(10, 14, "Edit", 1);
//    
//    for(int i = 0; i < 3; i++)
//    {
//        arr[i]->showControl();
//    }
//    
//    for(int i = 0; i < 3; i++)
//    {
//        delete arr[i];
//    }
//}


void demo11()
{
    CWindow* win = new CLoginWin();
    win->show();
    win->run();
    win->handle();
    delete win;
}

void demo12()
{
    CWindow* win = new CInitWin();
    win->show();
    win->run();
    win->handle();
    delete win;
}

void demo13()
{
    CWindow* win = new CRegisterWin();
    win->show();
    win->run();
    win->handle();
    delete win;
}

void demo14()
{
    CWindow* win = new CAdminWin();
    win->show();
    win->run();
    win->handle();
    delete win;
}

void demo15()
{
    CWindow* win = new CManagerWin();
    win->show();
    win->run();
    win->handle();
    delete win;
}

void demo16()
{
    CWindow* win = new CWaiterWin();
    win->show();
    win->run();
    win->handle();
    delete win;
}


// 状态枚举 : 有名字的常量  
// 跟宏定义差不多 但是enum 
// 指定第一个成员的值  后面的成员自动+1 
enum RunState {
    STATE_EXIT = 0,
    STATE_INIT,
    STATE_REGISTER,
    STATE_LOGIN,
    STATE_ADMIN,
    STATE_MANAGER,
    STATE_WAITER,
    STATE_ADMIN_TABLE,
    STATE_ADMIN_DM,
    STATE_ADMIN_PM,
    STATE_ORDER
};

int main() {
    // 初始化用户管理器
    // 获取用户管理器实例 (第1次调用,会创建实例并加载测试数据)
    CUserManager* userMgr = CUserManager::getInstance();    
    // 获取菜品管理器实例 
    CDishManager* dishMgr = CDishManager::getInstance();	
	// 获取台桌管理器实例
	CTableManager* tableMgr = CTableManager::getInstance();
	
	printf(" 系统初始化完成...\n");	
    Sleep(1000);
    system("cls");
    
    
    // 状态机变量
    int state = STATE_INIT;
    TABLE* selectedTable = NULL;  // 保存选中的台桌
  	
  	// 状态机主循环
    while(state != STATE_EXIT)
    {
        system("cls");
        
        switch(state)
        {
            case STATE_INIT:  // 初始窗口
            {
                CInitWin* win = new CInitWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                delete win;
                
                if(res == 1) state = STATE_REGISTER;
                else if(res == 2) state = STATE_LOGIN;
                else state = STATE_EXIT;
                break;
            }
            
            case STATE_REGISTER:  // 注册窗口
            {
                CRegisterWin* win = new CRegisterWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                int role = win->getUserRole();
                delete win;
                
                if(res == 1)  // 注册成功，自动登录
                {
                    if(role == 1) state = STATE_ADMIN;
                    else if(role == 2) state = STATE_MANAGER;
                    else state = STATE_WAITER;
                }
                else  // 取消
                {
                    state = STATE_INIT;
                }
                break;
            }
            
            case STATE_LOGIN:  // 登录窗口
            {
                CLoginWin* win = new CLoginWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                int role = win->getUserRole();
                delete win;
                
                if(res == 1)  // 登录成功
                {
                    if(role == 1) state = STATE_ADMIN;
                    else if(role == 2) state = STATE_MANAGER;
                    else state = STATE_WAITER;
                }
                else  // 取消
                {
                    state = STATE_INIT;
                }
                break;
            }
            
            case STATE_ADMIN:  // 管理员窗口
            {
                CAdminWin* win = new CAdminWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                delete win;
                
                if(res == 1) state = STATE_ADMIN_TABLE;
                else if(res == 2) state = STATE_ADMIN_DM;
                else if(res == 3) state = STATE_ADMIN_PM;
                else if(res == 4) state = STATE_LOGIN;  // 注销
                else state = STATE_INIT;  // 退出
                break;
            }
            
            case STATE_MANAGER:  // 经理窗口
            {
                CManagerWin* win = new CManagerWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                delete win;
                
                if(res == 2) state = STATE_LOGIN;  // 注销
                else state = STATE_INIT;  // 退出
                break;
            }
            
            case STATE_WAITER:  // 服务员窗口
            {
                CWaiterWin* win = new CWaiterWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                delete win;
                
                if(res == 1 || res == 2) state = STATE_ADMIN_TABLE;  // 点菜/加菜
                else if(res == 5) state = STATE_LOGIN;  // 注销
                else state = STATE_INIT;  // 退出
                break;
            }
            
            case STATE_ADMIN_TABLE:  // 台桌管理
            {
                CAdminWin_Table* win = new CAdminWin_Table();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                selectedTable = win->getSelectedTable();
                delete win;
                
                if(res == 1 && selectedTable != NULL)
                {
                    state = STATE_ORDER;  // 跳转点菜
                }
                else
                {
                    state = STATE_ADMIN;  // 返回管理员窗口
                }
                break;
            }
            
            case STATE_ADMIN_DM:  // 菜品管理
            {
                CAdminWin_DM* win = new CAdminWin_DM();
                win->show();
                win->run();
                win->handle();
                
                delete win;
                state = STATE_ADMIN;  // 返回管理员窗口
                break;
            }
            
            case STATE_ADMIN_PM:  // 人员管理
            {
                CAdminWin_PM* win = new CAdminWin_PM();
                win->show();
                win->run();
                win->handle();
                
                delete win;
                state = STATE_ADMIN;  // 返回管理员窗口
                break;
            }
            
            case STATE_ORDER:  // 点菜窗口
            {
                COrderWin* win = new COrderWin(selectedTable);
                win->show();
                win->run();
                win->handle();
                
                delete win;
                selectedTable = NULL;  // 清空
                state = STATE_ADMIN_TABLE;  // 返回台桌选择
                break;
            }
        }
    }
    
    // 销毁单例管理器
    system("cls");
    CUserManager::destroyInstance();
    CDishManager::destroyInstance();
    CTableManager::destroyInstance();
    
    printf("\n 再见！\n");
    
    return 0;
}
