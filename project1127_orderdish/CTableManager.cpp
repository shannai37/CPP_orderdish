#include "CTableManager.h"

// 初始化静态成员变量
// 在类外部初始化静态成员
// 初始值为 NULL,表示还没有创建实例
CTableManager* CTableManager::instance = NULL;

// 私有构造函数 - 初始化台桌
CTableManager::CTableManager()
{
    TABLE tb1 = {1, "z1", 0, "靠窗桌"};
    tables.push_back(tb1); 
    TABLE tb2 = {2, "z2", 0, "靠窗"}; 
    tables.push_back(tb2);
    TABLE tb3 = {3, "z3", 0, "靠窗桌"}; 
    tables.push_back(tb3);
    TABLE tb4 = {4, "z4", 0, "靠过边"}; 
    tables.push_back(tb4);
    TABLE tb5 = {5, "z5", 1, "中间"};  
    tables.push_back(tb5);
    TABLE tb6 = {6, "z6", 1, "靠墙"}; 
    tables.push_back(tb6);
    TABLE tb7 = {7, "z7", 0, "西北角"}; 
    tables.push_back(tb7);
    TABLE tb8 = {8, "z8", 0, "北边"}; 
    tables.push_back(tb8);
    TABLE tb9 = {9, "z9", 0, "西北角"}; 
    tables.push_back(tb9);
    
    printf("CTableManager 台桌管理器实例已创建\n"); 
    printf("CTableManager 已加载 %d 张台桌\n", tables.size()); 
}

// 析构函数
CTableManager::~CTableManager()
{
    printf("CTableManager 台桌管理器实例已销毁\n");  
}

// 获取单例实例
CTableManager* CTableManager::getInstance()
{
    // 检查实例是否已创建
    if(instance == NULL)
    {    
        // 实例不存在,创建新实例
        instance = new CTableManager();
    }
    // 返回唯一实例
    return instance;
}

// 销毁单例实例
// 功能: 释放单例类的内存
void CTableManager::destroyInstance()
{
    if(instance != NULL) 
    {
        // 释放实例内存 (会调用析构函数)
        delete instance;
        
        // 指针置空,防止悬空指针
        instance = NULL;
    }    
}

// getter 

// 获取台桌数量
int CTableManager::getTableCount()
{
    return tables.size(); 
}

// 通过索引获取台桌
TABLE* CTableManager::getTableByIndex(int index) 
{
    // 检查index是否越界
    if(index < 0 || index >= tables.size()) 
    {
        return NULL;     // 没找到
    }
    return &tables[index];     // 返回指针
}

// 通过台桌号查找台桌
TABLE* CTableManager::getTableBynum(char* num)
{
    // 遍历tables查找
    for(int i = 0; i < tables.size(); i++) 
    {
    	// 字符串比较要用strcmp，我刚开始搞错了！ 
        if(strcmp(tables[i].tableNum, num) == 0)  
        {
            return &tables[i];
        }
    }
    
    return NULL;  // 没找到
}

// 通过ID查找台桌
TABLE* CTableManager::getTableByID(int tableID) 
{
    // 遍历tables查找
    for(int i = 0; i < tables.size(); i++) 
    {
        if(tables[i].tableID == tableID) 
        {
            return &tables[i];
        }
    }
    
    return NULL;  // 没找到
}

// setter 

// 添加台桌
bool CTableManager::addTable(int id, char* num, int status, char* desc)  
{
    // 1. 检查ID是否已存在
    if(getTableByID(id) != NULL)  
    {
        printf("台桌ID %d 已存在！\n", id);  
        return false;
    }
    
    // 2. 创建新台桌
    TABLE newTable;
    newTable.tableID = id;  
    strcpy(newTable.tableNum, num);  
    newTable.status = status;
    strcpy(newTable.description, desc);
    
    // 3. 添加到vector
    tables.push_back(newTable);
    
    // 4. 返回成功
    printf("添加台桌成功: %s\n", num);  
    return true;
}

// 修改台桌状态
bool CTableManager::updateTableStatus(int tableID, int newStatus)  // ? 修正：加类名
{
    // 1. 遍历查找台桌
    for(int i = 0; i < tables.size(); i++) 
    {
        if(tables[i].tableID == tableID) 
        {
            // 2. 找到了，修改状态
            tables[i].status = newStatus;
            printf("修改台桌 %d 状态成功！\n", tableID);
            return true;
        }
    }
    
    // 3. 没找到
    printf("台桌ID %d 不存在！\n", tableID);
    return false;
}
