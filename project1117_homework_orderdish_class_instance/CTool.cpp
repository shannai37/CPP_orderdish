#include "CTool.h"

//定义在CTool.h中声明的全局变量
//USER arr[10] = {
//	{"admin","123456",1},
//	{"manager","123456",2},
//	{"waiter","123456",3},	
//};
//
//int uCount = 3;
//
//MENU arr1[10] = {
//	{10000,"土豆炒土豆",10.5,20},
//	{10001,"番茄炒番茄",11.5,30},
//	{10002,"萝卜炒萝卜",9,15},	
//};
//
//int mCount = 3;
//LIST *userList = NULL;
//LIST *menuList = NULL;


/*
函数名称：gotoxy 
函数功能：光标定位
参数列表：int x : x坐标
		  int y : y坐标
函数返回值 :无 
*/
void CTool::gotoxy(int x, int y)
{
    HANDLE hOut;
    COORD pos = {x, y};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}


/*
-水平线占一个字符，竖线|要两个空格
才能达到从视觉上高宽一样的效果 

*/
void CTool::printBoarder(int startX, int startY, int width, int height)
{
    int i, j;
    
    for(i = 0; i < height; i++)
    {
        gotoxy(startX, startY + i);  // 每行开始时定位到起始位置?
        
        for(j = 0; j < width; j++)
        {
            
            if(i == 0) // 第一行 
			{
			    if(j == 0) // 左上角 
			    {
			        printf("┌");
			    }
			    else if(j == width - 1) // 右上角
			    {
			        printf("┐");
			    }
			    else // 水平线
			    {
			        printf("─");
			    }
			}
           else if(i == height - 1) // 最后一行
			{
			    if(j == 0) // 左下角
			    {
			        printf("└");
			    }
			    else if(j == width - 1) // 右下角
			    {
			        printf("┘");
			    }
			    else // 水平线
			    {
			        printf("─");
			    }
			}
           else // 普通行
			{
			    if(j == 0 || j == width - 1) // 垂直分隔线
			    {
			        printf("│");
			    }
			    else // 空格填充
			    {
			        printf(" ");  // 因为竖线是空格，或使用全角空格"　"
			    }
			}
        }
    }
}

/*
为什么方向键要读取两次？
因为它们在 Windows 控制台中是双字节扫描码 
按下 ↑  第1次 getch()：224   第2次 getch()：72
按下 ↓  第1次 getch()：224   第2次 getch()：80
按下 ←  第1次 getch()：224   第2次 getch()：75
按下 →  第1次 getch()：224   第2次 getch()：77

按下 F1  第1次 getch()：0    第2次 getch()：59
按下 F2  第1次 getch()：0    第2次 getch()：60
*/
int CTool::getKey()
{
	int key = getch();
	
	switch(key)
	{
		case 13:
			return KEY_ENTER;
		case 27:
			return KEY_ESC;
		case 224:   // 特殊键的前导字节
			key = getch(); // 再读取第2个字节，真正的键值
			if(key == 72) 
			{
				return KEY_UP;
			}
			else if(key == 80)
			{
				return KEY_DOWN;
			}
			else if(key == 75)
			{
				return KEY_LEFT;
			}
			else if(key == 77)
			{
				return KEY_RIGHT;
			}
		default:
			return key; // 其他普通键直接返回 
	} 
}

/*
打印row行col列的表格 
输入的宽度和高度要能整除row和col 
*/
void CTool::printTable(int startX,int startY,int width,int height,int col,int row) 
{
	 
    int i, j;
   //行高 = 高度/行数 
	int rowh = height / row;
	//列宽 = 宽度/列数 
	int colw = width / col;
    
    gotoxy(startX, startY);
    
    for(i = 0; i < height; i++)
    {
        gotoxy(startX, startY + i);  // 每行开始时定位到起始位置
        
        for(j = 0; j < width; j++)
        {
           if(i == 0) // 首行 
			{
			    if(j == 0) // 首列 
			    {
			        printf("┌");
			    }
			    else if(j % colw == 0) // 列分割线
			    {
			        printf("┬");
			    }
			    else if(j == width - 1) // 最后一列
			    {
			        printf("┐");
			    }
			    else // 水平线
			    {
			        printf("─");
			    }
			}
            else if(i % rowh == 0) // 中间行分割线
			{
			    if(j == 0) // 首列
			    {
			        printf("├");
			    }
			    else if(j % colw == 0) // 列分割线
			    {
			        printf("┼");
			    }
			    else if(j == width - 1) // 最后一列
			    {
			        printf("┤");
			    }
			    else // 水平线
			    {
			        printf("─");
			    }
			}
            else if(i == height - 1) // 最后一行
			{
			    if(j == 0) // 首列
			    {
			        printf("└");
			    }
			    else if(j % colw == 0) // 列分割线
			    {
			        printf("┴");
			    }
			    else if(j == width - 1) // 最后一列
			    {
			        printf("┘");
			    }
			    else // 水平线
			    {
			        printf("─");
			    }
			}
            else // 普通行
			{
			    if(j == 0 || j % colw == 0 || j == width - 1) // 垂直分隔线
			    {
			        printf("│");
			    }
			    else // 空格填充
			    {
			        printf(" ");
			    }
			}
        }
    }
}
