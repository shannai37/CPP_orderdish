#ifndef CDISHMANAGER_H
#define CDISHMANAGER_H

#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;

// 菜品结构体
typedef struct {
    int menuID;
    char menuName[20];
    double price;
    int num;
}DISH;

class CDishManager {
private:
    vector<DISH> dishes;
    
    // 1.私有构造函数
    CDishManager();
    
    // 私有析构函数
    ~CDishManager();
	
	 // 2.静态单例指针
    static CDishManager* instance;
public:
   	
   	// 3.获取单例实例 
    static CDishManager* getInstance(); 
    
    // 销毁单例实例 （释放单例内存） 
    static void destroyInstance();
    
  
  	// 访问方法 getter 
    
    // 获取菜品数量
    int getDishCount(); 
    
    // 根据索引获取菜品
    // 使用指针DISH*（8Byte） 比使用结构体DISH（32字节） 占用内存更小 
    // 使用指针可以修改原数据 
    DISH* getDishByIndex(int index); 
    
    
    // 根据菜品ID查找
    DISH* getDishByID(int menuID);
    
    // setter
    
    // 添加菜品
    // bool -> 看有没有重复名字的菜 
    bool addDish(int menuID, char* menuName, double price, int num);
    
    // 删除菜品（根据索引）
    bool deleteDishByIndex(int index); 
    
    // 修改菜品
    bool updateDish(int index,DISH* newDish);
    
};

#endif
