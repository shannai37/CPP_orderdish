#ifndef CSTARTWIN_H
#define CSTARTWIN_H

#include "CWindow.h"		// 因为要使用窗口结构体 
#include "CWindowManager.h"	// 因为要调用 jumpToWindow()
#include "CRegisterWin.h"	// 因为要调用CRegisterWin_init() 
#include "CLoginWin.h"		// 因为要调用CLoginWin_init() 
#include <string.h>			// 因为要调用 strcpy()
void CStartWin_init();  

#endif 
