#include "COrderWin.h"

// 构造函数
COrderWin::COrderWin(TABLE* table)
    : CWindow(10, 2, 70, 26)
{
    // 保存台桌指针
    currentTable = table;
    
    // 获取菜品数量
    CDishManager* dishMgr = CDishManager::getInstance();
    int dishCount = dishMgr->getDishCount();
    
    // 初始化orderCount，所有菜的点餐数量都是0
    for(int i = 0; i < dishCount; i++) 
    {
        orderCount.push_back(0);
    }
    
    // 初始化当前页、每页显示数量
    currentPage = 1;
    pageSize = 3;
    
    // 初始化总金额和总份数
    totalprices = 0;
    totalCount = 0;
    
    // 添加控件
    
    // arr[0] 菜编号输入框
    CEdit* edit1 = new CEdit(EDIT, 14, 20, 10, 3, " ", 6, 2, 1);
    this->addControl(edit1);
    
    // arr[1] 份数输入框
    CEdit* edit2 = new CEdit(EDIT, 28, 20, 10, 3, " ", 6, 2, 1);
    this->addControl(edit2);
    
    // arr[2] 确定按钮
    CButton* btnOK = new CButton(BUTTON, 42, 20, 10, 3, "确定");
    this->addControl(btnOK);
    
    // arr[3] 返回按钮
    CButton* btnBack = new CButton(BUTTON, 56, 20, 10, 3, "返回");
    this->addControl(btnBack);
    
    // arr[4] 上一页按钮
    CButton* btn1 = new CButton(BUTTON, 18, 23, 12, 3, "上一页");
    this->addControl(btn1);
    
    // arr[5] 页码标签
    CLabel* label2 = new CLabel(Label, 35, 24, 0, 0, "1 / 1");
    this->addControl(label2);
    
    // arr[6] 下一页按钮
    CButton* btnNext = new CButton(BUTTON, 50, 23, 12, 3, "下一页");
    this->addControl(btnNext);
}

// 析构函数
COrderWin::~COrderWin()
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

// 重写show 
void COrderWin::show()
{
    // 调用父类show - 画边框和控件
    CWindow::show();
    
    // 绘制菜品列表 
    drawDishList();
} 

// 绘制菜品列表
void COrderWin::drawDishList()
{
    // 1. 获取CDishManager
    CDishManager* dishMgr = CDishManager::getInstance();
    int totalDishCount = dishMgr->getDishCount();
    
    // 2. 计算总页数
    if(totalDishCount == 0) 
    {
        allPage = 1;
    } 
    else 
    {
        if(totalDishCount % pageSize == 0)
        {
            allPage = totalDishCount / pageSize;
        }
        else
        {
            allPage = (totalDishCount / pageSize) + 1;
        }
    }
    
    // 3. 更新页码标签
    char pageText[20];
    sprintf(pageText, "%d / %d", currentPage, allPage);
    arr[5]->setContext(pageText);
    arr[5]->showControl();
    
    // 4. 绘制表格边框（4列：菜编号、菜名、价格、份数）
    CTool::printTable(13, 3, 64, 16, 4, 4);
    
    // 5. 显示表头
    CTool::gotoxy(17, 5);   printf("菜编号");
    CTool::gotoxy(33, 5);   printf("菜名");
    CTool::gotoxy(49, 5);   printf("价格");
    CTool::gotoxy(63, 5);   printf("份数");
    
    // 6. 显示当前页数据
    int startIndex = (currentPage - 1) * pageSize;
    
    for(int i = 0; i < pageSize; i++)
    {
        int dataIndex = startIndex + i;
        if(dataIndex >= totalDishCount) break;
        
        DISH* dish = dishMgr->getDishByIndex(dataIndex);
        if(dish == NULL) continue;
        
        int dataY = 5 + 4 + (i * 4);
        
        // 菜编号（如果已点，前面加*）
        CTool::gotoxy(17, dataY);
        if(orderCount[dataIndex] > 0)
        {
            printf("*%d", dish->menuID);
        }
        else
        {
            printf("%d", dish->menuID);
        }
        
        // 菜名
        CTool::gotoxy(33, dataY);  printf("%s", dish->menuName);
        
        // 价格
        CTool::gotoxy(49, dataY);  printf("%.1f", dish->price);
        
        // 份数
        CTool::gotoxy(63, dataY);  printf("%d", orderCount[dataIndex]);
    }
    
    // 7. 计算并显示总金额和总份数
    calculateTotal();
    CTool::gotoxy(30, 18);
    printf("总金额：%.1f    份数：%d", totalprices, totalCount);
}

// 计算总金额和总份数 
void COrderWin::calculateTotal()
{
    // 先清零！
    totalprices = 0;
    totalCount = 0;
    
    // 获取菜品管理器
    CDishManager* dishMgr = CDishManager::getInstance();
    int dishCount = dishMgr->getDishCount();
    
    for(int i = 0; i < dishCount; i++)
    {
        if(orderCount[i] > 0)
        {
            // 获取菜品信息
            DISH* dish = dishMgr->getDishByIndex(i);
            
            // 累加总份数
            totalCount += orderCount[i];
            
            // 累加总金额 = 单价 * 份数
            totalprices += dish->price * orderCount[i];
        }
    }
}

// 确认下单（更新台桌状态）
void COrderWin::confirmOrder()
{
    // 更新台桌状态为"占用"
    CTableManager* tableMgr = CTableManager::getInstance();
    tableMgr->updateTableStatus(currentTable->tableID, 1);  // 1表示占用
    
    printf("\n 下单成功！台桌 %s 已开桌。\n", currentTable->tableNum);
}

// 处理用户输入
void COrderWin::handle()
{
    bool running = true;
    while(running)
    {
        if(this->flag == 2)  // arr[2] 确定按钮
        {
            // 1. 获取输入的菜编号和份数
            char* menuIDStr = arr[0]->getContext();
            char* qtyStr = arr[1]->getContext();
            
            int menuID = atoi(menuIDStr);  // 字符串转整数
            int qty = atoi(qtyStr);
            
            // 2. 查找菜品
            CDishManager* dishMgr = CDishManager::getInstance();
            DISH* dish = dishMgr->getDishByID(menuID);
            
            if(dish == NULL)
            {
                CTool::gotoxy(30, 26);
                printf("菜品不存在！");
                Sleep(1000);
            }
            else if(qty <= 0)
            {
                CTool::gotoxy(30, 26);
                printf("份数必须大于0！");
                Sleep(1000);
            }
            else
            {
                // 3. 找到菜品在vector中的索引
                for(int i = 0; i < dishMgr->getDishCount(); i++)
                {
                    DISH* d = dishMgr->getDishByIndex(i);
                    if(d->menuID == menuID)
                    {
                        orderCount[i] += qty;  // 累加份数
                        break;
                    }
                }
                
                CTool::gotoxy(30, 26);
                printf("添加成功！");
                Sleep(500);
            }
            
            // 刷新界面
            system("cls");
            this->show();
            this->run();
        }
        else if(this->flag == 3)  // arr[3] 返回按钮
        {
            // 如果有点菜，先确认下单
            if(totalCount > 0)
            {
                confirmOrder();
                Sleep(1000);
            }
            
            running = false;
            this->result = 0;    // 返回台桌选择窗口
            
//            // 返回台桌管理窗口
//            CAdminWin_Table* tableWin = new CAdminWin_Table();
//            tableWin->show();
//            tableWin->run();
//            tableWin->handle();
//            delete tableWin;
        }
        else if(this->flag == 4)  // arr[4] 上一页
        {
            if(currentPage > 1) 
            {
                currentPage--;
                system("cls");
                this->show();
                this->run();
            }
            else 
            {
                CTool::gotoxy(30, 26);
                printf("已经是第1页");
                Sleep(1000);
                system("cls");
                this->show();
                this->run();
            }
        }
        else if(this->flag == 6)  // arr[6] 下一页
        {
            if(currentPage < allPage) 
            {
                currentPage++;
                system("cls");
                this->show();
                this->run();
            } 
            else 
            {
                CTool::gotoxy(30, 26);
                printf("已经是最后一页");
                Sleep(1000);
                system("cls");
                this->show();
                this->run();
            }
        }
        else if(this->flag == -1)  // ESC退出
        {
            running = false;
    		this->result = 0;    // 返回台桌选择窗口
        }
    }
}
