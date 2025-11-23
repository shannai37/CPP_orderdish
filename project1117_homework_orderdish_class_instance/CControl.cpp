#include "CControl.h"

// 无参构造函数
CControl::CControl()
{
	this->type = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	strcpy(this->context,"");
} 
		
// 带参构造函数 
CControl::CControl(int type,int x,int y,int width,int height,char *context)
{
	this->type = type;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    strcpy(this->context, context);
} 	
		
// 析构函数
CControl::~CControl()
{
	
} 	

// getter
int CControl::getType()
{
	return this->type;
}

int CControl::getX()
{
	return this->x;
}

int CControl::getY()
{
	return this->y;
}

int CControl::getWidth()
{
	return this->width;
}

int CControl::getHeight()
{
	return this->height;
}



//int CControl::getKey()
//{
//	return this->key;
//}

char* CControl::getContext()
{
	return this->context;
}

// setter
void CControl::setType(int type)
{
	this->type = type;
}
void CControl::setX(int x)
{
	this->x = x;
}

void CControl::setY(int y)
{
	this->y = y;
}

void CControl::setWidth(int width)
{
	this->width = width;
}

void CControl::setHeight(int height)
{
	this->height = height;
}


//int CControl::setKey(int key)
//{
//	this->key = key;
//}


void CControl::setContext(const char* context)
{
	strcpy(this->context,context);
}




