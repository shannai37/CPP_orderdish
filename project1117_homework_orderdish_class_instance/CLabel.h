#ifndef CLABEL_H
#define CLABEL_H

#include "CTool.h"
#include "CControl.h"
#include <string.h>


/// CLabel 类
/// 标签控件类,继承自 CControl
/// 功能:显示静态文字(标题、提示信息等)
class CLabel:public CControl 
{
private:
	
public:
	// 无参构造函数 
	CLabel(); 
    // 带参构造函数 ,因为我们传入的是字符串常量(比如"张三"),所以加const，不加会报警告 
    CLabel(int type,int x,int y,int width,int height,const char* context);
    // 析构函数 
	~CLabel(); 
    // 实现父类的纯虚函数 
    virtual void showControl(); 
    
};

#endif
