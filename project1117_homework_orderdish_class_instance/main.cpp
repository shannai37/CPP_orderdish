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

int main() {
    // 初始化用户管理器
    // 获取用户管理器实例 (第1次调用,会创建实例并加载测试数据)
    CUserManager* userMgr = CUserManager::getInstance();
    printf(" 用户管理器已初始化 \n\n");
    
    // 运行初始窗口
    demo2();  
    
    
    system("cls");
    // 销毁用户管理器 (会释放内存)
    CUserManager::destroyInstance();
    printf("\n 用户管理器已销毁 \n");
    
    return 0;
}
