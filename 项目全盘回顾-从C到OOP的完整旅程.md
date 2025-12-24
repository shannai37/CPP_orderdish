# C++点菜系统 - 项目全盘回顾

## 一、项目背景与目标

### 1.1 项目是什么

一个**控制台点菜系统**，功能包括：
- 用户登录/注册（管理员、经理、服务员三种角色）
- 台桌管理（查看、开桌）
- 菜品管理（增删改查）
- 人员管理（查看用户）
- 点菜流程（选桌、选菜、下单）

### 1.2 核心任务

将老师给的 **C 风格面向过程代码**，改造成 **C++ 面向对象代码**

### 1.3 为什么要改造？

**C 风格代码的问题**：

```c
// C风格：每个窗口都要重复写类似的代码
void showLoginWin() {
    drawBorder(10, 5, 40, 15);
    gotoxy(15, 7); printf("用户名:");
    gotoxy(15, 9); printf("密码:");
    // ... 大量重复代码
}

void showRegisterWin() {
    drawBorder(10, 5, 40, 15);  // 又写一遍
    gotoxy(15, 7); printf("用户名:");  // 又写一遍
    // ...
}
```

**问题**：
- 代码重复，改一处要改多处
- 数据和函数分离，容易出错
- 难以扩展和维护

**OOP 的解决方案**：
- **封装**：数据和操作放在一起
- **继承**：公共部分放基类，子类复用
- **多态**：统一接口，不同实现

---

## 二、项目架构总览

### 2.1 三大模块

```
┌─────────────────────────────────────────────────────────┐
│                      点菜系统                            │
├─────────────────┬─────────────────┬─────────────────────┤
│   控件体系       │    窗口体系      │    数据管理体系      │
│   (UI组件)       │   (业务界面)     │    (单例模式)        │
├─────────────────┼─────────────────┼─────────────────────┤
│ CControl        │ CWindow         │ CUserManager        │
│   ├─ CLabel     │   ├─ CInitWin   │ CDishManager        │
│   ├─ CEdit      │   ├─ CLoginWin  │ CTableManager       │
│   └─ CButton    │   ├─ CAdminWin  │                     │
│                 │   ├─ ...        │                     │
│                 │   └─ COrderWin  │                     │
└─────────────────┴─────────────────┴─────────────────────┘
```

### 2.2 两棵继承树

**控件继承树**：
```
CControl (抽象基类)
    │
    ├── CLabel    标签控件（只显示文字）
    ├── CEdit     输入框控件（可输入文字）
    └── CButton   按钮控件（可点击触发）
```

**窗口继承树**：
```
CWindow (抽象基类)
    │
    ├── CInitWin         初始界面（注册/登录选择）
    ├── CLoginWin        登录界面
    ├── CRegisterWin     注册界面
    ├── CAdminWin        管理员主界面
    ├── CManagerWin      经理界面
    ├── CWaiterWin       服务员界面
    ├── CAdminWin_Table  台桌管理（带分页）
    ├── CAdminWin_DM     菜品管理（带分页）
    ├── CAdminWin_PM     人员管理（带分页）
    └── COrderWin        点菜界面（带分页）
```

### 2.3 窗口与控件的关系

```
CWindow 包含 CControl*[] 数组
    │
    │  arr[0] ──→ CLabel("用户名:")
    │  arr[1] ──→ CEdit(用户名输入框)
    │  arr[2] ──→ CLabel("密码:")
    │  arr[3] ──→ CEdit(密码输入框)
    │  arr[4] ──→ CButton("登录")
    │  arr[5] ──→ CButton("返回")
    │
    └── 窗口"包含"多个控件，这是组合关系，不是继承
```

---

## 三、C风格代码回顾（改造前）

### 3.1 C风格代码的核心结构

#### 3.1.1 数据结构：用结构体代替类

```c
// 控件结构体
typedef struct {
    int type;           // 0=Label, 1=Edit, 2=Button
    int x, y;
    int width, height;
    char context[20];
    int maxLen;         // Edit专用
    int isPassword;     // Edit专用
} CONTROL;

// 窗口结构体
typedef struct {
    int x, y;
    int width, height;
    int flag;           // 记录哪个按钮被点击
    int count;          // 控件数量
    CONTROL arr[20];    // 控件数组
} CWIN;

// 用户结构体
typedef struct {
    char account[20];
    char password[20];
    int role;
} USER;
```

#### 3.1.2 窗口函数：每个窗口是一个函数

```c
// 登录窗口函数
void CLoginWin_init() {
    // 1. 创建窗口结构体
    CWIN win = {20, 5, 60, 20, 0, 0};
    
    // 2. 创建控件
    CONTROL lab1 = {LABEL, 35, 12, 0, 0, "用户名:"};
    CONTROL edit1 = {EDIT, 45, 11, 25, 3, "", 10, 0};
    CONTROL btn1 = {BUTTON, 28, 21, 12, 3, "确定"};
    
    // 3. 添加到窗口
    addControl(&win, &lab1);
    addControl(&win, &edit1);
    addControl(&win, &btn1);
    
    // 4. 显示并运行
    printWindow(&win);
    winRun(&win);
    
    // 5. 根据flag跳转
    if(win.flag == 4) {
        // 验证登录...
        CAdminWin_init();  // 直接调用另一个窗口函数！
    }
}
```

#### 3.1.3 数据存储：全局链表 + void*

```c
// 通用链表节点（用void*存任意数据）
typedef struct node {
    void* data;           // 指向任意类型数据
    struct node* pnext;
} LIST;

// 全局变量
LIST* userList;   // 用户链表
LIST* menuList;   // 菜品链表

// 使用时需要强制类型转换
USER* user = (USER*)(node->data);
```

#### 3.1.4 窗口跳转：函数指针

```c
// 函数指针类型
typedef void (*WindowFunc)();

// 按钮配置（包含跳转目标）
typedef struct {
    char text[20];
    int x, y, width, height;
    WindowFunc jump;  // 跳转到哪个窗口函数
} ButtonConfig;

// 使用
ButtonConfig buttons[] = {
    {"注册", 32, 11, 16, 3, CRegisterWin_init},
    {"登录", 32, 16, 16, 3, CLoginWin_init},
    {"退出", 32, 21, 16, 3, NULL}
};

// 跳转函数
void jumpToWindow(WindowFunc targetWindow) {
    if(targetWindow != NULL) {
        system("cls");
        targetWindow();  // 通过函数指针调用
    } else {
        exit(0);
    }
}
```

### 3.2 C风格代码的问题分析

#### 问题1：递归调用导致栈溢出

```c
void CLoginWin_init() {
    // ...
    if(登录成功) {
        CAdminWin_init();  // 调用另一个窗口函数
    }
}

void CAdminWin_init() {
    // ...
    if(返回) {
        CLoginWin_init();  // 又调用回来！
    }
}
```

**调用栈不断增长**：
```
main()
  └── CStartWin_init()
        └── CLoginWin_init()
              └── CAdminWin_init()
                    └── CLoginWin_init()  // 返回时又调用
                          └── ...无限嵌套
```

**后果**：长时间运行后栈溢出崩溃

#### 问题2：全局变量难以管理

```c
// 全局变量散落各处
LIST* userList;   // 在某个文件定义
LIST* menuList;   // 在另一个文件定义

// 任何地方都能修改，难以追踪
void someFunction() {
    userList = NULL;  // 谁改的？什么时候改的？
}
```

#### 问题3：void* 类型不安全

```c
// 存入时
New_List_pushback(head, &user, sizeof(USER));

// 取出时必须知道是什么类型
USER* user = (USER*)(node->data);  // 如果类型错了呢？

// 编译器不会报错，运行时才崩溃
MENU* menu = (MENU*)(node->data);  // 错误！实际是USER
menu->price = 10.0;  // 内存越界，崩溃或数据损坏
```

#### 问题4：代码重复

```c
// 每个窗口都要写类似的初始化代码
void CLoginWin_init() {
    CWIN win = {20, 5, 60, 20, 0, 0};
    // 创建控件...
    printWindow(&win);
    winRun(&win);
    // 处理逻辑...
}

void CRegisterWin_init() {
    CWIN win = {20, 5, 60, 20, 0, 0};  // 又写一遍
    // 创建控件...
    printWindow(&win);  // 又写一遍
    winRun(&win);       // 又写一遍
    // 处理逻辑...
}
```

#### 问题5：手动内存管理容易出错

```c
// 创建链表节点
LIST* newNode = (LIST*)malloc(sizeof(LIST));
newNode->data = malloc(length);
memcpy(newNode->data, pdata, length);

// 删除时要记得释放两块内存
free(node->data);  // 先释放数据
free(node);        // 再释放节点
// 如果顺序反了或者漏了，就内存泄漏
```

### 3.3 C风格代码的优点（也要认识到）

| 优点 | 说明 |
|------|------|
| **直观简单** | 没有类、继承等概念，容易理解 |
| **灵活** | void* 可以存任意数据 |
| **效率高** | 没有虚函数调用开销 |
| **兼容性好** | 纯C代码可以在更多平台编译 |

**适用场景**：小型项目、嵌入式系统、对性能要求极高的场景

### 3.4 为什么要改成OOP？

| C风格问题 | OOP解决方案 |
|-----------|-------------|
| 递归调用栈溢出 | 状态机模式 |
| 全局变量难管理 | 单例模式 |
| void* 类型不安全 | 泛型/具体类型 |
| 代码重复 | 继承复用 |
| 手动内存管理 | 构造/析构函数 |
| 数据函数分离 | 封装在类中 |

---

## 四、阶段1：C风格 → OOP改造（详细）

### 4.1 设计思路：从"做什么"到"是什么"

**C 风格思维**（面向过程）：
- 思考：程序要"做什么"？
- 答案：画边框、显示文字、获取输入、处理逻辑...
- 结果：一堆函数

**OOP 思维**（面向对象）：
- 思考：系统里有"什么东西"？
- 答案：窗口、控件（标签、输入框、按钮）、用户、菜品...
- 结果：一堆类

### 4.2 控件体系设计

#### 4.2.1 为什么需要 CControl 基类？

观察三种控件的共同点：

| 属性/方法 | CLabel | CEdit | CButton |
|-----------|--------|-------|---------|
| x, y 坐标 | 有 | 有 | 有 |
| width, height | 有 | 有 | 有 |
| context 内容 | 有 | 有 | 有 |
| type 类型 | 0 | 1 | 2 |
| showControl() | 要实现 | 要实现 | 要实现 |

**共同点提取到基类**，**不同点留给子类**。

#### 4.2.2 CControl 基类设计

```cpp
// CControl.h
class CControl {
protected:  // 子类可访问，外部不可直接访问
    int type;           // 控件类型 0=Label, 1=Edit, 2=Button
    int x, y;           // 控件位置
    int width, height;  // 控件大小
    char context[20];   // 控件内容

public:
    // 构造函数
    CControl();
    CControl(int type, int x, int y, int width, int height, char* context);
    
    // 虚析构函数（重要！）
    virtual ~CControl();
    
    // 纯虚函数 - 强制子类实现
    virtual void showControl() = 0;
    
    // getter/setter 方法
    int getX();
    void setX(int x);
    // ...
};
```

**关键设计决策**：

1. **protected 成员**
   - 子类能直接访问 `x, y` 等
   - 外部只能通过 getter/setter

2. **virtual ~CControl()**
   - 虚析构函数
   - 确保 `delete 基类指针` 时能调用子类析构函数

3. **virtual void showControl() = 0**
   - 纯虚函数，`= 0` 表示没有默认实现
   - 强制每个子类必须实现自己的显示逻辑
   - 使 CControl 成为**抽象类**，不能直接实例化

#### 4.2.3 子类实现

**CLabel（标签）**：

```cpp
// CLabel.h
class CLabel : public CControl {
public:
    CLabel(int x, int y, char* text);
    ~CLabel();
    
    // 实现父类的纯虚函数
    virtual void showControl();
};

// CLabel.cpp
CLabel::CLabel(int x, int y, char* text)
    : CControl(0, x, y, strlen(text), 1, text)  // 初始化列表调用父类构造
{
    // 子类特有的初始化（如果有）
}

void CLabel::showControl() {
    CTool::gotoxy(x, y);
    printf("%s", context);  // 直接打印文字
}
```

**CEdit（输入框）**：

```cpp
// CEdit.cpp
void CEdit::showControl() {
    CTool::gotoxy(x, y);
    printf("[          ]");  // 画输入框样式
    CTool::gotoxy(x + 1, y);
    printf("%s", context);   // 显示当前内容
}
```

**CButton（按钮）**：

```cpp
// CButton.cpp
void CButton::showControl() {
    CTool::gotoxy(x, y);
    printf("[ %s ]", context);  // 画按钮样式
}
```

#### 4.2.4 多态的体现

```cpp
// 多态：用父类指针指向不同子类对象
CControl* arr[3];
arr[0] = new CLabel(10, 5, "用户名:");
arr[1] = new CEdit(20, 5, "", 10);
arr[2] = new CButton(15, 10, "登录");

// 同一个调用，执行不同的实现
for(int i = 0; i < 3; i++) {
    arr[i]->showControl();  // 自动调用正确的版本
}

// 清理
for(int i = 0; i < 3; i++) {
    delete arr[i];  // 虚析构确保正确释放
}
```

#### 4.2.5 常见疑问：抽象类不能实例化，为什么能用基类指针？

**关键区分：实例化对象 vs 声明指针**

```cpp
// 这是【实例化对象】- 抽象类不允许！
CControl obj;                  // 错误！不能创建 CControl 对象
CControl* p = new CControl();  // 错误！不能 new CControl 对象

// 这是【声明指针】- 完全可以！
CControl* p;                   // 只是声明了一个指针变量，没有创建任何对象
```

**指针只是"地址"，不是"对象"**

```cpp
CControl* p = new CLabel(10, 5, "Hello");
```

这行代码做了什么？

| 部分 | 做了什么 | 创建了什么 |
|------|----------|-----------|
| `CControl* p` | 声明一个指针变量 | 只是一个存地址的变量（4或8字节） |
| `new CLabel(...)` | 创建 CLabel 对象 | 一个完整的 CLabel 对象 |
| `=` | 让 p 指向那个对象 | 把地址存到 p 里 |

**内存图**：

```
栈内存                    堆内存
┌─────────┐              ┌─────────────────┐
│ p       │ ───────────→ │ CLabel 对象      │
│ (地址)   │              │ type = 0        │
└─────────┘              │ x = 10          │
                         │ y = 5           │
                         │ context="Hello" │
                         └─────────────────┘
```

**关键理解**：
- 堆上创建的是 **CLabel 对象**（子类），不是 CControl 对象
- p 只是一个"能指向 CControl 及其子类"的指针
- **指针的类型决定你能调用什么方法，对象的实际类型决定调用哪个版本**

**类比理解**：

```
抽象类 CControl 就像"动物"这个概念
- 你不能创建一个"纯粹的动物"（太抽象了，是猫还是狗？）
- 但你可以说"这是一只动物"，然后指着一只猫

CControl* p = new CLabel(...);
// "这是一个控件" 指着 "一个标签"
// 控件是抽象的，但标签是具体的
```

### 4.3 窗口体系设计

#### 4.3.1 CWindow 基类设计

```cpp
// CWindow.h
class CWindow {
protected:
    int winX, winY;           // 窗口位置
    int winWidth, winHeight;  // 窗口大小
    
    CControl* arr[20];        // 控件数组（最多20个）
    int count;                // 当前控件数量
    int flag;                 // 记录哪个控件被触发
    
    int result;               // 窗口返回结果（状态机用）

public:
    CWindow();
    CWindow(int x, int y, int w, int h);
    virtual ~CWindow();
    
    // 添加控件
    void addControl(CControl* con);
    
    // 显示窗口（画边框 + 显示所有控件）
    void show();
    
    // 运行窗口（处理键盘输入）
    void run();
    
    // 纯虚函数 - 业务逻辑，子类必须实现
    virtual void handle() = 0;
    
    // getter
    int getResult();
};
```

#### 4.3.2 CWindow 核心方法实现

**show() - 显示窗口**：

```cpp
void CWindow::show() {
    // 1. 画窗口边框
    CTool::printBoarder(winX, winY, winWidth, winHeight);
    
    // 2. 显示所有控件（多态调用）
    for(int i = 0; i < count; i++) {
        arr[i]->showControl();
    }
}
```

**run() - 事件循环**：

```cpp
void CWindow::run() {
    int key;
    int currentIndex = 0;  // 当前选中的控件
    
    while(true) {
        key = getch();  // 获取按键
        
        if(key == 27) {  // ESC
            flag = -1;
            break;
        }
        else if(key == 13) {  // Enter
            if(arr[currentIndex]->getType() == 2) {  // 按钮
                flag = currentIndex;
                break;
            }
        }
        else if(key == 9) {  // Tab - 切换控件
            currentIndex = (currentIndex + 1) % count;
        }
        // ... 其他按键处理
    }
}
```

**handle() - 纯虚函数**：

```cpp
// 基类只声明，不实现
virtual void handle() = 0;

// 每个子窗口必须实现自己的业务逻辑
```

#### 4.3.3 子窗口实现示例

**CLoginWin（登录窗口）**：

```cpp
// CLoginWin.cpp
CLoginWin::CLoginWin() 
    : CWindow(20, 5, 40, 15)  // 初始化列表调用父类构造
{
    userRole = 0;
    
    // 添加控件
    addControl(new CLabel(25, 7, "用户名:"));
    addControl(new CEdit(35, 7, "", 10));
    addControl(new CLabel(25, 9, "密码:"));
    addControl(new CEdit(35, 9, "", 10));
    addControl(new CButton(28, 12, "登录"));
    addControl(new CButton(40, 12, "返回"));
}

void CLoginWin::handle() {
    if(flag == 4) {  // 登录按钮
        char* account = arr[1]->getContext();
        char* password = arr[3]->getContext();
        
        CUserManager* mgr = CUserManager::getInstance();
        int role = mgr->verifyUser(account, password);
        
        if(role > 0) {
            userRole = role;
            result = 1;  // 登录成功
        } else {
            // 显示错误信息
        }
    }
    else if(flag == 5 || flag == -1) {  // 返回或ESC
        result = 0;
    }
}
```

### 4.4 继承中的核心知识点

#### 4.4.1 protected 访问权限

```cpp
class CControl {
protected:
    int x, y;  // 子类可以直接访问
};

class CLabel : public CControl {
    void showControl() {
        CTool::gotoxy(x, y);  // OK，子类可以访问 protected
        printf("%s", context);
    }
};

// 外部代码
CLabel* label = new CLabel(10, 5, "Hello");
label->x = 20;  // 错误！外部不能访问 protected
label->setX(20);  // OK，通过 public 方法访问
```

#### 4.4.2 构造函数初始化列表

**核心问题：子类构造时，父类必须先构造好**

C++ 规则：创建子类对象时，**必须先**构造父类部分，**然后**才构造子类部分。

**不用初始化列表会怎样？**

```cpp
CLabel::CLabel(int x, int y, char* text) {
    // ！！！执行到这一行之前，父类 CControl 已经被构造了！！！
    // 用的是 CControl 的【默认构造函数】（无参数）
    // 此时父类的 x, y 已经是 0 或垃圾值
    
    this->x = x;  // 这是"赋值"，不是"初始化"
    this->y = y;  // 父类已经构造完了，现在只是改值
}
```

**执行顺序**：
1. 调用 `CControl()` 默认构造函数 → 父类 x=0, y=0
2. 进入 CLabel 构造函数体
3. `this->x = x;` → 把 x 改成传入的值

**问题来了：如果 CControl 没有默认构造函数呢？**

```cpp
class CControl {
public:
    // 只有带参数的构造函数，没有默认构造函数
    CControl(int type, int x, int y, int w, int h, char* ctx);
    // 注意：没有 CControl(); 
};

class CLabel : public CControl {
public:
    CLabel(int x, int y, char* text) {
        // 编译错误！！！
        // 编译器不知道怎么构造父类（没有默认构造函数可调用）
    }
};
```

**用初始化列表解决**

```cpp
CLabel::CLabel(int x, int y, char* text)
    : CControl(0, x, y, strlen(text), 1, text)  // 告诉编译器：用这些参数构造父类
{
    // 执行到这里时，父类已经用正确的参数构造好了
}
```

**执行顺序**：
1. 调用 `CControl(0, x, y, ...)` → 父类直接用正确的值初始化
2. 进入 CLabel 构造函数体

**总结：为什么必须用初始化列表？**

| 情况 | 不用初始化列表 | 用初始化列表 |
|------|---------------|-------------|
| 父类有默认构造函数 | 可以，但效率低（先默认初始化再赋值） | 直接用正确的值初始化 |
| **父类没有默认构造函数** | **编译报错！** | 必须用，指定调用哪个构造函数 |
| 有 const 成员 | 编译报错（const 不能赋值） | 可以初始化 |
| 有引用成员 | 编译报错（引用必须初始化） | 可以初始化 |

**一句话记忆**：

> **初始化列表是"告诉编译器怎么构造父类和成员"的唯一方式**

#### 4.4.3 虚函数与纯虚函数

| 类型 | 语法 | 含义 |
|------|------|------|
| 普通函数 | `void show();` | 子类可以重写，但不强制 |
| 虚函数 | `virtual void show();` | 子类可以重写，支持多态 |
| 纯虚函数 | `virtual void show() = 0;` | 子类**必须**重写，基类不能实例化 |

**为什么 handle() 是纯虚函数？**

- 每个窗口的业务逻辑都不同
- 基类无法提供通用实现
- 强制每个子窗口必须实现自己的 handle()

#### 4.4.4 虚析构函数

```cpp
// 如果析构函数不是 virtual
class CControl {
    ~CControl() { printf("~CControl\n"); }
};

class CLabel : public CControl {
    ~CLabel() { printf("~CLabel\n"); }
};

CControl* p = new CLabel();
delete p;  // 只调用 ~CControl()，不调用 ~CLabel()！内存泄漏！

// 正确做法：虚析构
class CControl {
    virtual ~CControl() { printf("~CControl\n"); }
};

delete p;  // 先调用 ~CLabel()，再调用 ~CControl()
```

**规则**：只要类可能被继承，析构函数就应该是 virtual

### 4.5 阶段1遇到的经典错误

#### 错误1：子类重复定义父类成员变量

**错误代码**：

```cpp
// CControl.h
class CControl {
protected:
    int x, y;  // 父类定义了
};

// CLabel.h
class CLabel : public CControl {
protected:
    int x, y;  // 子类又定义了一遍！
};
```

**现象**：控件不显示，坐标全是 0

**原因**：
- 子类的 `x, y` 遮蔽了父类的 `x, y`
- 构造函数初始化的是父类的 `x, y`
- showControl() 使用的是子类的 `x, y`（未初始化，是0）

**修复**：删除子类中重复的成员定义

#### 错误2：初始化列表写错

**错误代码**：

```cpp
CLabel::CLabel(int x, int y, char* text) {
    CControl(0, x, y, strlen(text), 1, text);  // 错！这是创建临时对象
}
```

**正确代码**：

```cpp
CLabel::CLabel(int x, int y, char* text)
    : CControl(0, x, y, strlen(text), 1, text)  // 冒号后面才是初始化列表
{
}
```

#### 错误3：忘记 virtual 关键字

**错误代码**：

```cpp
// CControl.h
class CControl {
    void showControl();  // 没有 virtual
};

// 使用
CControl* p = new CLabel(10, 5, "Hello");
p->showControl();  // 调用的是 CControl::showControl()，不是 CLabel 的！
```

**修复**：加上 `virtual`

---

## 五、阶段2：单例模式实现

### 5.1 为什么需要单例？

**问题场景**：

```cpp
// CLoginWin 里
CUserManager* mgr1 = new CUserManager();
mgr1->registerUser("admin", "123", 1);

// CRegisterWin 里
CUserManager* mgr2 = new CUserManager();
// mgr2 里没有刚才注册的用户！因为是不同的对象
```

**需求**：全局只有一个用户管理器，所有窗口共享

### 5.2 单例模式三要素

```cpp
class CUserManager {
private:
    // 1. 私有构造函数（禁止外部 new）
    CUserManager();
    ~CUserManager();
    
    // 2. 静态实例指针
    static CUserManager* instance;
    
    // 数据
    vector<USER> users;

public:
    // 3. 静态获取方法
    static CUserManager* getInstance() {
        if(instance == NULL) {
            instance = new CUserManager();
        }
        return instance;
    }
    
    static void destroyInstance() {
        if(instance != NULL) {
            delete instance;
            instance = NULL;
        }
    }
    
    // 业务方法
    int verifyUser(char* account, char* password);
    bool registerUser(char* account, char* password, int role);
};

// 静态成员初始化（在 .cpp 文件中）
CUserManager* CUserManager::instance = NULL;
```

### 5.3 使用方式

```cpp
// 任何地方都这样获取
CUserManager* mgr = CUserManager::getInstance();
mgr->registerUser("admin", "123", 1);

// 另一个地方
CUserManager* mgr2 = CUserManager::getInstance();
// mgr2 和 mgr 是同一个对象！
```

### 5.4 本项目的三个单例

| 单例类 | 管理的数据 | 存储方式 |
|--------|-----------|----------|
| CUserManager | 用户信息 | vector\<USER\> |
| CDishManager | 菜品信息 | vector\<DISH\> |
| CTableManager | 台桌信息 | vector\<TABLE\> |

---

## 六、阶段3：分页功能实现

### 6.1 为什么需要分页？

- 数据量大时，一屏显示不下
- 控制台窗口高度有限
- 用户体验更好

### 6.2 分页核心算法

```cpp
// 核心变量
int currentPage = 0;   // 当前页（从0开始）
int pageSize = 5;      // 每页显示数量
int totalCount;        // 总数据量
int allPage;           // 总页数

// 计算总页数（向上取整）
allPage = (totalCount + pageSize - 1) / pageSize;
// 例：totalCount=12, pageSize=5 → allPage = (12+4)/5 = 3

// 计算当前页的数据范围
int startIndex = currentPage * pageSize;
int endIndex = min(startIndex + pageSize, totalCount);
// 第0页：0-4，第1页：5-9，第2页：10-11

// 遍历当前页数据
for(int i = startIndex; i < endIndex; i++) {
    DISH* dish = mgr->getDishByIndex(i);
    // 显示第 i 条数据
}

// 上一页
if(currentPage > 0) {
    currentPage--;
}

// 下一页
if(currentPage < allPage - 1) {
    currentPage++;
}
```

### 6.3 为什么选 vector？

| 操作 | vector | 链表 | map |
|------|--------|------|-----|
| 按索引取 `arr[i]` | O(1) | O(n) | O(n) |
| 按ID查找 | O(n) | O(n) | O(log n) |

**分页需要频繁按索引取数据** → vector 最合适

**vector O(1) 的原理**：
```
内存连续：[数据0][数据1][数据2][数据3]
地址计算：目标地址 = 起始地址 + 索引 × 元素大小
一次计算直接定位，不需要遍历！
```

---

## 七、阶段4：状态机重构（重点）

### 7.1 原来的问题：递归调用

**错误代码**：

```cpp
void CLoginWin::handle() {
    if(登录成功) {
        CAdminWin* win = new CAdminWin();
        win->show();
        win->run();
        win->handle();  // 在 handle 里又创建新窗口...
    }
}

void CAdminWin::handle() {
    if(选择台桌管理) {
        CAdminWin_Table* win = new CAdminWin_Table();
        win->handle();  // 又嵌套...
    }
}
```

**调用栈越来越深**：

```
main()
  └── CInitWin::handle()
        └── CLoginWin::handle()
              └── CAdminWin::handle()
                    └── CAdminWin_Table::handle()
                          └── COrderWin::handle()
                                └── ...无限嵌套
```

**问题**：
- 栈空间有限，嵌套太深会**栈溢出崩溃**
- 每个窗口对象都没被 delete，**内存泄漏**

### 7.2 解决方案：状态机

**核心思想**：
- 用一个**主循环**控制所有窗口
- 窗口只负责"告诉主循环下一步去哪"
- 主循环负责创建、运行、销毁窗口

### 7.3 状态机实现

#### 7.3.1 定义状态

```cpp
enum AppState {
    STATE_EXIT = 0,      // 退出程序
    STATE_INIT,          // 1 - 初始界面
    STATE_REGISTER,      // 2 - 注册界面
    STATE_LOGIN,         // 3 - 登录界面
    STATE_ADMIN,         // 4 - 管理员界面
    STATE_MANAGER,       // 5 - 经理界面
    STATE_WAITER,        // 6 - 服务员界面
    STATE_ADMIN_TABLE,   // 7 - 台桌管理
    STATE_ADMIN_DM,      // 8 - 菜品管理
    STATE_ADMIN_PM,      // 9 - 人员管理
    STATE_ORDER          // 10 - 点菜界面
};
```

#### 7.3.2 主循环结构

```cpp
int main() {
    // 初始化单例
    CUserManager::getInstance();
    CDishManager::getInstance();
    CTableManager::getInstance();
    
    int state = STATE_INIT;
    TABLE* selectedTable = NULL;
    
    // 状态机主循环
    while(state != STATE_EXIT) {
        system("cls");
        
        switch(state) {
            case STATE_INIT: {
                CInitWin* win = new CInitWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                delete win;  // 用完立即删除
                
                // 根据结果决定下一个状态
                if(res == 1) state = STATE_REGISTER;
                else if(res == 2) state = STATE_LOGIN;
                else state = STATE_EXIT;
                break;
            }
            
            case STATE_LOGIN: {
                CLoginWin* win = new CLoginWin();
                win->show();
                win->run();
                win->handle();
                
                int res = win->getResult();
                int role = win->getUserRole();
                delete win;
                
                if(res == 1) {
                    if(role == 1) state = STATE_ADMIN;
                    else if(role == 2) state = STATE_MANAGER;
                    else state = STATE_WAITER;
                } else {
                    state = STATE_INIT;
                }
                break;
            }
            
            // ... 其他状态类似 ...
        }
    }
    
    // 销毁单例
    CUserManager::destroyInstance();
    CDishManager::destroyInstance();
    CTableManager::destroyInstance();
    
    return 0;
}
```

#### 7.3.3 窗口只设置 result

**修改后的 handle()**：

```cpp
void CAdminWin_Table::handle() {
    bool running = true;
    while(running) {
        if(flag == 1) {  // 开桌点菜
            // ... 处理逻辑 ...
            selectedTable = table;
            result = 1;      // 告诉主循环：去点菜界面
            running = false;
        }
        else if(flag == -1) {  // ESC
            result = 0;      // 告诉主循环：返回上级
            running = false;
        }
        // 不再创建新窗口！
    }
}
```

### 7.4 状态转换图

```
┌─────────┐
│  EXIT   │←──────────────────────────────────┐
│ state=0 │                                   │
└─────────┘                                   │
     ↑                                        │
     │ ESC                                    │
     │                                        │
┌─────────┐  注册   ┌──────────┐              │
│  INIT   │ ──────→ │ REGISTER │──┐           │
│ state=1 │         └──────────┘  │ 成功      │
└─────────┘                       ↓           │
     │ 登录      ┌─────────────────────┐      │
     ↓           │                     │      │
┌─────────┐      ↓                     │      │
│  LOGIN  │──→ 角色判断                │      │
│ state=3 │      │                     │      │
└─────────┘      ├─→ 管理员 ──→ ┌───────────┐ │
     ↑           │              │   ADMIN   │ │
     │           │              │  state=4  │ │
     │           │              └───────────┘ │
     │           │                 │ │ │      │
     │           │       ┌─────────┘ │ └────┐ │
     │           │       ↓           ↓      ↓ │
     │           │  ┌─────────┐ ┌──────┐ ┌──────┐
     │           │  │ TABLE   │ │  DM  │ │  PM  │
     │           │  │ state=7 │ │ st=8 │ │ st=9 │
     │           │  └─────────┘ └──────┘ └──────┘
     │           │       │
     │           │       ↓ 开桌
     │           │  ┌─────────┐
     │           │  │  ORDER  │
     │           │  │ state=10│
     │           │  └─────────┘
     │           │
     │           ├─→ 经理 ──→ ┌───────────┐
     │           │            │  MANAGER  │
     │           │            │  state=5  │
     │           │            └───────────┘
     │           │
     │           └─→ 服务员 ─→ ┌───────────┐
     │                        │  WAITER   │
     │                        │  state=6  │
     │                        └───────────┘
     │                             │
     └─────────── 注销 ────────────┘
```

### 7.5 状态机的优点

| 优点 | 说明 |
|------|------|
| **无递归** | 所有窗口在同一层循环，栈深度恒定为1 |
| **无内存泄漏** | 每个窗口 new 完立即 delete |
| **逻辑清晰** | 所有跳转逻辑集中在 main，一目了然 |
| **易于维护** | 新增窗口只需加一个 case |
| **易于调试** | 打印 state 就知道当前在哪个界面 |

### 7.6 result 的含义约定

**重要**：result 是每个窗口**自己定义**的，不是全局统一！

```cpp
// CInitWin 的 result：
// 0 = 退出  1 = 注册  2 = 登录

// CLoginWin 的 result：
// 0 = 返回  1 = 登录成功

// CAdminWin 的 result：
// 0 = 返回  1 = 台桌管理  2 = 菜品管理  3 = 人员管理  4 = 注销

// CAdminWin_Table 的 result：
// 0 = 返回  1 = 开桌点菜（selectedTable有值）
```

main 里根据不同窗口的 result 做不同的状态切换。

---

## 八、常见错误速查表

| 错误现象 | 原因 | 修复方法 |
|----------|------|----------|
| 控件不显示 | 子类重复定义父类成员变量 | 删除子类中的重复定义 |
| 字符串比较失败 | 用 `==` 比较 char[] | 改用 `strcmp() == 0` |
| 条件永远为真 | `if(flag = -1)` 是赋值 | 改为 `if(flag == -1)` |
| sprintf 报错 | 拼写成 `springf` | 改正拼写 |
| gotoxy 报错 | 缺少命名空间 | 改为 `CTool::gotoxy()` |
| 多态不生效 | 忘记写 `virtual` | 给基类函数加 `virtual` |
| 析构不完整 | 基类析构非虚 | 改为 `virtual ~Base()` |
| 程序崩溃 | 递归调用栈溢出 | 改用状态机模式 |
| 内存泄漏 | new 了没 delete | 状态机中及时 delete |
| 总价累加错误 | 没重置变量 | 计算前加 `total = 0;` |

---

## 九、项目文件清单

```
project1127_orderdish/
│
├── 控件类
│   ├── CControl.h / CControl.cpp    (基类)
│   ├── CLabel.h / CLabel.cpp        (标签)
│   ├── CEdit.h / CEdit.cpp          (输入框)
│   └── CButton.h / CButton.cpp      (按钮)
│
├── 窗口类
│   ├── CWindow.h / CWindow.cpp      (基类)
│   ├── CInitWin.h / CInitWin.cpp    (初始界面)
│   ├── CLoginWin.h / CLoginWin.cpp  (登录)
│   ├── CRegisterWin.h / CRegisterWin.cpp (注册)
│   ├── CAdminWin.h / CAdminWin.cpp  (管理员主界面)
│   ├── CManagerWin.h / CManagerWin.cpp (经理)
│   ├── CWaiterWin.h / CWaiterWin.cpp (服务员)
│   ├── CAdminWin_Table.h / CAdminWin_Table.cpp (台桌管理)
│   ├── CAdminWin_DM.h / CAdminWin_DM.cpp (菜品管理)
│   ├── CAdminWin_PM.h / CAdminWin_PM.cpp (人员管理)
│   └── COrderWin.h / COrderWin.cpp  (点菜)
│
├── 数据管理类 (单例)
│   ├── CUserManager.h / CUserManager.cpp
│   ├── CDishManager.h / CDishManager.cpp
│   └── CTableManager.h / CTableManager.cpp
│
├── 工具类
│   └── CTool.h / CTool.cpp
│
└── main.cpp (状态机主循环)
```

---

## 十、学习收获总结

### 10.1 面向对象核心

1. **封装**：数据和方法放一起，用访问权限控制
2. **继承**：提取公共部分到基类，子类复用
3. **多态**：同一接口，不同实现，运行时决定

### 10.2 设计模式

1. **单例模式**：全局唯一实例，共享数据
2. **状态机模式**：用状态变量控制流程，避免递归

### 10.3 实用技能

1. **分页算法**：索引计算、边界处理
2. **内存管理**：new/delete 配对使用
3. **调试技巧**：打印状态、逐步排查

### 10.4 避坑经验

1. 子类不要重复定义父类成员
2. 用初始化列表调用父类构造
3. 基类析构函数要 virtual
4. 字符串比较用 strcmp
5. 避免递归调用，用状态机替代

