#ifndef CManagerWIN_H
#define CManagerWIN_H

#include "CWindow.h"		
#include "CButton.h"
#include "CLabel.h"
#include "CLoginWin.h"   	// CLoginWin窗口
#include "CInitWin.h" 		// CInitWin 窗口 
#include <stdlib.h>
class CManagerWin : public CWindow
{
	public:
		// 无参构造函数
		CManagerWin();
		
		// 实现父类的纯虚函数
		virtual void handle();
		
		// 析构函数
		~CManagerWin(); 
	
}; 



#endif

