#include "CDishManager.h"

// 初始化静态成员变量
/// 初始值为 NULL,表示还没有创建实例
CDishManager* CDishManager::instance = NULL;

// 构造函数 初始化数据 
CDishManager::CDishManager()
{
	DISH dish1 = {1001, "宫保鸡丁", 28.5, 10};
	dishes.push_back(dish1);
	DISH dish2 = {1002, "炒饭", 15.5, 30};
	dishes.push_back(dish2);
	DISH dish3 = {1003, "牛肉饭", 20.99, 15};
	dishes.push_back(dish3);
	DISH dish4 = {1004, "番茄炒蛋", 13.9, 20};
	dishes.push_back(dish4);
	DISH dish5 = {1005, "番茄炒番茄", 9.9, 21};
	dishes.push_back(dish5);
	printf("CDishManager 菜品管理器实例已创建\n");	
}	

// 析构函数
CDishManager::~CDishManager() 
{
    printf("CDishManager 菜品管理器实例已销毁\n");
}

// 获取单例实例 
CDishManager* CDishManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new CDishManager();	
	}	
	
	return instance;
} 

// 销毁单例实例
void CDishManager::destroyInstance() 
{
    if(instance != NULL) 
	{
        delete instance;
        instance = NULL;
    }  
}


//getter

// 获取菜品数量
int CDishManager::getDishCount() 
{
   return dishes.size(); 
}

// 根据索引获取菜品（1001 是ID，不是索引） 
DISH* CDishManager::getDishByIndex(int index) 
{
    // 检查index是否越界
    if(index < 0 || index >= dishes.size())
    {
        return NULL; // 没找到 
	}
    // 返回指针
    return &dishes[index];
}

// 根据菜品ID查找
DISH* CDishManager::getDishByID(int menuID) 
{
    // 遍历dishes查找
    for(int i = 0; i < dishes.size(); i++) 
	{
         if(dishes[i].menuID == menuID) 
		 {
             return &dishes[i];
         }
    }
   
    return NULL;  // 没找到
}

// setter
// 添加菜品
bool CDishManager::addDish(int menuID, char* menuName, double price, int num) 
{
    // 1.检查ID是否已存在
    if(getDishByID(menuID) != NULL) 
	{
        printf("菜品ID %d 已存在！\n", menuID);
        return false;
    }
    
    //  创建新菜品
    DISH newDish;
    newDish.menuID = menuID;
    strcpy(newDish.menuName, menuName);
    newDish.price = price;
    newDish.num = num;
    
    // 添加到vector
    dishes.push_back(newDish);
    
    // 返回成功
    printf("添加菜品成功: %s\n", menuName);
    return true;
    
} 

// 删除菜品（根据索引）
bool CDishManager::deleteDishByIndex(int index) 
{
	// 1.索引是否合法
	if(index < 0 || index >= dishes.size())
	{
		return false;	
	} 
	
	// 2.删除元素
	// begin位置为0 
	dishes.erase(dishes.begin() + index);
	
	// 3.返回成功
	printf("删除菜品成功!\n");
	return true; 
}


// 修改菜品
bool CDishManager::updateDish(int index, DISH* newDish) 
{
	// 检查索引是否合法
    if(index < 0 || index >= dishes.size())
    {
    	return false;
	}     
    
    
    // 更新数据  解引用 将指针指向的东西（菜品数据）复制过来 
    dishes[index] = *newDish;
    
    
    // 返回成功
    printf("修改菜品成功\n");
    return true;
}
