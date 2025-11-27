#ifndef CUSERMANAGER_H
#define CUSERMANAGER_H

#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std; 
/// 用户结构体
/// 存储单个用户的信息
typedef struct {
    char account[20];   // 账号
    char password[20];  // 密码
    int role;           // 角色: 1=管理员, 2=经理, 3=服务员
} USER;

/// CUserManager 类
/// 用户管理器,使用单例模式
/// 功能:
///   - 管理所有用户数据 (注册、登录、查找)
///   - 全局只有一个实例,所有窗口共享
/// 使用方式:
///   CUserManager* mgr = CUserManager::getInstance();
///   mgr->registerUser("admin", "123", 1);
///   int role = mgr->verifyUser("admin", "123");
class CUserManager {
private:
   
    /// 静态实例指针
    /// 存储唯一的 CUserManager 实例
    /// 所有对象共享这个指针
    static CUserManager* instance;
    
    /// 用户数组
    /// 存储所有用户信息
//    USER users[100];
	vector<USER> users;
    
    /// 私有构造函数
    /// 防止外部创建对象
    /// 功能: 初始化用户数据
    CUserManager();
    
    /// 私有析构函数
    ~CUserManager();

public:
    
    /// 获取单例实例
    /// 返回值: CUserManager 的唯一实例
    /// 功能: 
    ///   - 如果实例不存在,创建新实例
    ///   - 如果实例已存在,返回现有实例
    static CUserManager* getInstance();
    
    /// 销毁单例实例
    /// 功能: 释放单例对象的内存
    static void destroyInstance();
    
    /// 验证用户登录
    /// 参数:
    ///   account - 用户输入的账号
    ///   password - 用户输入的密码
    /// 返回值:
    ///   -1: 用户不存在或密码错误
    ///   1: 管理员
    ///   2: 经理
    ///   3: 服务员
    int verifyUser(char* account, char* password);
    
    /// 注册新用户
    /// 参数:
    ///   account - 新用户的账号
    ///   password - 新用户的密码
    ///   role - 新用户的角色 (1=管理员, 2=经理, 3=服务员)
    /// 返回值:
    ///   true: 注册成功
    ///   false: 注册失败 (账号已存在)
    bool registerUser(char* account, char* password, int role);
    
    /// 检查账号是否存在
    /// 参数:
    ///   account - 要检查的账号
    /// 返回值:
    ///   true: 账号已存在
    ///   false: 账号不存在
    bool checkAccount(char* account);
    
    int getUserCount();  // 返回用户管理器内的总人数 
	
	USER* getUserByIndex(int index);  // 获取用户索引 
};

#endif
