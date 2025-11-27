#ifndef CADMINWIN_H
#define CADMINWIN_H

#include "CWindow.h"		// 因为要使用窗口结构体 
#include "CLoginWin.h"   	// 因为要调用 CLoginWin_init()
#include "CStartWin.h"   	// 因为要调用 CStartWin_init()
#include "CWindowManager.h" // 因为要调用 jumpToWindow()
#include "CAdminWin_PM.h"	// 因为要调用 CAdminWin_PM() 
#include <string.h>			// 因为要调用 strcpy()
#include "CAdminWin_DM.h"   // CAdminWin_DM()
void CAdminWin_init();

#endif
