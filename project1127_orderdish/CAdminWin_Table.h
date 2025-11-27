#ifndef CADMINWIN_TABLE_H
#define CADMINWIN_TABLE_H

#include "CWindow.h"
#include "CButton.h"
#include "CLabel.h"
#include "CEdit.h"          // 需要输入框
#include "CTableManager.h"
#include "CTool.h"
#include "CAdminWin.h"
#include "COrderWin.h" 
class CAdminWin_Table : public CWindow 
{
private:
    int currentPage;
    int pageSize;	// 每页显示多少条 
    int allPage;
    
    void drawTable();  // 绘制台桌列表
    
    TABLE* selectedTable;         // 保存选中的台桌 
    
public:
    CAdminWin_Table();
    ~CAdminWin_Table();
    
    // 重写父类show 
    void show(); // 将边框和控件 + 台桌管理核心（表格+数据）打印出来 
    
    // 实现父类的纯虚函数
    virtual void handle();
    
    TABLE* getSelectedTable();    // 获取选中的台桌
    
    
};

#endif
