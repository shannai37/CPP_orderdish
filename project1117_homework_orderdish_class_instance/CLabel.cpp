#include "CLabel.h"

// 无参构造函数 
CLabel::CLabel()
{
	
} 

// 带参构造函数实现
CLabel::CLabel(int type,int x,int y,int width,int height,const char* context) 
:CControl(type,x,y,width,height,(char *)context)
{
  
}
// 析构函数 
CLabel::~CLabel()
{
	
} 

/// 标签控件类,继承自 父类CControl 的纯虚函数showControl()  
/// 功能:显示静态文字(标题、提示信息等)
/// 标签不需要边框,只显示文字
void CLabel::showControl()
{ 
	// 1.移动光标到标签位置
	CTool::gotoxy(this->x,this->y);
	
	// 2. 显示标签内容
	printf("%s", this->context);	
}
