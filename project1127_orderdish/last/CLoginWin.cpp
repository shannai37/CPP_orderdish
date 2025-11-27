#include "CLoginWin.h"

void CLoginWin_init()
{
	// 创建空窗口 
	CWIN win = {20,5,60,20,0,0};
	
	
	// 定义需要的组件 
	CONTROL lab1 = {LABEL,35,12,0,0,"用户名: "}; 
	CONTROL lab2 = {LABEL,35,17,0,0,"密码: "};
	
	CONTROL btn1 = {BUTTON,28,21,12,3,"确 定"}; 
	CONTROL btn2 = {BUTTON,48,21,12,3,"取 消"};
	 
	CONTROL edit1 = {EDIT,45,11,25,3,"",10,1,3}; //最后一个参数是过滤输入，限制用户输入类型 1：数字 2：字母 3：数字+字母 
	CONTROL edit2 = {EDIT,45,16,25,3,"",10,0,3}; 


	
	// 将控件添加到窗口
	addControl(&win, &lab1); //装第一个(装进win的控件数组里，从下标0开始) 
	addControl(&win, &lab2); //装第二个(数组下标1)
	addControl(&win, &edit1); 
	addControl(&win, &edit2); 
	addControl(&win, &btn1);
	addControl(&win, &btn2);
	
	// 一次性绘制整个窗口
	printWindow(&win);
	
	//光标驱动 
	winRun(&win);
	
	if(win.flag == 4) //确定按钮被enter点击
	{
		// 调用登录验证
		int role; 
    	role = loginCheck(win.arr[2].context, win.arr[3].context);
    	if(role == 1)  // 管理员
		{  
	        system("cls");  // 清屏
	        CAdminWin_init();  // 跳转到管理员界面
    	}
	    else if(role == 2)  // 经理
		{ 
	        system("cls");
	        CManagerWin_init();  // 跳转到经理界面
	    }
	    else if(role == 3) // 服务员
		{  
	        system("cls");
	        CWaiterWin_init();  // 跳转到服务员界面
	    }
	    else if(role == -1)  // 登录失败逻辑 
		{ 
	        system("cls");
	        printf("\n\n 账号或密码错误！\n\n");
	        Sleep(2000);  // 等待2秒
	        system("cls");
	        CLoginWin_init();  // 重新显示登录界面
	    }
	}
	else if(win.flag == 5)//退出按钮被enter点击 
	{
		system("cls");
		printf("\n\n 已取消登录！\n\n");
		Sleep(2000);
    	system("cls");
    	CStartWin_init();  // 返回主菜单	
	} 
		
	
}


int loginCheck(char username[], char password[])  
{
    LIST *p = userList->pnext;  
    
    while(p != NULL)  
    {
        if(strcmp(username, ((USER*)p->data)->account) == 0)
        {
            if(strcmp(password, ((USER*)p->data)->password) == 0)
            {
                return ((USER*)p->data)->role;
            }
        }
        p = p->pnext; 
    }
    
    return -1;
}
