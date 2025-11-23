#ifndef CCONTROL_H
#define CCONTROL_H

#define LABEL 1
#define BUTTON 2
#define EDIT 3

//控件结构体 
typedef struct Control
{
	int inputType;//控件类型 1:LABEL 2:BUTTON 3:EDIT
	int x;//控件左上角x坐标
	int y;//控件左上角y坐标
	int width;//控件宽度
	int height;//控件高度
	char context[50];//控件字符串,从20改到50，改的更大，容纳更多字符 
	int maxLength;//最大长度
	int ips;//显示类型: 明文1 密文0
	int contentType;//输入内容类型 1：数字 2：字母 3：数字+字母
} CONTROL;


#endif

