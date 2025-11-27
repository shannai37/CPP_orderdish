#ifndef CWINDOW_H
#define CWINDOW_H

#include "CControl.h"
#include "CTool.h"
#include "CLabel.h"
#include "CButton.h"
#include "CEdit.h"


//针对不同的点菜窗口，于是我们封装了窗口结构体 里面包括了各项参数与控件结构体 
//可以想象成一个空的收纳箱，准备往里面装东西 
typedef struct win
{
	int winX,winY; 			//窗口左上角位置
	int winWidth,winHeight;	//窗口尺寸 
	int count; 				//已添加的控件数量 
	int flag; 				//纪录业务下标(即当前光标走到哪个组件了) 
	CONTROL arr[20]; 		//万能控件数组(容器，用来装不同的控件) 
}CWIN;

//往窗口结构体里添加控件 
//就像往购物车里加商品，每次加一个，count就是购物车的商品数量
void addControl(CWIN *win, CONTROL *con);
 
void printWindow(CWIN *win); 

void winRun(CWIN *win); 
#endif 
