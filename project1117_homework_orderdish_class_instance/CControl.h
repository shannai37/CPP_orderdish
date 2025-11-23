#ifndef CCONTROL_H
#define CCONTROL_H

#include <string.h>
// CControl 类
// 控件基类,所有控件(标签、编辑框、按钮)的父类
// 功能:
//   - 存储控件的通用属性(位置、大小、类型、内容)
//   - 定义纯虚函数 showControl(),强制子类实现显示逻辑
//   - 提供 getter/setter 方法访问 protected 成员
class CControl
{
	protected:	// protected: 子类可以访问,外部不能直接访问 
		int type; 			// 控件类型  0=Label, 1=Edit, 2=Button
		int x; 				// 控件左上角X坐标 
		int y; 				// 控件左上角y坐标	
		int width;			// 控件宽度 
		int height;			// 控件高度 
		char context[20];	// 控件内容(标签文字/编辑框文本/按钮文字)
//		int key;
	public:
		// 无参构造函数
		CControl(); 
		
		// 带参构造函数 
		CControl(int type,int x,int y,int width,int height,char *context); 	
		
		
		// 虚析构函数，确保子类析构函数会被正确调用 
		// 释放窗口时会先释放子类，再释放父类，防止内存泄漏 
		virtual ~CControl(); 	
	
		// 纯虚函数，子类必须实现 
		virtual void showControl() = 0; 
		// getter
		int getType(); 
		int getX();
		int getY();
		int getWidth();
		int getHeight();
//		int getKey();
		char* getContext();
		
		// setter
		void setType(int type);
		void setX(int x);
    	void setY(int y);
    	void setWidth(int width);
    	void setHeight(int height);
//		int setKey(int key);
    	void setContext(const char* context); 
};


#endif
