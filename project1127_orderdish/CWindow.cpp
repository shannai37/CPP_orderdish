#include "CWindow.h"

CWindow::CWindow()
{
	this->count = 0;  // 初始化控件数量为0
    this->flag = 0;   // 初始化标志为0
    this->result = 0;
}


/// 有参构造函数
/// 参数:
///   winX, winY - 窗口左上角坐标
///   winWidth, winHeight - 窗口宽度和高度
/// 功能:
///   初始化窗口属性,控件数组为空
CWindow::CWindow(int winX,int winY,int winWidth,int winHeight)
{
	this->winX = winX;
    this->winY = winY;
    this->winWidth = winWidth;
    this->winHeight = winHeight;
    this->count = 0;
    this->flag = 0;
    this->result = 0;
}

CWindow::~CWindow()
{
	
}


/// 添加控件到窗口
/// 参数:
///   control - 要添加的控件指针(可以是 CLabel、CEdit、CButton)
/// 功能:
///   将控件添加到 arr 数组中,count 加 1
void CWindow::addControl(CControl* con)
{
	  // 检查是否超过最大控件数量
    if(this->count >= 20) {
        printf("错误: 控件数量超过最大限制 20!\n");
        return;
    }
    
    // 将控件添加到数组   控件数量加1 
	this->arr[this->count++] = con;
	 
}


/// 显示窗口
/// 功能:
///   1. 清空屏幕
///   2. 画窗口边框
///   3. 显示所有控件
void CWindow::show()
{
	
	int i;
	// 1.画窗口的大边框 
	CTool::printBoarder(this->winX,this->winY,this->winWidth,this->winHeight);
	
	// 2.遍历所有控件，逐个绘制
	for(i = 0 ; i < this->count ; i++)
	{
		// 调用每个控件的 showControl() 方法
        // 利用多态性,自动调用正确的子类实现
		this->arr[i]->showControl();
	} 

}


/// 运行窗口,处理用户输入
/// 功能:
///   1. 光标停留在编辑框或者按钮上 
///   2. 处理方向键(上下移动光标)
///   3. 处理在回车键(确认选择)
///   4. 处理 ESC 键(取消)
///   5. 处理其他按键(如果是编辑框,则输入字符)
void CWindow::run()
{
	int i;
	// 窗口第一次显示，光标停留位置要么在编辑框内部，要么在按钮上 
	for(i = 0 ; i < this->count ;i++)
	{
		if(this->arr[i]->getType() == EDIT || this->arr[i]->getType() == BUTTON)
		{
			break;
		}	
	}	
	CTool::gotoxy(this->arr[i]->getX() + 2, this->arr[i]->getY() + 1);
	
	// 光标移动操作
	int ikey; // 读取键盘输入
	int pos = 0; // 索引，计算光标该去哪里，用于左右光标移动  
	while(true)
	{
		ikey = CTool::getKey();
		switch(ikey)
		{
			/*
				对应“按下ESC退出操作”
				不管是在按钮Button控件中、还是编辑Edit控件中按下,我们要结束winrun（光标移动）,退出整个系统
			*/
			case KEY_ESC:
				this -> flag = -1;  // 特殊值，表示用户按了ESC
    			return;     // 直接退出
			/*
			  对应“按下Enter操作 ”,
			  若是在按钮Button控件中按下,我们要结束winrun（光标移动）,进行账号判断并且跳转逻辑
			  若是在编辑Edit控件中按下，我们要跳转到下一个非Label控件 
			*/
			case KEY_ENTER:  
				if(this->arr[i]->getType() == BUTTON) // 若是在按钮Button控件中按下
				{
					this->flag = i; //记录当前光标走到哪个组件了
					return ; //退出函数，返回到业务逻辑层(CLoginWin) 
				}
				else if(this->arr[i]->getType() == EDIT) // 若是在编辑Edit控件中按下
				{
					i++;
					// 光标运动到最后一个时，回到第一个
					if(i >= this->count - 1)
					{
						i = 0;	
					} 	
					// 跳过LABEL组件 
					while(this->arr[i]->getType() == Label)
					{
						if(i < this->count - 1)
						{
							i++;	
						} 
						else
						{
							i = 0;
						}
					} 
					//移动光标到新控件位置
			   	 	CTool::gotoxy(this->arr[i]->getX() + 2, this->arr[i]->getY() + 1);
			    	break;	
				}
				break;
				 
			case KEY_UP: //向上键移动
    			i--;
    			//如果小于0，跳到最后一个
    			if(i < 0) 
				{
        			i = this->count - 1;	
    			} 
    
			    //跳过Label控件
			    while(this->arr[i]->getType() == Label) 
				{
			        if(i > 0) 
					{
			            i--;	
			        } 
					else 
					{
			            i = this->count - 1;  //回到最后一个
			        }
			    } 
			    
			    //移动光标到新控件位置
			    CTool::gotoxy(this->arr[i]->getX() + 2, this->arr[i]->getY() + 1);
			    break;
			    
			case KEY_DOWN: //光标向下移动
				i++;
				//光标运动到最后一个时，回到第一个
				if(i >= this->count) //当组件数量是5个时，下标是 0 1 2 3 4，所以不能相等 
				{
					i = 0;	
				} 
				//跳过Label组件
				while(this->arr[i]->getType() == Label)
				{
					if(i < this->count - 1) //当前组件不是最后一个时(win->count-1) ，都可以++ 
					{
						i++;	
					}
					else
					{
						i = 0;
					}
				} 
				CTool::gotoxy(this->arr[i]->getX() + 2, this->arr[i]->getY() + 1);
				break;
			case KEY_LEFT: //光标向左移动
				if(this->arr[i]->getType() == EDIT) //编辑框才行 
				{
					int count;
					// 获取现在已经有多少个字符 
					count = strlen(this->arr[i]->getContext());
					
					if(count > 0) //有字符，才可以移动
					{
						if(pos == 0)
						{
							pos = count;
							CTool::gotoxy(this->arr[i]->getX() + 2 + pos,this->arr[i]->getY()+ 1);
						} 
						else //不在最左边就左移
						{
							pos--;
							CTool::gotoxy(this->arr[i]->getX() + 2 + pos,this->arr[i]->getY() + 1);  
						}
						
					} 
				}
				break;
			case KEY_RIGHT: //光标向右移动
				
				if(this->arr[i]->getType() == EDIT) //编辑框才行 
				{
					int count;
					// 获取现在已经有多少个字符 
					count = strlen(this->arr[i]->getContext());
					
					if(count > 0) //有字符，才可以移动
					{
						if(pos == count) //如果此时指针在最右边 
						{
							pos = 0;
							CTool::gotoxy(this->arr[i]->getX() + 2 + pos,this->arr[i]->getY() + 1);
						} 
						else //不在最右边就左移 
						{
							pos++;
							CTool::gotoxy(this->arr[i]->getX() + 2 + pos,this->arr[i]->getY()+ 1);  
						}
							
					} 
				}
				break;
				 
			default: // 其他按键： 可能是输入字符 
				// 检查选中的控件是否是编辑框 
				if(this->arr[i]->getType() == EDIT)
				{
					// 向下转型 : CControl* -> CEdit* 
					CEdit *edit =(CEdit*)this->arr[i];
					
					// 调用 CEdit::input() 处理输入 
					edit->input(ikey);	
				} 
				break;
		}	
	} 
}


	
// getter
int CWindow::getWinX()
{
	return this->winX;
}

int CWindow::getWinY()
{
	return this->winY;
}

int CWindow::getWinWidth()
{
	return this->winWidth;
}

int CWindow::getWinHeight()
{
	return this->winHeight;
}

CControl**CWindow::getArr()
{
	return this->arr;
}

int CWindow::getResult()
{
    return this->result;
}
		
// setter
void CWindow::setWinX(int winX)
{
	this->winX = winX;	
}

void CWindow::setWinY(int winY)
{
	this->winY = winY;
}

void CWindow::setWinWidth(int winWidth)
{
	this->winWidth = winWidth;
}

void CWindow::setWinHeight(int winHeight)
{
	this->winHeight = winHeight;
}
