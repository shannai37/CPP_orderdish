#ifndef CWAITERWIN_H
#define CWAITERWIN_H

#include "CWindow.h"	
#include "CButton.h"
#include "CLabel.h"
#include "CLoginWin.h"   	// CLoginWin窗口
#include "CInitWin.h" 		// CInitWin 窗口 

class CWaiterWin : public CWindow {
public:
    // 无参构造函数
    CWaiterWin();
    
    // 析构函数
    ~CWaiterWin();
    
    // 实现父类的纯虚函数
    virtual void handle();
};

#endif
