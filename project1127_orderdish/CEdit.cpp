#include "CEdit.h"

// 无参构造函数
CEdit::CEdit():CControl()
{
	this->maxLen = 0;
	this->inputType = 0;
	this->ips = 0;
} 


/// 有参构造函数
/// 参数:
///   type - 控件类型 (EDIT)
///   x, y - 编辑框左上角坐标
///   width, height - 编辑框宽度和高度
///   context - 初始内容 (通常为空字符串 "")
///   maxLen - 最大输入长度
///   inputType - 输入类型 (0=纯数字, 1=纯字母, 2=字母+数字, 3=所有字符)
///   ips - 显示方式 (1=明文, 0=密文)
CEdit::CEdit(int type,int x,int y,int width,int height,char* context,int maxLen,int inputType,int ips)
:CControl(type,x,y,width,height,context)	// 调用父类构造函数 
{
	// 初始化 CEdit 特有的成员变量 
	this->maxLen = maxLen;
	this->inputType = inputType;
	this->ips = ips;
}


/// 显示编辑框 以及编辑框内的数字和字母 
/// 功能:
///   1. 画编辑框边框
///   2. 根据 ips 决定显示明文还是密文 
void CEdit::showControl()
{
	// 1. 绘制边框
    CTool::printBoarder(this->x, this->y, this->width, this->height);
    
    // 2.显示已经输入的数据
    // x + 1: 跳过左边框
    // y + 1: 跳过上边框 
   	CTool::gotoxy(this->x + 1, this->y + 1);
   	
   	// 3.根据ips决定显示方式 
    if(this->ips == 1) 
	{
        // 明文显示
        printf("%s", this->context);
    }
    else if(this->ips == 0)  
	{
        // 密文显示：显示 * 号
		int len = strlen(this->context); 
        for(int i = 0 ; i < len ; i++)
        {
            printf("*"); // 每个字符显示为 * 
        }
	}	
}

// 构造函数 
CEdit::~CEdit()
{
	
}

/// 处理键盘输入
/// 参数:
///   key - 按键码 (ASCII码)
/// 功能:
///   1. 处理 Backspace 删除
///   2. 检查是否超过最大长度
///   3. 根据 inputType 过滤输入
///   4. 根据 ips 决定显示方式
void CEdit::input(int key)
{	
	// 获取当前字符长度 
	int len = strlen(this->context);
	
	// 1.处理 Backspace 删除
	if(key == 8)   // 8: Backspace的ASCII码 
	{  
        if(len > 0) // 如果有内容能删除的话 
		{
			// 删除最后一个字符(将最后一个字符改成结束符)
            this->context[len - 1] = '\0';  
            
            // 重新显示编辑框(清空后重新画)
            this->showControl();
        }
        return; // 处理完毕，直接返回 
    }
    // 2.检查是否超过最大长度
	if(len >= this->maxLen)
	{
		return;  // 已满，直接返回，这次输入无效	
	} 
	
	 // 3. 根据 inputType 过滤输入
    bool Valid = false;
    // 0:纯数字  1:纯字母 2:字母+数字 
    switch(this->inputType)
	{
		case 0: // 纯数字
			if(key >= '0' && key <= '9')
			{
				Valid = true;		
			} 
			break;
		case 1: // 纯字母
		 	if( (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') )
			{
				Valid = true;		
			} 
			break;
		case 2: // 字母+数字
			if( (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') )
			{
				Valid = true;		
			} 
			break; 
	} 
	
	// 4.如果输入有效，添加字符
	if(Valid)
	{
			
		this->context[len] = (char)key; // 添加字符 
		this->context[len + 1] = '\0';   // 结束符
		
		// 5. 移动光标到新字符位置 根据 ips 决定显示方式 明文：1  密文：0 
		// x + 1:跳过左边框 y + 1:跳过上边框  len:已有字符的长度 
        CTool::gotoxy(this->x + 1 + len, this->y + 1);
        
        if(this->ips == 1) 
		{
            // 明文显示
            printf("%c", (char)key);
        }
        else if(this->ips == 0)  
		{
            // 密文显示：显示 * 
            printf("*");
        }
	} 
    
	// 如果Valid == false，什么都不做，忽略这次输入 
	 
}

int CEdit::getMaxLen()
{
	return this->maxLen;
}

int CEdit::getInputType()
{
	return this->inputType;
}

int CEdit::getIps()
{
	return this->ips;
}


int CEdit::setMaxLen(int maxlen)
{
	this->maxLen = maxLen;
}

int CEdit::setInputType(int inputType)
{
	this->inputType = inputType;
}
int CEdit::setIps(int ips)
{
	this->ips = ips;
}


