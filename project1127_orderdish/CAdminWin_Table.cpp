#include "CAdminWin_Table.h"

// 构造函数
CAdminWin_Table::CAdminWin_Table()
    : CWindow(10, 2, 70, 26)
{
    currentPage = 1;
    pageSize = 3;
    selectedTable = NULL;    // 添加这行
    // 添加控件
    
    // arr[0] 编辑框 
    CEdit* edit = new CEdit(EDIT, 14, 20, 15, 3," ", 10, 2, 1);
    this->addControl(edit);
    
    // arr[1] 开桌点菜按钮 
    CButton* btn = new CButton(BUTTON, 32, 20, 14, 3, "开桌点菜");
    this->addControl(btn);
    
    // arr[2] 上一页按钮 
    CButton* btn1 = new CButton(BUTTON, 18, 23, 14, 3, "上一页");
    this->addControl(btn1);
    
    // arr[3] 页码标签
    CLabel* label = new CLabel(Label, 35, 24, 0, 0, "1 / 1");
    this->addControl(label);
    
    // arr[4] 下一页按钮
    CButton* btn2 = new CButton(BUTTON, 50, 23, 14, 3, "下一页");
    this->addControl(btn2);
}

// 析构函数
CAdminWin_Table::~CAdminWin_Table() 
{
    // 释放所有控件
    for(int i = 0; i < this->count; i++)
    {
        if(this->arr[i] != NULL)
        {
            delete this->arr[i];
            this->arr[i] = NULL;
        }
    }
}

/*
	获取选中的台桌
	添加变量selectedTable 是为了在窗口之间传递数据，
	因为状态机模式下窗口不再直接创建下一个窗口，
	需要通过成员变量把数据"带出去"给 main 
*/
TABLE* CAdminWin_Table::getSelectedTable()
{
    return this->selectedTable;
}

// 重写show
void CAdminWin_Table::show() 
{
    // 调用父类show - 画边框和控件
    CWindow::show();
    
    // 绘制表格+数据
    drawTable();
}

// 绘制台桌列表
void CAdminWin_Table::drawTable() 
{
    // 1. 获取CTableManager
    CTableManager* tbMgr = CTableManager::getInstance();
    int totalCount = tbMgr->getTableCount();
    
    // 2. 计算总页数
    if(totalCount == 0) 
    {
        allPage = 1;
    } 
    else 
    {
        if(totalCount % pageSize == 0)
        {
            allPage = totalCount / pageSize;
        }
        else
        {
            allPage = (totalCount / pageSize) + 1;
        }
    }
    
    // 3. 更新页码标签
    char pageText[20];
    sprintf(pageText, "%d / %d", currentPage, allPage);
    
    arr[3]->setContext(pageText);
    arr[3]->showControl();
    
    // 4. 绘制表格边框
    CTool::printTable(13, 3, 64, 16, 4, 4);
    
    // 5. 显示表头
    CTool::gotoxy(17, 5);   printf("ID");
    CTool::gotoxy(33, 5);   printf("台桌号");
    CTool::gotoxy(49, 5);   printf("状态");
    CTool::gotoxy(65, 5);   printf("描述");
    
    // 6. 显示当前页数据
    int startIndex = (currentPage - 1) * pageSize;
    
    for(int i = 0; i < pageSize; i++)
    {
        int dataIndex = startIndex + i;
        if(dataIndex >= totalCount) break;
        
        TABLE* table = tbMgr->getTableByIndex(dataIndex);
        if(table == NULL) continue;
        
        int dataY = 5 + 4 + (i * 4);
        
        CTool::gotoxy(17, dataY);  printf("%d", table->tableID);
        CTool::gotoxy(33, dataY);  printf("%s", table->tableNum);
        CTool::gotoxy(49, dataY);
        if(table->status == 0) printf("空闲");
        else printf("占用");
        CTool::gotoxy(65, dataY);  printf("%s", table->description);
    }
}

void CAdminWin_Table::handle() {
    bool running = true;
    while(running) 
	{
        if(this->flag == 1)  // 开桌点菜按钮
        {
            char* tableNum = arr[0]->getContext();
            
            CTableManager* mgr = CTableManager::getInstance();
            TABLE* table = mgr->getTableBynum(tableNum);
            
            if(table == NULL) 
            {
                CTool::gotoxy(30, 28);
                printf("台桌号不存在！");
                Sleep(1000);
                system("cls");
                this->show();
                this->run();
            }
            else if(table->status == 1) 
            {
                CTool::gotoxy(30, 28);
                printf("该台桌已被占用！");
                Sleep(1000);
                system("cls");
                this->show();
                this->run();
            }
            else 
            {
                // 选择成功
                this->selectedTable = table;    // 保存选中的台桌
                this->result = 1;               // 1 = 选择成功，跳转点菜
                running = false;
            }
        }
        else if(this->flag == 2) {
            if(currentPage > 1) 
            {
                currentPage--;
                system("cls");
                this->show();
                this->run();
            }
            else 
            {
                CTool::gotoxy(30, 28);
                printf("已经是第1页");
                Sleep(1000);
                system("cls");
                this->show();
                this->run();
            }
        }
        else if(this->flag == 4) {
            if(currentPage < allPage) 
            {
                currentPage++;
                system("cls");
                this->show();
                this->run();
            } 
            else 
            {
                CTool::gotoxy(30, 28);
                printf("已经是最后一页");
                Sleep(1000);
                system("cls");
                this->show();
                this->run();
            }
        }
        else if(flag == -1) 
		{
        	running = false;
            this->result = 0;    // 返回管理员窗口/服务员窗口	
//            running = false;
//            system("cls");
//            printf("\n\n 正在返回...\n\n");
//            Sleep(1000);
//            system("cls");
//            
//            CAdminWin* adminWin = new CAdminWin();
//            adminWin->show();
//            adminWin->run();
//            adminWin->handle();
//            delete adminWin;
        }
    }
}
