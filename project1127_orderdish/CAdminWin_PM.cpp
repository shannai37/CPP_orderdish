#include "CAdminWin_PM.h"

// 构造函数
CAdminWin_PM::CAdminWin_PM()
: CWindow(10, 2, 70, 26)	// 初始化列表 
{
	currentPage = 1;
    pageSize = 3;
    
    // 添加控件
    CButton* btn1 = new CButton(BUTTON, 18, 23, 14, 3, "上一页");
    this->addControl(btn1);  // arr[0]
    
    CLabel* labelPage = new CLabel(Label, 35, 24, 0, 0, "1 / 1");
    this->addControl(labelPage);  // arr[1]
    
    CButton* btn2 = new CButton(BUTTON, 50, 23, 14, 3, "下一页");
    this->addControl(btn2);  // arr[2]
}	

// 析构函数 
CAdminWin_PM::~CAdminWin_PM()
{
	for(int i = 0 ; i < this->count ; i++)
	{
		if(this->arr[i] != NULL)
		{
			delete this->arr[i];
			this->arr[i] = NULL;
		}
	}	
} 

// 重写show	
// 将边框和控件 + 人员管理核心（表格+数据）打印出来 
void CAdminWin_PM::show()
{
	// 调用父类show   绘制边框和控件
	CWindow::show();
	
	// 表格+数据
	drawTable(); 
} 

// 绘制表格和数据
void CAdminWin_PM::drawTable()
{
	// 1.获取菜品管理器
	CUserManager* userMgr = CUserManager::getInstance();
	int totalCount = userMgr->getUserCount(); // 获取菜品总数
	
	// 2.计算总页数
	if(totalCount == 0) 
	{
        allPage = 1;
    } 
	else 
	{
        allPage = (totalCount + pageSize - 1) / pageSize;
    } 
	
	// 3.更新页码标签（更新的 “1 / 3 页 ”这部分内容） 
	char pageText[20];
	sprintf(pageText,"%d / %d",currentPage,allPage);
	
	arr[1]->setContext(pageText);	// 更新标签内容
	arr[1]->showControl();          // 重新显示 
	
	// 4. 绘制表格边框
    CTool::printTable(13, 5, 64, 16, 4, 4);
    
    // 5. 显示表头
    CTool::gotoxy(17, 7);   printf("序号");
    CTool::gotoxy(33, 7);   printf("账号");
    CTool::gotoxy(49, 7);   printf("密码");
    CTool::gotoxy(65, 7);   printf("角色");
    
    // 6. 显示数据 
    int startIndex = (currentPage - 1) * pageSize;
    for(int i = 0; i < pageSize; i++) 
	{
        int dataIndex = startIndex + i;
        if(dataIndex >= totalCount) break;
        
        USER* user = userMgr->getUserByIndex(dataIndex);  
        if(user == NULL) continue;	// 找不到这个用户的话，直接跳过后续显示用户数据 
        
        int dataY = 7 + 4 + (i * 4);
        
        // 显示用户数据
        CTool::gotoxy(17, dataY);  printf("%d", startIndex + i + 1); 
        CTool::gotoxy(33, dataY);  printf("%s", user->account);
        CTool::gotoxy(49, dataY);  printf("%s", user->password);
        CTool::gotoxy(65, dataY);
        if(user->role == 1) printf("管理员");
        else if(user->role == 2) printf("经理");
        else if(user->role == 3) printf("服务员");
	}
} 	


void CAdminWin_PM::handle() 
{
	bool runWin = true;
	while(runWin)
	{
		if(this->flag == 0) 
		{
            if(currentPage > 1) 
			{
                currentPage--;
                system("cls");
                this->show();	// 重新显示 
                this->run();	// 重新运行 
            }
            else 
			{
	            CTool::gotoxy(30, 28);
	            printf("已经是第1页");
	            Sleep(1000);
	            system("cls");
	            this->show();	// 重新显示 
                this->run();	// 重新运行 
	        }
		}
		else if(this->flag == 2) // 下一页 
		{
			if(currentPage < allPage) 
			{
	            currentPage++;
	            system("cls");
	            this->show();	// 重新显示 
                this->run();	// 重新运行 
	        } 
			else 
			{
	            CTool::gotoxy(30, 28);
	            printf("已经是最后一页");
	            Sleep(1000);
	            system("cls");
	            this->show();	// 重新显示 
                this->run();	// 重新运行 
	        }
		}
		else if(flag == -1) 
		{
			
			runWin = false;
   			this->result = 0;    // 返回管理员窗口
			
			
//            runWin = false;  // 退出循环
//            system("cls");                     // 清屏 
//        	printf("\n\n 正在跳转...\n\n");    
//        	Sleep(1000);                        // 等待1秒，让用户看到提示 
//        	system("cls");                     // 再次清屏，准备显示新界面
//        	
//			// 跳转回管理员初始页面 
//			CAdminWin* adminWin = new CAdminWin();
//			adminWin->show();
//			adminWin->run();
//			adminWin->handle();
//			delete adminWin; 
        }
	} 
}
