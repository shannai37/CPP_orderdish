#ifndef CORDERWIN_H
#define CORDERWIN_H

#include <vector>
#include "CWindow.h"
#include "CTableManager.h"
#include "CDishManager.h"
#include "CButton.h"
#include "CLabel.h"
#include "CEdit.h"          // 需要输入框
#include "CAdminWin_Table.h"
class COrderWin : public CWindow
{
	public:
		COrderWin(TABLE* table); // 构造函数，传入台桌
		~COrderWin();
		
		
		void show();	  		 // 重写父类的show函数 显示窗口+菜品表格 	
		void handle();    		// 处理输入
		void drawDishList();    // 绘制菜品列表
    	void calculateTotal();  // 计算总金额和总份数
    	void confirmOrder();    // 确认下单（更新台桌状态）
		
	private:
		TABLE* currentTable;  	// 当前台桌
		vector<int> orderCount;   // 每个菜点的份数 
		double totalprices;		// 订单总金额
		int totalCount;			// 总份数
		 
		int currentPage; 		// 菜品列表当前页
		int pageSize;	 		// 每页显示数量
		int allPage;	 		// 总页面
		
		
		
};

#endif 
