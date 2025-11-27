#ifndef CTABLEMANAGER_H
#define CTABLEMANAGER_H

#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;

// 台桌结构体
typedef struct {
    int tableID;          // 台桌ID
    char tableNum[10];    // 台桌编号（z1, z3等）
    int status;           // 状态：0=空闲，1=占用
    char description[30]; // 台桌描述
} TABLE;

class CTableManager
{
	private:
		static CTableManager* instance;	
		vector<TABLE> tables;
		
		CTableManager();  // 私有构造
    	~CTableManager();
	public:
		static CTableManager* getInstance();
		static void destroyInstance();
		
		// getter
		int getTableCount();
		TABLE* getTableByIndex(int index); 
		TABLE* getTableBynum(char* num);
		TABLE* getTableByID(int tableID);  
		
		// setter
		bool addTable(int id, char* num, int status, char* desc);
    	bool updateTableStatus(int tableID, int newStatus);  // 修改状态
};

#endif
