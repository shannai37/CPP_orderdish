#include "CUserManager.h"

/// 初始化静态成员变量
/// 必须在类外初始化静态成员
/// 初始值为 NULL,表示还没有创建实例
CUserManager* CUserManager::instance = NULL;

/// 私有构造函数
/// 功能: 初始化用户数据
CUserManager::CUserManager() {
	// 初始化三个身份数据 
   	USER admin = {"admin","123456",1};
   	users.push_back(admin);
   	
   	USER manager = {"manager","123456",1};
   	users.push_back(manager);
   	
   	USER waiter = {"waiter","123456",1};
   	users.push_back(waiter);
    
	printf("CUserManager 用户管理器实例已创建\n");
    printf("CUserManager 已加载 %d 个测试用户\n", users.size());
}

/// 私有析构函数
CUserManager::~CUserManager() 
{
    printf("CUserManager 用户管理器实例已销毁\n");
}

/// 获取单例实例
/// 返回值: CUserManager 的唯一实例
/// 功能:
///   - 第1次调用: 创建新实例
///   - 后续调用: 返回已有实例
CUserManager* CUserManager::getInstance() {
    // 检查实例是否已创建
    if(instance == NULL) {
        // 实例不存在,创建新实例
        instance = new CUserManager();
    }
    
    // 返回唯一实例
    return instance;
}

/// 销毁单例实例
/// 功能: 释放单例对象的内存
void CUserManager::destroyInstance() {
    if(instance != NULL) {
        // 释放实例内存 (会调用析构函数)
        delete instance;
        
        // 指针置空,防止悬空指针
        instance = NULL;
    }
}

/// 验证用户登录
/// 参数:
///   account - 用户输入的账号
///   password - 用户输入的密码
/// 返回值:
///   -1: 用户不存在或密码错误
///   1: 管理员
///   2: 经理
///   3: 服务员
int CUserManager::verifyUser(char* account, char* password) {
    // 遍历用户数组
    for(int i = 0; i < users.size(); i++) {
        // 检查账号和密码是否匹配
        if(strcmp(users[i].account, account) == 0 && 
           strcmp(users[i].password, password) == 0) {
            // 匹配成功,返回角色
            printf("登录 用户 %s 登录成功,角色: %d\n", account, users[i].role);
            return users[i].role;
        }
    }
    
    // 没有找到匹配的用户
    printf("登录 用户 %s 登录失败\n", account);
    return -1;
}

/// 注册新用户
/// 参数:
///   account - 新用户的账号
///   password - 新用户的密码
///   role - 新用户的角色
/// 返回值:
///   true: 注册成功
///   false: 注册失败 (账号已存在)
bool CUserManager::registerUser(char* account, char* password, int role) {
    // 1. 检查账号是否已存在
    if(checkAccount(account)) {
        printf("注册 账号 %s 已存在\n", account);
        return false;  // 账号已存在
    }
    
    // 2. 检查用户数量是否已满
    if(users.size() >= 100) {
        printf("注册 用户数量已达上限\n");
        return false;
    }
    
   // 3.创建新用户
   USER newUser;
   strcpy(newUser.account,account);
   strcpy(newUser.password,password); 
   newUser.role = role;
   users.push_back(newUser);
    
    printf("注册 用户 %s 注册成功,角色: %d\n", account, role);
    
    // 5. 注册成功
    return true;
}

/// 检查账号是否存在
/// 参数:
///   account - 要检查的账号
/// 返回值:
///   true: 账号已存在
///   false: 账号不存在
bool CUserManager::checkAccount(char* account) {
    // 遍历用户数组
    for(int i = 0; i < users.size(); i++) {
        // 检查账号是否匹配
        if(strcmp(users[i].account, account) == 0) {
            return true;  // 账号已存在
        }
    }
    
    return false;  // 账号不存在
}

// 返回用户管理器内的总人数
int CUserManager::getUserCount() 
{
    return users.size();  
}

// 获取用户索引 
USER* CUserManager::getUserByIndex(int index) 
{
    if(index < 0 || index >= users.size()) 
	{
        return NULL;
    }
    return &users[index];
}
