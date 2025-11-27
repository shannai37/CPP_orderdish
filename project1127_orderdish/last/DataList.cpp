#include "DataList.h" 

// 创建链表： 创建一个头结点 
LIST *  New_List_Init()
{
	// 1.分配内存创建头节点 
	LIST * head = (LIST *)malloc(sizeof(LIST));
	
	// 2. 检查是否成功
	if(head == NULL)
	{
		printf("链表创建失败，内存分配失败\n");
		return NULL;	
	} 
	
	// 3. 初始化内存空间（清零）
	memset( head,0,sizeof(LIST) ) ;
	

	// 4. 头节点的next指向NULL（表示空链表） 
	head -> pnext = NULL;
	head -> data  = NULL;
	printf("链表创建成功\n"); 
	return head; 	
}

void  New_List_pushback(LIST * head, void *pdata,int length)
{
	
	// 1. 检查头节点
	if(head == NULL)
	{
		printf("链表创建失败，内存分配失败\n");
		return ;	
	} 
	
	// 2.创建新结点
	LIST * newNode = (LIST *)malloc(sizeof(LIST));	
	
	if(newNode == NULL)
	{
		printf("错误：新节点创建失败");		
		return; 
	} 
	
	// 3.初始化新节点 
	// 通用链表数据区在堆区动态创建出来 
	memset(newNode,0,sizeof(LIST)); 
	newNode -> data = malloc(length);  // 存储菜单数据
	if(newNode -> data == NULL)
	{
		printf("错误：新节点数据域创建失败");		
		return; 
	} 
	memset(newNode -> data,0,length);
	
	// 从栈区拷贝数据到堆区
	memcpy(newNode -> data,pdata,length);
	 
	newNode -> pnext = NULL; // 新节点是新的尾节点
    
    
    
	// 4. 找到当前的尾节点
	LIST * ptemp = head;		// 从头节点开始
	while(ptemp -> pnext != NULL)
	{
		ptemp = ptemp -> pnext;	 // 一直往后走
	}	
	// 循环结束时，ptemp指向最后一个节点
    
    // 5. 将新节点连接到尾部
	ptemp -> pnext = newNode;
	
	
	printf("新节点添加成功！\n");
}


int New_List_getSize(LIST * head)
{
	int count = 0;
	
	// 从头节点开始遍历链表  
	LIST * ptemp = head;
	while(ptemp->pnext != NULL)
	{
		count++;
		ptemp = ptemp -> pnext;
	}
	
	return count;	
} 

LIST * New_getNodeByPos(LIST * head,int position)
{
	// 1.检查参数 
	if(position < 1 || head == NULL)
	{
		printf("位置或链表头节点不合法！\n");
		return NULL;
	}
	
	// 2.到第一个有效节点开始
	LIST * ptemp = head -> pnext;
	
	// 3.遍历  注意position位置不能超过整个链表长度！ 
	int i;
	for( i = 1 ; i < position && ptemp != NULL ; i++)
	{
				ptemp  = ptemp -> pnext;
	} 
	
	// 4.到达NULL报错
	if(ptemp == NULL)
	{
		printf("已经到达链表末尾，位置不合法！\n");
		return NULL;	
	}
	
	// 5.返回节点 
	return ptemp; 
}


int New_deleteNodeByPos(LIST * head,int position)
{
	// 1.检查参数
	if(position < 1 || head == NULL)
	{
		printf("参数不合法！\n");
		return 0;	// 暂定0就是失败情况	
	} 
	
	// 2.找到前驱节点
	LIST * ppre = head;
	int i;
	for( i = 1 ; i < position && ppre -> pnext != NULL ; i++) //我们要找的是前驱节点，所以下一个节点不能为空 
	{
		ppre = ppre -> pnext ;
		 
	}
	
	// 3.下一个节点是NULL的话，没找到前驱节点
	if(ppre -> pnext == NULL)
	{
		printf("找不到前驱节点！"); 
		return 0; 
	} 
	
	// 4.找到前驱节点，开始删除
	LIST * ptemp = head;
	ptemp  = ppre -> pnext; // 现在ptemp指向了被删除节点
	ppre -> pnext = ptemp -> pnext; 
	free(ptemp -> data);
	free(ptemp);
	
	// 5.返回成功 
	return 1; 
	 
}

// 在指定位置插入节点 
int New_List_insert(LIST *head,void *pdata,int length,int position)
{
	// 1.检查参数
	if(position < 1 || head == NULL)
	{
		printf("参数不合法！\n");
		return 0;	// 暂定0就是失败情况	
	} 
	
	// 2.创建新节点 
	LIST * newNode = (LIST *)malloc(sizeof(LIST));
	if(newNode == NULL) 
	{
        printf("内存分配失败！\n");
        return 0;
    }
	memset(newNode,0,sizeof(LIST));
	
	newNode -> data = malloc(length);
	if(newNode -> data == NULL)
	{
		printf("错误：新节点数据域创建失败");		
		return; 
	} 
	memset(newNode -> data,0,length);
	// 从栈区拷贝数据到堆区
	memcpy(newNode -> data,pdata,length);
	
	
	// 3.找到前驱节点（第 position-1 个节点）
	LIST *ppre = head;
	int i;
	for(i = 1 ; i < position && ppre -> pnext != NULL ; i++)
	{
		ppre = ppre -> pnext; 	
	} 
	
	// 4.插入新节点
	newNode -> pnext = ppre -> pnext;
	ppre -> pnext = newNode;
	
	printf("节点插入成功！\n");
	return 1;
}

// 清空链表(保留头节点) 
void New_List_clear(LIST *head)
{
	// 1.检查参数 
	if(head == NULL) 
	{
        return;
    }
    
    // 2.从第一个有效数据节点开始 
    LIST *p = head->pnext;
    
    // 3.遍历删除所有节点
	while(p != NULL)
	{
		LIST * temp = p;
		p = p -> pnext;	
		free(temp->data); // 先释放数据  
		free(temp);		  // 再释放节点 
	} 
	
	// 4.	头节点的next指向NULL
    head->pnext = NULL;
    printf("链表已清空！\n");
}


// 摧毁链表(不保留头节点)
void New_List_destroy(LIST **head)
{
		// 1.检查参数
	if(*head == NULL) 
	{
        return;
    }
    
    // 2.先清空所有节点
	New_List_clear(*head);
	
	// 3.释放头节点
	free(*head);
	*head = NULL; // 将头指针设为NULL
	
	printf("链表已销毁!\n"); 
}

