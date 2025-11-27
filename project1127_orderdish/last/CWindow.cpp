#include "CWindow.h"

/*
函数名称：addcontrol
函数功能：将 控件结构体 封装进 窗口结构体 
参数列表：CWIN *win：窗口结构体指针 
CONTROL *con：控件结构体指针 
函数返回值：无 
*/
void addControl(CWIN *win, CONTROL *con)
{
	win->arr[win->count++] = *con;
}
/*
函数名称：printWindow
函数功能：传入窗口结构体，绘制完整窗口
参数列表：CWIN win：窗口结构体
函数返回值：无 
*/
void printWindow(CWIN *win)
{
	int i;
	//1.画窗口的大边框 
	printBoarder(win->winX,win->winY,win->winWidth,win->winHeight);
	
	//2.遍历所有控件，逐个绘制
	for(i = 0 ; i < win->count ; i++)
	{
		switch(win->arr[i].inputType)
		{
			case LABEL:
				showLabel(win->arr[i]);
				break;
			case BUTTON:
				showButton(win->arr[i]);
				break;
			case EDIT:
				showEdit(win->arr[i]);
				break;
		}
	} 
}

/****************************************
函数名称：winRun
函数功能：窗口中光标的驱动函数
函数参数：CWIN win：窗口结构体
函数返回值：CWIN win，因为值传参函数结束后
对参数变量修改不会被保留，所以需要这个返回值 
光标向左向右现在只做了个基础版，就是只能 移动+光标末尾输入，不能 移动+到任意位置输入 
**************************************/
void winRun(CWIN *win)
{
	int i;
	//窗口第一次显示，光标停留位置要么在编辑框内部，要么在按钮上 
	for(i = 0 ; i < win->count ;i++)
	{
		if(win->arr[i].inputType == EDIT || win->arr[i].inputType == BUTTON)
		{
			break;
		}	
	}	
	gotoxy(win->arr[i].x+2, win->arr[i].y+1);
	
	//光标移动操作
	int ikey; //读取键盘输入
	int pos = 0; //索引，计算光标该去哪里，用于左右光标移动  
	while(1)
	{
		ikey = getKey();
		switch(ikey)
		{
			/*
				对应“按下ESC退出操作”
				不管是在按钮Button控件中、还是编辑Edit控件中按下,我们要结束winrun（光标移动）,退出整个系统
			*/
			case KEY_ESC:
				win -> flag = -1;  // 特殊值，表示用户按了ESC
    			return;     // 直接退出
			/*
			  对应“按下Enter操作 ”,
			  若是在按钮Button控件中按下,我们要结束winrun（光标移动）,进行账号判断并且跳转逻辑
			  若是在编辑Edit控件中按下，我们要跳转到下一个非Label控件 
			*/
			case KEY_ENTER:  
				if(win->arr[i].inputType == BUTTON) // 若是在按钮Button控件中按下
				{
					win->flag = i; //记录当前光标走到哪个组件了
					return ; //退出函数，返回到业务逻辑层(CLoginWin) 
				}
				else if(win->arr[i].inputType == EDIT) // 若是在编辑Edit控件中按下
				{
					i++;
					//光标运动到最后一个时，回到第一个
					if(i >= win->count - 1)
					{
						i = 0;	
					} 	
					//跳过LABEL组件 
					while(win->arr[i].inputType == LABEL)
					{
						if(i < win->count - 1)
						{
							i++;	
						} 
						else
						{
							i = 0;
						}
					} 
					//移动光标到新控件位置
			   	 	gotoxy(win->arr[i].x + 2, win->arr[i].y + 1);
			    	break;	
				}
				break;
				 
			case KEY_UP: //向上键移动
    			i--;
    			//如果小于0，跳到最后一个
    			if(i < 0) 
				{
        			i = win->count - 1;	
    			} 
    
			    //跳过LABEL控件
			    while(win->arr[i].inputType == LABEL) 
				{
			        if(i > 0) 
					{
			            i--;	
			        } 
					else 
					{
			            i = win->count - 1;  //回到最后一个
			        }
			    } 
			    
			    //移动光标到新控件位置
			    gotoxy(win->arr[i].x + 2, win->arr[i].y + 1);
			    break;
			    
			case KEY_DOWN: //光标向下移动
				i++;
				//光标运动到最后一个时，回到第一个
				if(i >= win->count) //当组件数量是5个时，下标是 0 1 2 3 4，所以不能相等 
				{
					i = 0;	
				} 
				//跳过label组件
				while(win->arr[i].inputType == LABEL)
				{
					if(i < win->count - 1) //当前组件不是最后一个时(win->count-1) ，都可以++ 
					{
						i++;	
					}
					else
					{
						i = 0;
					}
				} 
				gotoxy(win->arr[i].x + 2, win->arr[i].y + 1);
				break;
			case KEY_LEFT: //光标向左移动
				if(win->arr[i].inputType == EDIT) //编辑框才行 
				{
					int count;
					// 获取现在已经有多少个字符 
					count = strlen(win->arr[i].context);
					
					if(count > 0) //有字符，才可以移动
					{
						if(pos == 0)
						{
							pos = count;
							gotoxy(win->arr[i].x + 2 + pos,win->arr[i].y + 1);
						} 
						else //不在最左边就左移
						{
							pos--;
							gotoxy(win->arr[i].x + 2 + pos,win->arr[i].y + 1);  
						}
						
					} 
				}
				break;
			case KEY_RIGHT: //光标向右移动
				
				if(win->arr[i].inputType == EDIT) //编辑框才行 
				{
					int count;
					// 获取现在已经有多少个字符 
					count = strlen(win->arr[i].context);
					
					if(count > 0) //有字符，才可以移动
					{
						if(pos == count) //如果此时指针在最右边 
						{
							pos = 0;
							gotoxy(win->arr[i].x + 2 + pos,win->arr[i].y + 1);
						} 
						else //不在最右边就左移 
						{
							pos++;
							gotoxy(win->arr[i].x + 2 + pos,win->arr[i].y + 1);  
						}
							
					} 
				}
				break;
				 
			default:
				if(win->arr[i].inputType == EDIT)
				{
					// 输入前先把光标移到末尾
       				int count;
					count = strlen(win->arr[i].context);
        			pos = count;
        			gotoxy(win->arr[i].x + 2 + pos, win->arr[i].y + 1);
					inputControl(win->arr[i].maxLength,
								 win->arr[i].contentType,
								 win->arr[i].ips,
								 win->arr[i].context,
								 ikey 
					);	
				} 
				break;
		}	
	} 
}

