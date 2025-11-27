#ifndef CADMINWIN_DM
#define CADMINWIN_DM

#include "CWindow.h"
#include "CButton.h"
#include "CLabel.h"
#include "CDishManager.h"  // 菜品管理器 
#include "CTool.h"
#include "CAdminWin.h" 
class CAdminWin_DM : public CWindow {
	private:
		int currentPage;	 // 当前页码
		int pageSize;	 	 // 每页显示多少条
		int allPage;		 // 总页数 
		
		
		void drawTable(); 	// 绘制表格和数据 (是我们菜品管理页面的核心部分)
	public:
		
		CAdminWin_DM();  	// 构造函数 
		~CAdminWin_DM(); 	// 析构函数 
		
		
		
		// 重写父类show 
		void show();  // 将边框和控件 + 菜品管理核心（表格+数据）打印出来 
		
		// 实现父类的纯虚函数
    	virtual void handle();
}; 



//void CAdminWin_DM();
//
//void FillTable_DM(int nowPage, int AllPage, int pageSize);	
#endif
