#ifndef CWINDOW_H
#define CWINDOW_H
#include "CControl.h"
#include "CEdit.h"
#include "CLabel.h"


/// CWindow 类
/// 窗口基类,所有窗口(初始窗口、登录窗口、注册窗口等)的父类
/// 功能:
///   - 存储窗口的通用属性(位置、大小、控件数组)
///   - 提供控件管理方法(添加控件、显示控件)
///   - 提供用户交互方法(处理键盘输入、光标移动)
///   - 定义纯虚函数 handle(),强制子类实现业务逻辑
class CWindow
{
	public:
		// 构造函数 
		CWindow();
		CWindow(int winX,int winY,int winWidth,int winHeight);
		
		// 虚析构函数 
		virtual~CWindow();
		
		// 添加控件到窗口 
		void addControl(CControl* con);
		
		// 显示窗口（画边框 + 显示所有控件） 
		void show();
		
		// 运行窗口（处理键盘输入、光标移动） 
		void run();
		
		
		// 每个窗口的业务逻辑 
		virtual void handle() = 0; 
		
		
		// getter
		int getWinX();
		int getWinY();
		int getWinWidth();
		int getWinHeight();
		CControl** getArr();
		
		// setter
		void setWinX(int winX);
		void setWinY(int winY);
		void setWinWidth(int winWidth);
		void setWinHeight(int winHeight);
		
		protected: 					// protected: 子类可以访问,外部不能直接访问 
			int winX;				// 窗口左上角X坐标
			int winY;				// 窗口左上角Y坐标
			int winWidth;			// 窗口宽度 
			int winHeight;			// 窗口高度 
			
			CControl *arr[20];		 // 控件数组,最多存储20个控件
			int count; 				//已添加的控件数量 
			int flag; 				//纪录业务下标(即当前光标走到哪个组件了) 
			
};

#endif
