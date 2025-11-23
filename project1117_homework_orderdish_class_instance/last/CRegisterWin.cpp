#include "CRegisterWin.h"

void CRegisterWin_init() {
    // 窗口
    CWIN win = {10, 2, 60, 28, 0, 0};
    
    // 标题
    CONTROL title = {LABEL, 32, 5, 0, 0, "=== 用户注册 ==="};
    
    // 账号
    CONTROL lab1 = {LABEL, 15, 8, 0, 0, "账号: "};
    CONTROL edit1 = {EDIT, 25, 8, 25, 3, "", 20, 1, 3};
    
    // 密码
    CONTROL lab2 = {LABEL, 15, 12, 0, 0, "密码: "};
    CONTROL edit2 = {EDIT, 25, 12, 25, 3, "", 20, 0, 3};
    
    // 重复密码
    CONTROL lab3 = {LABEL, 15, 16, 0, 0, "重复密码: "};
    CONTROL edit3 = {EDIT, 25, 16, 25, 3, "", 20, 0, 3};
    
    // 角色 (1=管理员 2=经理 3=服务员)
    CONTROL lab4 = {LABEL, 15, 20, 0, 0, "角色(1-3): "};
    CONTROL edit4 = {EDIT, 25, 20, 10, 3, "", 1, 1, 1};  // 只能输入1个数字
    
    // 按钮
    CONTROL btn1 = {BUTTON, 20, 25, 12, 3, "注册"};
    CONTROL btn2 = {BUTTON, 38, 25, 12, 3, "取消"};
    
   // 把所有控件添加到窗口
   addControl(&win, &title); // 添加标题
   addControl(&win, &lab1); 
   addControl(&win, &edit1); // 添加账号
   addControl(&win, &lab2); 
   addControl(&win, &edit2); // 添加密码
   addControl(&win, &lab3); 
   addControl(&win, &edit3); // 添加重复密码
   addControl(&win, &lab4); 
   addControl(&win, &edit4); // 添加角色
   addControl(&win, &btn1);	 // 添加注册按钮 
   addControl(&win, &btn2); // 添加取消按钮 
   //绘制整个窗口
   printWindow(&win);
   
   //光标驱动 
   winRun(&win);
   
    if(win.flag == 9) //注册按钮被enter点击 应该有个保存账号还有判断用户名是否重复缝逻辑，先不做了 
	{
		// 调用注册验证函数
    int result = registerUser(
        win.arr[2].context,  // 账号（edit1）
        win.arr[4].context,  // 密码（edit2）
        win.arr[6].context,  // 重复密码（edit3）
        win.arr[8].context   // 角色（edit4）
    );
    
    if(result == 0) 
	{  // 注册成功
        system("cls");
        printf("\n\n 注册成功！\n\n");
        Sleep(2000);
        system("cls");
        CLoginWin_init();
    }
    else if(result == -1) 
	{  // 密码不一致
        system("cls");
        printf("\n\n 两次密码不一致！\n\n");
        Sleep(2000);
        system("cls");
        CRegisterWin_init();  // 重新回到注册页面 
    }
    else if(result == -2) 
	{  // 账号已存在
        system("cls");
        printf("\n\n 账号已存在！\n\n");
        Sleep(2000);
        system("cls");
        CRegisterWin_init(); // 重新回到注册页面
    }
	}
	else if(win.flag == 10)//取消按钮被enter点击
	{
		system("cls"); //清屏 
		printf("请稍后......"); 
		Sleep(2000); //等待两秒 
		system("cls");
		CStartWin_init(); //回到开始页面	
	}  
} 

/*
	注册账号逻辑 
*/ 
int registerUser(char account[], char password[], char repassword[], char role[]) 
{
    if(strcmp(password, repassword) != 0)  // 密码不一致 
	{
        return -1;
    }
    
    LIST *p = userList -> pnext; // 第一个有效数据 
    while(p != NULL) // 遍历userList表中是否有相同的名字
	{
        if(strcmp(account, ((USER*)p -> data) -> account) == 0) // userList表中有 
		{
            return -2;
        }
        p = p -> pnext;
    }
    
    // 将新建账号存入userList表 
    USER newUser;
    strcpy(newUser.account, account);
    strcpy(newUser.password, password);
    newUser.role = atoi(role);
    
    // 插入userList表 
    New_List_pushback(userList, &newUser, sizeof(USER));
    
    return 0;
}
