#include "DataCollection.h"
#include <iostream>

using namespace std;

void freeNode(LinkList p, bool (*clear)(LinkList& p)) {
	if (!clear) {
		free(p);
	}
	else {
		clear(p);
	}
}
/*
* 初始化单链表
* 操作要求：无
* 操作结果：
* 1.初始化头节点数据域长度为0。
* 2.next指针指向NULL。
*/
void InitLinkList(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) exit(OVERFLOW);
	L->next = NULL;//将指针域置为NULL
}

/*
* 清空单链表
* 操作要求：单链表存在
* 初始条件：如数据类型存储数据类型需要手动释放空间，则需传入自定义clear函数
* 操作结果：
* 1.单链表内部节点被释放
* 2.修改指针域
*/
void ClearLinkList(LinkList& L) {
	if (!L) {
		cout << "不能释放空指针！" << endl;
		return;
	}
	LinkList next = L->next;
	if (next) {
		ClearLinkList(next);
		free(next);
		next = NULL;
	}
	L->next = NULL;
}
void ClearLinkList(LinkList& L, bool (*clear)(element&)) {
	if (!L) {
		cout << "不能释放空指针！" << endl;
		return;
	}
	LinkList next = L->next;
	if (next) {
		ClearLinkList(next);
		clear(next->data);
		free(next);
		next = NULL;
	}
	L->next = NULL;
}

/*
* 摧毁单链表
* 操作要求：单链表存在
* 初始条件：如数据类型存储数据类型需要手动释放空间，则需传入自定义clear函数
* 操作结果：
* 1.单链表内部节点被释放
* 2.单链表头节点长度更改
* 3.释放头节点
*/
void DeleteLinkList(LinkList& L) {
	if (!L) {
		cout << "不能释放空指针！" << endl;
		return;
	}
	LinkList next = L->next;
	if (next) {
		DeleteLinkList(next);
	}
	L->next = NULL;
	free(L);
}

void DeleteLinkList(LinkList& L, bool (*clear)(element&)) {
	if (!L) {
		cout << "不能释放空指针！" << endl;
		return;
	}
	LinkList next = L->next;
	if (next) {
		DeleteLinkList(next);
	}
	L->next = NULL;
	free(L);
	clear(L->data);
}

/*
* 头插法插入数据对象到单链表
* 初始条件：单链表存在
* 操作结果：将数据对象插入到第一个位置,返回插入结果
* 时间复杂度：O(1)
*/
bool InsFirst(LinkList& L, element e) {
	LinkList node = (LinkList)malloc(sizeof(LNode));
	if (!node) exit(OVERFLOW);
	node->data = e;
	node->next = L->next;
	L->next = node;
	return true;
}

/*
* 尾插法插入数据对象到单链表
* 初始条件：单链表存在
* 操作结果：将数据对象插入到第最后一个位置,返回插入结果
* 时间复杂度O(N)
*/
bool InsLast(LinkList& L, element e) {
	LinkList p = L;
	while (p->next) {
		p = p->next;
	}//找到最后一个节点
	LinkList node = (LinkList)malloc(sizeof(LNode));
	if (!node) exit(OVERFLOW);
	node->data = e;
	node->next = NULL;
	p->next = node;
	return true;
}

/*
* 查找第pos个节点的值
* 初始条件：单链表存在，节点存在
* 操作结果：将查找值给引用对象e返回，函数返回查找结果状态。
*
*/
bool GetElem(LinkList L, int pos, element* e) {
	LinkList p = L->next;//计数器 & 遍历器
	while (p && pos-- > 1) {
		p = p->next;
	}//找到最后相应位置的节点
	e = p == NULL ? NULL : &p->data;//如果满足条件则绑定e返回
	return p;//返回执行结果
}


/*
* 取下链表的最后一个节点
* 初始条件：单链表存在，存在尾节点，L->next ！= NULL
* 操作结果：删除单链表的最后一个节点并以q返回
* 操作细节：当且仅当自定义元素为栈区类型时，才无需指定函数，否则需要指定清理函数。
*/
bool Remove(LinkList& L, LNode* q, bool (* clear)(LinkList&)) {
	if (!L->next) {
		return false;
	}
	LinkList pre = L;//记录上一结点
	LinkList p = L->next;//记录尾节点
	while (p->next) {
		pre = pre->next;
		p = p->next;
	}
	q = p;
	pre->next = NULL;
	freeNode(q, clear);
	q = NULL;
}


/*
* 将两个链表链接到一起
* 初始条件：两个单链表存在
* 操作结果：将第二个链表连接到第一个链表的最后，并销毁第二个链表的头节点
* 时间复杂度O（1）
*/
bool Append(LinkList& fir, LinkList& sec) {
	if (fir == NULL) {
		cout << "第一个链表不能为空。" << endl;
		return false;
	}
	//找到第一个链表的尾巴
	LinkList p = fir;
	while (p->next) {
		p = p->next;
	}
	//链接
	p->next = sec->next;
	//释放
	free(sec);
	sec = NULL;
	return true;
}

/*
* 返回线性链表L中第1个与e满足函数compare判定关系的元素位置
* 初始条件：线性表存在，元素e合法，判定关系自定义
* 操作结果：如满足条件则返回节点，不满足返回NULL
*/
LinkList LocateElem(LinkList L, element e, 
	bool (*compare)(element f, element s)) {
	LinkList p = L;//节点指针
	while (p->next) {
		if (compare(p->next->data, e)) { return p; }
		p = p->next;
	}
	return NULL;
}

/*
* 返回链表中元素的个数
*/
int GetLength(LinkList L) {
	int x = 0;
	while (L->next) {
		L = L->next;
		x++;
	}
	return x;
}