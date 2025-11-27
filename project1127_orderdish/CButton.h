#ifndef CBUTTON_H
#define CBUTTON_H

#include "CTool.h"
#include <string.h>
#include "CControl.h"

/// CButton 类
/// 按钮控件类,继承自 CControl
/// 功能:显示可点击的按钮,用户按Enter键触发操作
class CButton:public CControl 
{
	private:

	public:
		// 无参构造函数
		CButton(); 
		
		// 带参构造函数 ,因为我们传入的是字符串常量(比如"张三"),所以加const，不加会报警告 
		CButton(int type,int x,int y,int width,int height,const char *context); 
		
		// 析构函数
		~CButton(); 
		
		// 显示按钮 实现父类的纯虚函数 
		virtual void showControl(); 
		 
		// getter
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		char* getContext();
		
		// setter
		void setX(int x);
    	void setY(int y);
    	void setWidth(int x);
    	void setHeight(int y);
    	void setContext(const char* context);
		
			
};


////void showButton(BTN btn);
//void showButton(CONTROL btn);
 
#endif
