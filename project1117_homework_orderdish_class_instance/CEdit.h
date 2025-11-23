#ifndef CEDIT_H
#define CEDIT_H

#include "CTool.h"
#include "CControl.h"

 
/// CEdit 类
/// 编辑框控件类,继承自 CControl
/// 功能:接收用户输入,支持输入过滤和明文/密文显示
class CEdit:public CControl
{
	private:				// private: 只有 CEdit 类内部可以访问
		int maxLen;			// 最大输入长度 (例如: 20 表示最多输入20个字符)
		int inputType;		// 输入类型过滤器: 0-纯数字 1-纯字母 2-数字+字母 
		int ips;			// 显示方式: 0-密文显示 1-明文显示 

	public:
		// 无参构造函数
		CEdit(); 
		
		// 带参构造函数 
		CEdit(int type,int x,int y,int width,int height,char* context,int maxLen,int inputType,int ips); 	
		
		// 析构函数
		~CEdit(); 
		
		// 实现父类的纯虚函数 显示编辑框 
		virtual void showControl(); 
		
		// 编辑框输入控制 处理键盘输入 
		void input(int key); 
		
		// getter 
		int getMaxLen();
		int getInputType();
		int getIps();
		
		//setter
		int setMaxLen(int maxlen);
		int setInputType(int inputType);
		int setIps(int ips); 
		
};

//void showEdit(CONTROL edt);
//
//void inputControl(int maxLen,int inputType,int ips,char str[20],int key); 
#endif
