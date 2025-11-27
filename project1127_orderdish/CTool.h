#ifndef CTOOL_H
#define CTOOL_H

#include <windows.h>
#include <stdio.h> 
#include <conio.h>

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// 控件类型定义
#define Label 0
#define EDIT 1
#define BUTTON 2
class CTool {
public:
   static void gotoxy(int x, int y);
   static void printBoarder(int startX, int startY, int width, int height);
   static int getKey();
   static void printTable(int startX, int startY, int width, int height, int col, int row);
};

#endif
