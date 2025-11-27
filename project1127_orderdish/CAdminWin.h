#ifndef CADMINWIN_H
#define CADMINWIN_H



//#include "CStartWin.h"   	// 因为要调用 CStartWin_init()
//#include "CWindowManager.h" // 因为要调用 jumpToWindow()
//#include "CAdminWin_PM.h"	// 因为要调用 CAdminWin_PM() 
//#include <string.h>			// 因为要调用 strcpy()
//#include "CAdminWin_DM.h"   // CAdminWin_DM()

#include "CWindow.h"		
#include "CButton.h"
#include "CLabel.h"
#include "CLoginWin.h"   	// CLoginWin窗口
#include "CInitWin.h" 		// CInitWin 窗口 
#include <stdlib.h>
#include "CButton.h"
#include "CLabel.h"
#include "CAdminWin_DM.h"
#include "CAdminWin_PM.h"
#include "CAdminWin_Table.h" 
class CAdminWin : public CWindow {
public:
    // 无参构造函数
    CAdminWin();
    
    // 析构函数
    ~CAdminWin();
    
    // 实现父类的纯虚函数
    virtual void handle();
};


#endif
