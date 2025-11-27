#include "CButton.h"

// 无参构造函数
CButton::CButton()
{
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	strcpy(this->context,"");
} 
// 带参构造函数实现
CButton::CButton(int type,int x,int y,int width,int height,const char *context)
:CControl(type,x,y,width,height,(char *)context)  
// 子类接收参数 调用父类构造函数 
// 子类是const char*  父类是char* 所以要强制类型转换   
{
	// 不需要再赋值,父类构造函数已经初始化了
}

// 析构函数
CButton::~CButton()
{
	
} 

/// 实现 showControl() 函数
/// 功能:显示带边框的按钮,文字居中显示
void CButton::showControl()
{
	// 1.画按钮边框 
	CTool::printBoarder(this->x,this->y,this->width,this->height);

	// 2.计算文字长度（一个中文字符占2个位置）
    int textLen = strlen(this->context);
    
    // 3.计算文字居中位置
    // 水平居中：起始位置 + 左边框(1) + (控件宽度 - 文字长度) / 2
    // 控件宽度 = 按钮宽度 -（左边框宽度+右边框宽度） 
    int textX = this->x + 1 + (this->width - 2 - textLen) / 2;
    // 垂直居中
    int textY = this->y + this->height / 2; 
    
	// 4. 定位并打印文字
    CTool::gotoxy(textX, textY);
    printf("%s", this->context);	
} 
// getter
int CButton::getX()
{
	return this->x;
}

int CButton::getY()
{
	return this->y;
}

int CButton::getWidth()
{
	return this->width;
}

int CButton::getHeight()
{
	return this->height;
}

char* CButton::getContext()
{
	return this->context;
}

// setter
void CButton::setX(int x)
{
	this->x = x;
}

void CButton::setY(int y)
{
	this->y = y;
}

void CButton::setWidth(int width)
{
	this->width = width;
}

void CButton::setHeight(int height)
{
	this->height = height;
}

void CButton::setContext(const char* context)
{
	strcpy(this->context,context);
}

//
//
//void showButton(CONTROL btn)
//{
//	//1.画边框 
//	printBoarder(btn.x,btn.y,btn.width,btn.height);
//	
//	//2.计算文字长度（中文字符占2个位置）
//	int textLen = strlen(btn.context);  // 需要#include <string.h> 
//	// 水平居中：起始位置 + 左边框(1) + (可用宽度 - 文字长度) / 2
//	int textX = btn.x + 1 + (btn.width - 2 - textLen) / 2;
//	// 垂直居中
//	int textY = btn.y + btn.height / 2;
//	
//	//3.定位并打印文字 
//	gotoxy(textX, textY);
//	printf("%s",btn.context);
//}	
