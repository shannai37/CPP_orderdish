#include "CStartWin.h"


/*
函数名称：CStartWin_init
函数功能：
	显示程序的主菜单界面（起始界面）
	包含注册、登录、退出 三个功能按钮
	
	跟前一版本不同，我们现在使用 按钮配置结构体（ButtonConfig）数组  来管理所有按钮
	好处：添加新按钮只需要在配置中加一行
*/
void CStartWin_init() 
{
    // 1、创建窗口结构
    CWIN win = {15, 3, 50, 25, 0, 0};
    
    // 2、定义按钮配置数组 		文字   ， x  ， y ，  宽 ， 高 ，  跳转函数
    ButtonConfig buttons[] = 
	{
        {"注册", 32, 11, 16, 3, CRegisterWin_init},
        {"登录", 32, 16, 16, 3, CLoginWin_init},
        {"退出", 32, 21, 16, 3, NULL} 	  // jump=NULL 表示退出程序
    };
    int buttonCount = 3; //	维护按钮数量，后面我们会根据flag去跳转对应的buttons 
    
    // 3、添加标题
    CONTROL title = {LABEL, 25, 7, 0, 0, "=== 欢迎使用点餐系统 ==="};
    addControl(&win, &title);
    
    // 4、循环创建按钮
    // 从按钮配置结构体读取信息，去生成真正的CONTROL控件
    
	int i;
    
    for(i = 0; i < buttonCount; i++) 
	{
        // 创建CONTROL结构体
        // 注意！context用空字符串，因为buttons[i].text是变量，初始化不能使用变量
		// CONTROL btn1 = {BUTTON, 32, 11, 16, 3, "注册"}; //这里的“注册”是字符串常量，所以不会报错	 
        CONTROL btn = {BUTTON, 
                       buttons[i].x, 
                       buttons[i].y, 
                       buttons[i].width, 
                       buttons[i].height, 
                       ""};
        
        // 复制文字到控件
        // 不能直接初始化，必须用strcpy
        strcpy(btn.context, buttons[i].text);
        
        // 添加到窗口
        // 注意：buttons[i].jump（函数指针）没有存入CONTROL
        // 它还保留在 按钮配置结构体 中，后面通过flag索引回来
        addControl(&win, &btn);
    }
    
    // 5、绘制界面，运行窗口
    printWindow(&win);  // 显示界面
    winRun(&win);       // 等待用户操作，设置flag
    
    // 6、根据flag跳转到对应函数
    // 点登录按钮 → flag = 2 → btnIndex = 1 → buttons[1].jump
    if(win.flag >= 1 && win.flag <= buttonCount) 
	{
		// 将窗口结构体CWIN中的业务下标flag 转换成 按钮配置数组buttons 对应的索引 
        int btnIndex = win.flag - 1; 
        jumpToWindow(buttons[btnIndex].jump);
    }
}

