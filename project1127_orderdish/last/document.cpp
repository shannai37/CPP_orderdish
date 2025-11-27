#include "document.h"

// 保存链表到文件 
void saveMenuList(LIST * head,char *filename)
{
	FILE * fp = NULL;
	fp = fopen(filename,"w+");
	LIST * temp = head -> pnext; // 从第一个有效节点开始 
	
	char buf[100] = {0}; 
	int count = 0; // 计数，看写入多少条数据 
	while(temp != NULL)
	{
		// 取出结构体数据 
		MENU *menu = (MENU *)(temp -> data);
		 
//		// 将结构体数据拼接成字符串
//		sprintf(buf,"%d %s %.2f %d\n",
//		menu->menuID,
//		menu->menuName,
//		menu->price,
//		menu->num
//		) ;
//		
//		// 文本写入文件 
//		fwrite(buf,1,strlen(buf),fp);
		
		fprintf(fp,"%d %s %.2f %d\n",menu->menuID,menu->menuName,menu->price,menu->num);
		
		// 刷新操作文件的内存，让写入数据更高效 
		fflush(fp);	
		
		// 写入成功打印文字
		count++;
		printf("菜品写入成功！已写入 %d 条数据！\n",count); 
		temp = temp -> pnext;
	} 
	fclose(fp);
	printf("菜品全部写入成功！\n");
}

// 从文件中加载出菜单链表
LIST* getMenuList(char *filename)
{
	FILE * fp = NULL;
	fp = fopen(filename,"r+");
	LIST * head = New_List_Init(); // 创建新链表头节点，装菜单 
	
	if (fp == NULL) 
	{
        printf("菜品文件不存在，链表为空\n");
        return head;
    }
    
    char buf[200] = {0};
    int count = 0; // 纪录载入的菜品数量 
//    // fgets更好，能直接读取一行，避免频繁判断是否到'\n' 
//    // 成功返回 buf 指针，失败返回 NULL
//    while( fgets(buf,sizeof(buf),fp) != NULL ) 
//	{
//		MENU  menu = {0}; // 创建一个菜单的结构体存储数据 
//		// scanf/sscanf 中 double 必须用 %lf !!!! 
//		// 它们不像printf中的double也能用%f，因为它们不会自动类型提升！ 
//		sscanf(buf, "%d %s %lf %d", 
//               &menu.menuID, 
//               menu.menuName, 
//               &menu.price,
//			   &menu.num
//			   );
//		New_List_pushback(head,&menu,sizeof(menu));
//		// 菜品加载成功打印文字
//		count++;
//		printf("菜品加载成功！已加载 %d 条数据！\n",count); 
//	}
	
	MENU  menu = {0}; // 创建一个菜单的结构体存储数据
	while( fscanf(fp,"%d %s %lf %d",
	&menu.menuID,menu.menuName,&menu.price,&menu.num) == 4
	) 
	{
		New_List_pushback(head,&menu,sizeof(MENU));
		// 菜品加载成功打印文字
		count++;
		printf("菜品加载成功！已加载 %d 条数据！\n",count);
	}
    
	fclose(fp);
	printf("菜品加载成功！\n");
	return head;   
}

// 保存用户链表到文件 
void saveUserList(LIST * head,char *filename)
{
	FILE *fp = fopen(filename,"w+");
	LIST * temp = head -> pnext ; // 从第一个有效节点开始读
	
	char buf[100] = {0};
	int count = 0; 
	while (temp != NULL)
	{
		// 取出结构体数据 
		USER *user = (USER *)(temp -> data);
		
//		// 将结构体数据拼接成字符串 
//		sprintf(buf,"%s %s %d\n", 
//		user->account,
//		user->password,
//		user->role
//		);
//		
//		// 写入成功 
//		fwrite(buf,1,strlen(buf),fp);
		
		// 结合了sprintf + fwrite 
		// 与fwrite不一样 写入文件时没有缓冲区 
		fprintf(fp,"%s %s %d\n",user->account,user->password,user->role);
		
		// 刷新操作文件的内存，让写入数据更高效 
		fflush(fp);		
//		
		// 写入成功打印文字
		count++;
		printf("用户写入成功！已写入 %d 条数据！\n",count); 
		temp = temp -> pnext;
	}
	fclose(fp);
	printf("用户全部写入成功！\n");
	 
}

// 从文件中加载出用户链表
LIST* getUserList(char *filename)
{
	FILE *fp = fopen(filename,"r+");
	LIST * head = New_List_Init();
	if(fp == NULL)
	{
		printf("User文件不存在，链表为空\n");
        return head;
	}
	
	char buf[100] = {0};
	int count = 0;
//	while ( fgets(buf,sizeof(buf),fp) != NULL )
//	{
//		USER user;
//		sscanf(buf,"%s %s %d",
//		user.account,
//		user.password,
//		&user.role
//		);
//		
//		New_List_pushback(head,&user,sizeof(user));
//		// 人员加载成功打印文字
//		count++;
//		printf("人员加载成功！已加载 %d 条数据！\n",count); // 加载成功 
//	}

	 // 直接从文件读取并解析，一步到位
	 USER user;
    while (fscanf(fp, "%s %s %d", 
                  user.account, user.password, &user.role) == 3) 
	{
        //                                                    ↑ 返回成功读取的项数
        New_List_pushback(head, &user, sizeof(USER));
        // 人员加载成功打印文字
		count++;
		printf("人员加载成功！已加载 %d 条数据！\n",count); // 加载成功
    }
	fclose(fp);
	printf("人员加载成功！\n");
	return head; 
}
