# C++点菜系统面向对象重构学习总结

> 本文档记录了从C风格代码重构到C++面向对象设计的完整学习过程，包括单例模式的应用、继承体系的设计，以及在实践中遇到的各种问题和解决方案。

---

## 一、项目概述

### 1.1 项目背景

这是一个**餐厅点菜系统**的重构项目，目标是将原有的C风格代码（使用结构体和函数）改造为C++面向对象设计（使用类和继承）。

### 1.2 架构设计

整个系统采用两层继承体系：

**控件类继承体系：**
```
CControl (基类)
├── CLabel (标签)
├── CEdit (编辑框)
└── CButton (按钮)
```
- CControl定义了所有控件的通用属性（坐标、尺寸、内容）
- 每个子类实现自己特有的显示逻辑（纯虚函数`showControl()`）

**窗口类继承体系：**
```
CWindow (基类)
├── CInitWin (初始窗口)
├── CLoginWin (登录窗口)
├── CRegisterWin (注册窗口)
├── CAdminWin (管理员窗口)
├── CManagerWin (经理窗口)
└── CWaiterWin (服务员窗口)
```
- CWindow提供窗口管理的通用功能（显示边框、添加控件、处理输入）
- 每个子类实现自己的业务逻辑（纯虚函数`handle()`）

### 1.3 从C到C++的转变

**C风格（旧版）：**
- 使用`typedef struct`定义数据结构
- 使用普通函数操作数据
- 全局变量管理状态

**C++风格（新版）：**
- 使用`class`封装数据和行为
- 使用继承和多态实现代码复用
- 使用单例模式管理共享数据

---

## 二、核心新知识：单例模式

### 2.1 为什么需要单例模式？

**问题场景：**

在重构过程中，遇到了一个关键问题：**不同窗口之间如何共享用户数据？**

- 用户在**注册窗口**注册了账号
- 切换到**登录窗口**时需要验证这个账号
- 如果每个窗口都创建自己的用户管理器对象，数据无法共享

**错误的做法：**
```cpp
// 注册窗口中
CUserManager* mgr1 = new CUserManager();
mgr1->registerUser("admin", "123", 1);  // 注册用户

// 登录窗口中
CUserManager* mgr2 = new CUserManager();
mgr2->verifyUser("admin", "123");  // ❌ 找不到用户！
```

问题：`mgr1`和`mgr2`是两个独立的对象，数据不共享。

**单例模式的解决方案：**

确保整个程序中只有**一个**`CUserManager`实例，所有窗口都使用这同一个实例。

```cpp
// 注册窗口中
CUserManager* mgr1 = CUserManager::getInstance();  // 获取唯一实例
mgr1->registerUser("admin", "123", 1);

// 登录窗口中
CUserManager* mgr2 = CUserManager::getInstance();  // 获取同一个实例
mgr2->verifyUser("admin", "123");  // ✅ 可以找到用户！
```

### 2.2 单例模式的三要素

#### 要素1：私有构造函数

**作用：** 防止外部直接创建对象。

```cpp
class CUserManager {
private:
    CUserManager() {  // 构造函数设为private
        userCount = 0;
        // 初始化工作...
    }
};

// 外部无法这样创建对象：
// CUserManager* mgr = new CUserManager();  // ❌ 编译错误
```

#### 要素2：静态实例指针

**作用：** 存储唯一的实例。

```cpp
class CUserManager {
private:
    static CUserManager* instance;  // 静态成员，所有对象共享
};

// 在.cpp中初始化
CUserManager* CUserManager::instance = NULL;
```

#### 要素3：静态getInstance()方法

**作用：** 提供全局访问点，第一次调用时创建实例。

```cpp
class CUserManager {
public:
    static CUserManager* getInstance() {
        if(instance == NULL) {  // 如果还没创建
            instance = new CUserManager();  // 创建唯一实例
        }
        return instance;  // 返回唯一实例
    }
};
```

**完整的单例类结构：**

```cpp
// CUserManager.h
class CUserManager {
private:
    static CUserManager* instance;  // ②静态实例指针
    USER users[100];
    int userCount;
    
    CUserManager();  // ①私有构造函数
    
public:
    static CUserManager* getInstance();  // ③静态获取方法
    static void destroyInstance();
    
    int verifyUser(char* account, char* password);
    bool registerUser(char* account, char* password, int role);
    bool checkAccount(char* account);
};
```

#### 三要素协同工作流程

**第一次调用 `getInstance()`：**

```cpp
CUserManager* mgr1 = CUserManager::getInstance();
// 执行流程：
// 1. 检查 instance == NULL？ → 是（还没创建）
// 2. 执行 instance = new CUserManager() → 调用私有构造函数
// 3. 返回 instance 的地址 → mgr1 得到这个地址
```

**第二次调用 `getInstance()`：**

```cpp
CUserManager* mgr2 = CUserManager::getInstance();
// 执行流程：
// 1. 检查 instance == NULL？ → 否（已经有对象了）
// 2. 跳过创建步骤
// 3. 直接返回 instance → mgr2 得到相同的地址
// 结果：mgr1 == mgr2 （指向同一个对象！）
```

**关键问题解答：**

**Q: 为什么 `instance` 必须是 `static`？**

因为`static`成员属于**类本身**，不属于某个对象，全局只有一份。

```cpp
// 如果不是static
class Test {
    Test* instance;  // 每个对象有自己的instance
};
Test* t1 = new Test();  // t1.instance
Test* t2 = new Test();  // t2.instance（不同的！）

// 如果是static
class Test {
    static Test* instance;  // 全局只有一个instance
};
// 所有地方访问的都是同一个instance
```

**Q: 为什么 `getInstance()` 必须是 `static`？**

因为要在**没有对象**的情况下调用。

```cpp
// 如果不是static，就会陷入死循环：
CUserManager* temp = ???;        // 怎么创建？构造函数是私有的！
temp->getInstance();              // 需要对象才能调用

// 是static，可以直接通过类名调用：
CUserManager::getInstance();     // ✅ 不需要对象
```

### 2.3 拷贝构造函数禁用

**问题：** 即使构造函数是私有的，编译器仍会生成默认的拷贝构造函数，可能导致单例被复制。

**解决方案：** 将拷贝构造函数声明为私有（或C++11中用`= delete`）。

```cpp
class CUserManager {
private:
    // 禁止拷贝
    CUserManager(const CUserManager&);  // 只声明不实现
    CUserManager& operator=(const CUserManager&);
};
```

**是否必需？**
- 对于初学者，这不是必需的（因为通常不会主动去复制单例对象）
- 但这是**最佳实践**，可以防止意外的复制行为
- 如果为了简化代码，可以省略，不会影响基本功能

### 2.4 单例模式的实际应用

在本项目中，`CUserManager`作为单例，提供了三个核心方法：

1. **`verifyUser(account, password)`** - 登录验证，返回用户角色
2. **`registerUser(account, password, role)`** - 注册新用户
3. **`checkAccount(account)`** - 检查账号是否已存在

所有窗口通过`getInstance()`获取同一个管理器实例，实现了数据共享。

---

## 三、C++面向对象知识回顾

### 3.1 继承与多态

**为什么使用继承？**

继承的核心价值在于**避免重复代码**。以窗口类为例：

所有窗口都需要：
- 绘制边框
- 添加控件
- 处理键盘输入

但每个窗口的**业务逻辑**不同：
- 登录窗口：验证用户名密码
- 注册窗口：保存新用户
- 管理员窗口：管理菜品和订单

**设计方案：**
- 把**通用功能**放在基类`CWindow`中
- 把**特定逻辑**通过纯虚函数让子类实现

```cpp
class CWindow {
protected:
    int winX, winY, winWidth, winHeight;
    CControl* arr[20];
    int count;
    
public:
    void show();     // 通用：显示边框和控件
    void run();      // 通用：处理键盘输入
    void addControl(CControl* con);  // 通用：添加控件
    
    virtual void handle() = 0;  // 纯虚函数：每个窗口不同
};
```

### 3.2 初始化列表的使用

**什么是初始化列表？**

在构造函数中，用冒号`:`调用父类构造函数或初始化成员变量。

```cpp
CLoginWin::CLoginWin() 
    : CWindow(15, 5, 50, 15)  // 初始化列表，调用父类构造
{
    // 构造函数体
    CLabel* lab1 = new CLabel(...);
    this->addControl(lab1);
}
```

**为什么必须用初始化列表调用父类构造？**

因为对象的构造顺序是：**先构造父类，再构造子类**。

**错误写法：**
```cpp
CLoginWin::CLoginWin() {
    // ❌ 没有调用父类构造函数
    // 父类的winX, winY等成员变量未初始化，值是垃圾值
}
```

**正确写法：**
```cpp
CLoginWin::CLoginWin() 
    : CWindow(15, 5, 50, 15)  // ✅ 先初始化父类
{
    // 然后初始化子类特有的内容
}
```

**初始化列表 vs 赋值语句：**

```cpp
// 方式1：初始化列表（推荐）
CWindow::CWindow(int x, int y, int w, int h)
    : winX(x), winY(y), winWidth(w), winHeight(h)  // 直接初始化
{
}

// 方式2：赋值语句（低效）
CWindow::CWindow(int x, int y, int w, int h) {
    winX = x;      // 先默认初始化，再赋值
    winY = y;
    winWidth = w;
    winHeight = h;
}
```

初始化列表更高效，对于const成员和引用成员是唯一选择。

### 3.3 虚函数与纯虚函数

**关键认识：逻辑不同才需要虚函数**

这是一个重要的理解转折点。最初的误解是"逻辑相同才要虚函数"，实际上恰恰相反。

**场景1：逻辑相同 → 不需要虚函数**

所有窗口显示边框的逻辑都一样（画`┌─┐ │ │ └─┘`），只是坐标和尺寸不同。

```cpp
class CWindow {
public:
    void show() {  // 普通函数，不是虚函数
        CTool::printBoarder(winX, winY, winWidth, winHeight);
        // 显示所有控件...
    }
};
```

**场景2：逻辑不同 → 需要虚函数**

每个窗口处理按钮点击的逻辑完全不同：

```cpp
class CWindow {
public:
    virtual void handle() = 0;  // 纯虚函数
};

class CLoginWin : public CWindow {
public:
    void handle() {
        // 登录窗口的逻辑：验证用户名密码
        if(flag == 4) {  // 确定按钮
            int role = userMgr->verifyUser(...);
            // 根据角色跳转...
        }
    }
};

class CRegisterWin : public CWindow {
public:
    void handle() {
        // 注册窗口的逻辑：保存新用户
        if(flag == 9) {  // 注册按钮
            bool success = userMgr->registerUser(...);
            // 显示注册结果...
        }
    }
};
```

**纯虚函数的作用：**
- 强制子类必须实现这个方法
- 基类无法给出具体实现（因为每个子类的逻辑不同）
- 实现多态：通过父类指针调用子类的方法

### 3.4 继承中的成员变量管理

**为什么父类成员用`protected`？**

```cpp
class CControl {
protected:  // 子类可以访问
    int x, y;
    int width, height;
    char context[20];
};
```

- `private`：只有本类能访问，子类也不能访问
- `protected`：本类和子类都能访问，外部不能访问
- `public`：所有人都能访问

使用`protected`让子类可以直接访问这些属性：

```cpp
class CLabel : public CControl {
public:
    void showControl() {
        CTool::gotoxy(x, y);  // 直接使用父类的x, y
        printf("%s", context);
    }
};
```

**子类不能重复定义父类成员**

这是最容易犯的严重错误，详见下一章节。

---

## 四、遇到的问题与解决方案

### 问题1：子类重复定义父类成员变量 ⭐⭐⭐

**问题描述：**

在`CEdit.h`和`CLabel.h`中，重复定义了父类`CControl`中已有的成员变量。

**错误代码：**

```cpp
// CControl.h (父类)
class CControl {
protected:
    int x, y;
    int width, height;
    char context[20];
};

// CEdit.h (子类) - ❌ 错误
class CEdit : public CControl {
private:
    int x, y;           // ❌ 重复定义
    int width, height;  // ❌ 重复定义
    char context[20];   // ❌ 重复定义
    // 特有成员
    int maxLen;
    int inputType;
};
```

**为什么会导致问题？**

1. 子类的私有成员会**隐藏**父类的同名成员
2. 构造函数初始化的是**父类的变量**
3. `showControl()`访问的是**子类的变量**（未初始化，值是垃圾值）
4. 结果：控件画在了错误的位置，导致不显示

**具体表现：**
- 编辑框无法显示
- 即使设置了正确的坐标，控件也不出现在预期位置
- 标签可以显示（因为代码中手动赋值了子类变量）

**正确代码：**

```cpp
// CEdit.h - ✅ 正确
class CEdit : public CControl {
private:
    // 不重复定义x, y等，直接使用父类的
    
    // 只定义子类特有的成员
    int maxLen;
    int inputType;
    int ips;
};
```

**核心知识点：**

继承的本质是**复用父类成员**，而不是重新定义。子类自动拥有父类的所有`protected`和`public`成员。

### 问题2：中文乱码导致无法查看代码

**问题描述：**

编辑器显示中文注释为乱码，无法阅读代码。

**原因：**

编码不匹配（源文件可能是GBK，编辑器按UTF-8解析）。

**解决方案：**

请求提供完整的文件内容（从第1行到最后一行），然后重新复制到编辑器中。

**涉及的文件：**
- CUserManager.h
- CUserManager.cpp
- CLoginWin.cpp
- CRegisterWin.cpp
- main.cpp

### 问题3：数据存储方案选择

**两种方案对比：**

| 对比项 | 方案A：内存存储 | 方案B：文件持久化 |
|--------|----------------|------------------|
| **实现难度** | 简单 | 需要文件操作代码 |
| **数据持久性** | 程序关闭后丢失 | 程序关闭后保留 |
| **初始用户** | 硬编码在构造函数中 | 从文件加载 |
| **适用场景** | 学习、测试 | 实际应用 |

**最终选择：方案A（内存存储）**

原因：
- 作业要求相对简单，重点是学习面向对象设计
- 避免文件操作代码干扰对单例模式的理解
- 在构造函数中初始化3个默认用户（admin、manager、waiter）

**实现方式：**

```cpp
CUserManager::CUserManager() {
    userCount = 0;
    
    // 初始化3个默认用户
    strcpy(users[0].account, "admin");
    strcpy(users[0].password, "123456");
    users[0].role = 1;
    
    strcpy(users[1].account, "manager");
    strcpy(users[1].password, "123456");
    users[1].role = 2;
    
    strcpy(users[2].account, "waiter");
    strcpy(users[2].password, "123456");
    users[2].role = 3;
    
    userCount = 3;
}
```

### 问题4：函数命名修改

**问题描述：**

函数名`accountExists`不够直观，改为`checkAccount`更符合习惯。

**修改内容：**

```cpp
// CUserManager.h
class CUserManager {
public:
    // bool accountExists(char* account);  // ❌ 旧名称
    bool checkAccount(char* account);      // ✅ 新名称
};

// CUserManager.cpp
bool CUserManager::checkAccount(char* account) {
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].account, account) == 0) {
            return true;
        }
    }
    return false;
}

// 调用处也要修改
bool CUserManager::registerUser(char* account, char* password, int role) {
    if(checkAccount(account)) {  // 使用新名称
        return false;
    }
    // ...
}
```

**知识点：** 函数命名应该清晰表达意图，动词+名词的形式更易理解。

### 问题5：代码风格统一问题

**问题描述：**

`CRegisterWin`和`CLoginWin`的实现方式不一致。

**CLoginWin的实现（推荐）：**

```cpp
CLoginWin::CLoginWin() 
    : CWindow(15, 5, 50, 15)  // 初始化列表
{
    CLabel* lab1 = new CLabel(...);
    this->addControl(lab1);  // 使用addControl()
    
    CEdit* edit1 = new CEdit(...);
    this->addControl(edit1);
}
```

**如果手动管理数组（不推荐）：**

```cpp
CLoginWin::CLoginWin() {
    this->arr[0] = new CLabel(...);
    this->arr[1] = new CEdit(...);
    this->count = 2;  // 手动维护计数
}
```

**为什么使用`addControl()`？**

1. **封装性**：隐藏了数组管理的细节
2. **安全性**：`addControl()`内部会检查数组是否越界
3. **一致性**：所有窗口使用相同的方式添加控件
4. **可维护性**：如果以后改变存储方式，只需修改`addControl()`

**`addControl()`的实现：**

```cpp
void CWindow::addControl(CControl* con) {
    if(count < 20) {
        arr[count] = con;
        count++;
    }
}
```

### 问题6：初始化列表调用父类构造的必要性

**问题描述：**

为什么必须用`: CWindow(x, y, width, height)`这种形式？

**原因：**

C++对象的构造顺序是固定的：
1. 先构造父类部分
2. 再构造子类部分

如果不显式调用父类构造函数，编译器会调用父类的**无参构造函数**。

**场景分析：**

```cpp
// 如果CWindow只有有参构造函数
class CWindow {
public:
    CWindow(int x, int y, int w, int h);  // 只有这个
};

// 子类必须调用它
CLoginWin::CLoginWin() 
    : CWindow(15, 5, 50, 15)  // ✅ 必须显式调用
{
}

// 如果不调用
CLoginWin::CLoginWin() {  // ❌ 编译错误
    // 编译器尝试调用CWindow()，但找不到无参构造
}
```

**优势：**
- 确保父类成员被正确初始化
- 效率更高（直接初始化，而非默认初始化+赋值）
- 对于const成员和引用成员，这是唯一方式

### 问题7：何时需要重写`show()`和`run()`

**问题描述：**

`CRegisterWin`重写了`show()`方法，而`CLoginWin`没有重写，为什么？

**`CRegisterWin`的特殊需求：**

```cpp
void CRegisterWin::show() {
    CWindow::show();  // 先调用父类的show()
    
    // 额外显示角色说明
    CTool::gotoxy(30, 20);
    printf("角色说明: 1=管理员, 2=经理, 3=服务员");
}
```

注册窗口需要在标准界面基础上，**额外显示**角色说明信息。

**`CLoginWin`不需要重写：**

登录窗口的显示逻辑和父类完全一样，直接用父类的`show()`即可。

**决策规则：**

- 如果子类需要**额外功能**：重写方法，内部调用`父类::方法()`，然后添加额外代码
- 如果子类逻辑和父类**完全相同**：不重写，直接使用父类方法
- 如果子类需要**完全不同的逻辑**：重写方法，不调用父类方法

### 问题8：窗口大小和控件位置调整

**问题描述：**

控件重叠或位置不合理。

**调试方法：**

1. **理解坐标系统**：
   - 左上角是(0, 0)
   - X轴向右增加
   - Y轴向下增加

2. **计算控件占用空间**：
   ```cpp
   CEdit* edit1 = new CEdit(EDIT, 32, 8, 25, 3, ...);
   // 起点：(32, 8)
   // 宽度：25，占据X: 32-57
   // 高度：3，占据Y: 8-10
   ```

3. **避免重叠**：
   - 两个控件的Y坐标至少相差控件高度+1
   - 例如：第一个控件y=8, height=3，第二个控件y至少应为12

4. **对齐标签和编辑框**：
   ```cpp
   // 标签在左边
   CLabel* lab1 = new CLabel(Label, 20, 8, 0, 0, "用户名:");
   // 编辑框在右边，Y坐标相同
   CEdit* edit1 = new CEdit(EDIT, 32, 8, 25, 3, ...);
   ```

---

## 五、系统运行流程串联

### 5.1 程序启动流程

```cpp
int main() {
    // 1. 初始化单例（第一次调用getInstance）
    CUserManager* userMgr = CUserManager::getInstance();
    
    // 2. 创建并显示初始窗口
    CInitWin* initWin = new CInitWin();
    initWin->show();
    initWin->run();
    initWin->handle();
    
    // 3. 清理资源
    delete initWin;
    CUserManager::destroyInstance();
    
    return 0;
}
```

### 5.2 单例如何串联不同窗口

**核心机制：** 所有窗口都通过`getInstance()`获取同一个管理器实例。

**场景：用户注册流程**

```cpp
// 步骤1：在注册窗口中注册
void CRegisterWin::handle() {
    if(flag == 9) {  // 注册按钮
        char* account = arr[2]->getContext();
        char* password = arr[4]->getContext();
        
        // 获取单例实例
        CUserManager* mgr = CUserManager::getInstance();
        
        // 注册用户（数据保存在单例中）
        bool success = mgr->registerUser(account, password, role);
    }
}

// 步骤2：切换到登录窗口
// 创建登录窗口对象
CLoginWin* loginWin = new CLoginWin();
loginWin->show();

// 步骤3：在登录窗口中验证
void CLoginWin::handle() {
    if(flag == 4) {  // 确定按钮
        char* username = arr[1]->getContext();
        char* password = arr[3]->getContext();
        
        // 获取同一个单例实例
        CUserManager* mgr = CUserManager::getInstance();
        
        // 验证用户（可以找到刚才注册的用户！）
        int role = mgr->verifyUser(username, password);
    }
}
```

**关键点：**
- 两个窗口调用的`getInstance()`返回的是**同一个对象**
- 第一次调用时创建实例，之后的调用直接返回已创建的实例
- 所有用户数据都存储在这个唯一的实例中

### 5.3 登录验证流程

```
用户输入 → CLoginWin捕获输入 → 验证逻辑
                                    ↓
                           CUserManager::verifyUser()
                                    ↓
                         遍历users数组查找匹配
                                    ↓
                    返回角色(1/2/3)或-1(失败)
                                    ↓
            CLoginWin根据角色创建对应的窗口
                                    ↓
        角色1 → CAdminWin (管理员窗口)
        角色2 → CManagerWin (经理窗口)
        角色3 → CWaiterWin (服务员窗口)
```

**关键代码片段：**

```cpp
void CLoginWin::handle() {
    if(flag == 4) {  // 确定按钮
        int role = userMgr->verifyUser(username, password);
        
        if(role == 1) {
            CAdminWin* win = new CAdminWin();
            win->show();
            win->run();
            win->handle();
            delete win;
        }
        // 其他角色类似...
    }
}
```

### 5.4 注册用户流程

```
用户填写信息 → CRegisterWin捕获输入 → 验证逻辑
                                        ↓
                            检查账号、密码、角色有效性
                                        ↓
                            CUserManager::registerUser()
                                        ↓
                                checkAccount() 检查重复
                                        ↓
                        将用户添加到users数组，userCount++
                                        ↓
                            返回成功/失败
                                        ↓
                        CRegisterWin显示结果提示
```

**关键代码片段：**

```cpp
void CRegisterWin::handle() {
    if(flag == 9) {  // 注册按钮
        // 验证输入
        if(strlen(account) == 0) { return; }
        if(strcmp(password, repassword) != 0) { return; }
        if(role < 1 || role > 3) { return; }
        
        // 调用单例注册
        bool success = userMgr->registerUser(account, password, role);
        
        // 显示结果
        if(success) {
            printf("注册成功!\n");
        }
    }
}
```

### 5.5 窗口切换机制

**窗口切换通过`handle()`方法实现：**

```cpp
// 当前窗口的handle()中
void CLoginWin::handle() {
    if(flag == 5) {  // 取消按钮
        system("cls");
        
        // 创建新窗口
        CInitWin* initWin = new CInitWin();
        initWin->show();
        initWin->run();
        initWin->handle();
        
        // 清理新窗口
        delete initWin;
    }
    // 当前窗口的handle()结束后，返回到调用处
    // 调用处会delete当前窗口对象
}
```

**窗口生命周期：**
1. 创建窗口对象（`new`）
2. 显示窗口（`show()`）
3. 运行窗口（`run()` - 处理键盘输入）
4. 处理业务（`handle()` - 可能创建新窗口）
5. 销毁窗口（`delete`）

---

## 六、学习收获与最佳实践

### 6.1 单例模式的实际应用价值

**核心价值：** 全局唯一实例 + 全局访问点

**适用场景：**
- 需要全局共享的数据管理器（如用户管理器、配置管理器）
- 资源管理器（如数据库连接池、日志记录器）
- 系统级服务（如窗口管理器）

**实现要点：**
- 私有构造函数防止外部创建
- 静态实例指针存储唯一对象
- 静态方法提供全局访问
- 首次调用时延迟创建（懒汉模式）

### 6.2 初始化列表的重要性

**必须使用的场景：**
1. 调用父类的有参构造函数
2. 初始化const成员变量
3. 初始化引用成员

**推荐使用的场景：**
- 所有成员变量的初始化（效率更高）

**语法格式：**
```cpp
Constructor(params) 
    : member1(value1), member2(value2), BaseClass(args)
{
    // 构造函数体
}
```

### 6.3 继承的正确使用方式

**原则1：子类不重复定义父类成员**

父类的`protected`成员，子类可以直接使用，无需重新定义。

**原则2：合理使用虚函数**

- 逻辑不同的方法 → 声明为虚函数或纯虚函数
- 逻辑相同的方法 → 普通方法，子类直接复用

**原则3：构造函数中调用父类构造**

使用初始化列表确保父类被正确初始化。

**原则4：基类指针实现多态**

```cpp
CWindow* windows[10];
windows[0] = new CLoginWin();
windows[1] = new CRegisterWin();

// 多态调用
for(int i = 0; i < 2; i++) {
    windows[i]->handle();  // 调用各自的实现
}
```

### 6.4 代码风格统一的必要性

**一致性原则：**

同一个项目中，相似的代码应该用相似的方式实现。

**具体体现：**
- 所有窗口都用`addControl()`添加控件
- 所有窗口都用初始化列表调用父类构造
- 所有窗口的构造函数结构相似

**好处：**
- 代码易读易懂
- 降低出错概率
- 便于团队协作

### 6.5 充分利用继承避免重复代码

**Don't Repeat Yourself (DRY) 原则**

**反例：每个窗口都实现自己的show()**

```cpp
void CLoginWin::show() {
    CTool::printBoarder(15, 5, 50, 15);
    for(int i = 0; i < count; i++) {
        arr[i]->showControl();
    }
}

void CRegisterWin::show() {
    CTool::printBoarder(10, 3, 60, 25);  // 重复代码
    for(int i = 0; i < count; i++) {      // 重复代码
        arr[i]->showControl();
    }
}
```

**正例：在父类中实现，子类直接复用**

```cpp
// CWindow基类
void CWindow::show() {
    CTool::printBoarder(winX, winY, winWidth, winHeight);
    for(int i = 0; i < count; i++) {
        arr[i]->showControl();
    }
}

// 子类直接继承使用，无需重写
```

**思考方式：**
- 先思考"这个功能在所有子类中是否相同"
- 如果相同 → 放在基类中实现
- 如果不同 → 声明为虚函数，让子类各自实现

---

## 七、常见错误速查表

### 编译时错误

| 错误现象 | 可能原因 | 快速检查 | 解决方案 |
|---------|---------|---------|---------|
| `no matching function for call to 'CWindow::CWindow()'` | 子类构造函数未调用父类构造 | 检查是否有初始化列表 | 添加`: CWindow(x,y,w,h)` |
| `'member' is private within this context` | 访问了父类的private成员 | 检查父类成员访问修饰符 | 改为protected |
| `cannot declare variable to be of abstract type` | 尝试创建含有纯虚函数的对象 | 检查是否实现了所有纯虚函数 | 实现`handle()`等纯虚函数 |
| `redefinition of 'class'` | 头文件重复包含 | 检查是否有头文件保护 | 添加`#ifndef` `#define` `#endif` |

### 运行时错误

| 错误现象 | 可能原因 | 快速检查 | 解决方案 |
|---------|---------|---------|---------|
| 控件不显示 | 子类重复定义了父类成员 | 检查子类是否有x,y等成员 | 删除子类中的重复定义 |
| 控件位置错误 | 坐标值未初始化（垃圾值） | 检查构造函数是否初始化 | 使用初始化列表 |
| 数据无法共享 | 每个窗口创建了独立对象 | 检查是否使用单例模式 | 改用`getInstance()` |
| 程序崩溃 | 空指针访问 | 检查指针是否为NULL | 添加`if(ptr != NULL)`检查 |

### 逻辑错误

| 错误现象 | 可能原因 | 快速检查 | 解决方案 |
|---------|---------|---------|---------|
| 注册的用户无法登录 | 使用了不同的管理器实例 | 确认是否用单例 | 统一使用单例 |
| 窗口切换后程序结束 | `handle()`中没有创建新窗口 | 检查按钮处理逻辑 | 添加窗口切换代码 |
| 输入无法显示 | 编辑框未实现输入处理 | 检查`CEdit`的实现 | 实现输入处理方法 |

### 设计检查清单

**使用单例模式时：**
- [ ] 构造函数是private的吗？
- [ ] 声明了`static Type* instance`吗？
- [ ] 实现了`static getInstance()`吗？
- [ ] 在.cpp中初始化`instance = NULL`了吗？

**编写子类时：**
- [ ] 构造函数中调用了父类构造（初始化列表）吗？
- [ ] 子类没有重复定义父类成员吗？
- [ ] 实现了所有纯虚函数吗？
- [ ] 需要重写的方法才重写了吗？

**添加控件时：**
- [ ] 使用`addControl()`而非手动管理数组吗？
- [ ] 控件坐标没有重叠吗？
- [ ] 控件在窗口范围内吗？

**代码风格：**
- [ ] 相似的代码使用相似的实现方式吗？
- [ ] 能复用的代码没有重复编写吗？
- [ ] 命名清晰表达了意图吗？

---

## 总结

这次C++点菜系统的重构学习，核心收获有三点：

1. **单例模式**：解决了窗口间数据共享的问题，理解了"全局唯一实例"的设计思想

2. **继承体系**：通过合理的继承设计，避免了大量重复代码，提高了可维护性

3. **初始化列表**：掌握了正确初始化父类和成员变量的方法，避免了许多隐蔽的bug

最重要的是，通过实际遇到的问题（特别是子类重复定义父类成员这个严重错误），深刻理解了C++继承机制的本质：**子类自动拥有父类的成员，无需重新定义，直接使用即可**。

这些经验将在后续开发其他面向对象项目时持续发挥作用。

---

*文档创建时间：2025年11月*

