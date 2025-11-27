#ifndef CINITWIN_H
#define CINITWIN_H

#include "CWindow.h"
#include "CLabel.h"
#include "CButton.h"
#include "CLoginWin.h"
#include "CRegisterWin.h"
#include <stdlib.h> // 清屏
 
class CInitWin : public CWindow
{
	public:
		// 无参构造函数
		CInitWin();
	
		// 实现父类的纯虚函数
	    virtual void handle();
		
		// 析构函数
		~CInitWin();
	
	 
};




#endif  
