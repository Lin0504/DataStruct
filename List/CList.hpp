#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

typedef int DataType;

typedef struct ListNode
{
	DataType _data;
	struct ListNode* _next;
}ListNode,*PListNode;

//初始化
void InitSList(PListNode* pList)
{
	assert(pList);
	*pList = 0;
}
//销毁
void DestorySList(PListNode* pList)
{
	ListNode* begin = *pList;
	assert(pList);
	while (begin)
	{
		ListNode* tmp = begin;
		begin = begin->_next;

		free(tmp);
	}
	*pList = 0;
}

//打印
void Print(PListNode pList)
{
	ListNode* begin = pList;
	printf("PListNode:");
	while(begin)
	{
		printf("->%d", begin->_data);
		begin = begin->_next;
	}
	printf("->NULL\n");
}

//长度
int GetLength(PListNode pList)
{
	int length = 0;
	ListNode* begin = pList;
	while (begin)
	{
		++length;
		begin = begin->_next;
	}
	return length;
}

//创建节点
ListNode* CreateNode(DataType data)
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	tmp->_data = data;
	tmp->_next = NULL;
	return tmp;
}

//尾插
void PushBack(PListNode* pList, DataType data)
{
	assert(pList);
	ListNode *tmp = CreateNode(data);
	//没有节点
	if (*pList == NULL)
	{
		*pList = tmp;
	}
	//有一个或一个以上节点
	else
	{
		ListNode* begin = *pList;
		while (begin->_next)
		{
			begin = begin->_next;
		}
		begin->_next = tmp;
	}
}

//尾删
void PopBack(PListNode* pList)
{
	assert(pList);
	ListNode* begin = *pList;
    //1.没有节点
	if (*pList == NULL)
	{
		return;
	}
	//2.一个节点
	if (begin->_next == NULL)
	{
		free(*pList);
		*pList = NULL;
		return;
	}
	//3.两个或两个以上节点
	if (begin->_next->_next == NULL)
	{
		while (begin->_next)
		{
			begin = begin->_next;
		}
		free(begin->_next);
		begin->_next = NULL;
	}
}

//头插
void PushFront(PListNode* pList, DataType data)
{
	assert(pList);
	ListNode*tmp = CreateNode(data);
	//没有节点
	if (*pList == NULL)
	{
		*pList = tmp;
	}
	//有节点
	else
	{
		tmp->_next = *pList;
		*pList = tmp;
	}
}

//头删
void PopFront(PListNode* pList, DataType data)
{
	assert(pList);
	ListNode* del = *pList;
	//1.没有节点
	if (*pList == NULL)
	{
		return;
	}
	//2.只有一个节点
	if ((*pList)->_next == NULL)
	{
		free(del);
		*pList = NULL;
		return;
	}
	//3.两个或两个以上节点
	if ((*pList)->_next->_next == NULL)
	{
		*pList = del->_next;
		free(del);
		return;
	}
}

//查找某个节点
ListNode* FindNode(PListNode pList, DataType data)
{
	assert(pList);
	ListNode* begin = pList;
	while (begin)
	{
		if (begin->_data == data)
		{
			return begin;
		}
		begin = begin->_next;
	}
	return 0;
}

//删除任意节点
void Remove(PListNode* pList, DataType data)
{
	assert(pList);
	ListNode*prev = NULL;
	ListNode*begin = *pList;
	ListNode*del = NULL;
	 
	while (begin)
	{
		if (begin->_data == data)
		{
			del = begin;
			//1.头节点
			if (*pList == begin)
			{
				*pList = (*pList)->_next;
			}
			//2.中间节点
			else
			{
				prev->_next = begin->_next;
			}
			free(del);
		}
		prev = begin;
		begin = begin->_next;
	}
}

//在节点n后插入一个节点
void Insert(PListNode* pList, ListNode* n, DataType data)
{
	assert(pList);
	ListNode *tmp = 0;
	tmp = CreateNode(data);
	ListNode* begin = *pList;
	//1.链表为空
	if (*pList == NULL)
	{
		*pList = tmp;
	}
	//2.链表不为空
	else
	{
		assert(n);
		tmp->_next = n->_next;
		n->_next = tmp;
	}

}
