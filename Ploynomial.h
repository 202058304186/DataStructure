#pragma once
/*
* ========================================================================LinkList
* 单链表
*/


typedef struct term {
	float coef; //系数
	int expn;//指数
	bool operator ==(const struct term b) {
		return (this->coef - b.coef) > 0.000001
			|| (this->coef - b.coef) < 0.000001
			&& this->expn == b.expn;
	}
	void operator =(const struct term b) {
		this->coef = b.coef;
		this->expn = b.expn;
	}
	bool operator <(const struct term b) {
		return this->expn < b.expn;
	}
}term, ElemType;

//声明并定义线性表初始值
#define element term
/*
* 属性规约：
* element data为单链表的数据区
* next指针指向下一节点位置，如果无下一节点则为空。
* 规定头结点的数据域存储单链表长度。
*/
typedef struct LNode {
	element data;
	struct LNode* next;
}LNode, * LinkList;

/*
* 释放一个节点:当指定了清理方法时，调用清理方法
*/
void freeNode(LinkList p, bool (*clear)(LinkList& p));

/*
* 初始化单链表
* 操作要求：无
* 操作结果：
* 1.初始化头节点数据域长度为0。
* 2.next指针指向NULL。
*/
void InitLinkList(LinkList&);

/*
* 清空单链表
* 操作要求：单链表存在
* 初始条件：如数据类型存储数据类型需要手动释放空间，则需传入自定义clear函数
* 操作结果：
* 1.单链表内部节点被释放
* 2.单链表头节点长度更改
*/
void ClearLinkList(LinkList&);
void ClearLinkList(LinkList& L, bool (*clear)(element&));

/*
* 摧毁单链表
* 操作要求：单链表存在
* 初始条件：如数据类型存储数据类型需要手动释放空间，则需传入自定义clear函数
* 操作结果：
* 1.单链表内部节点被释放
* 2.单链表头节点长度更改
* 3.释放头节点
*/
void DeleteLinkList(LinkList&);
void DeleteLinkList(LinkList&, bool (*clear)(element&));

/*
* 头插法插入数据对象到单链表
* 初始条件：单链表存在
* 操作结果：将数据对象插入到第一个位置,返回插入结果
*/
bool InsFirst(LinkList& L, element e);

/*
* 尾插法插入数据对象到单链表
* 初始条件：单链表存在
* 操作结果：将数据对象插入到第最后一个位置,返回插入结果
*/
bool InsLast(LinkList& L, element e);

/*
* 查找第pos个节点的值
* 初始条件：单链表存在，节点存在
* 操作结果：将查找值给引用对象e返回，函数返回查找结果状态。
*
*/
bool GetElem(LinkList L, int pos, element& e);

/*
* 取下链表的最后一个节点
* 初始条件：单链表存在，存在尾节点，L->next ！= NULL
* 操作结果：删除单链表的最后一个节点并以q返回
*/
bool Remove(LinkList& L, LNode* q, bool (*clear)(LinkList&));

/*
* 将两个链表链接到一起
* 初始条件：两个单链表存在
* 操作结果：将第二个链表连接到第一个链表的最后，并销毁第二个链表的头节点
*/
bool Append(LinkList& fir, LinkList& sec);

/*
* 返回链表中元素的个数
*/
int GetLength(LinkList L);

/*
*
*/
LinkList LocateElem(LinkList P, element data, bool (*compare)(element f, element s));

//===========================================================================多项式

typedef LinkList ploynomial;
//- - - - - - - - - -基础操作函数定义- - - - - - - - - - - -.



/*
* 输入m项的系数和指数，建立表示一元多项式的有序链表P；
*/
void CreatPolyn(ploynomial& P, int m);

//销毁一元多项式
void DeletePolyn(ploynomial& P);

//打印一元多项式
void PrintPolyn(ploynomial P);

//一元多项式加法,并销毁p2表
/*
* 初始条件：传入的两表不能相同
* 时间复杂度(记p1长度为n， p2长度为m)：
* 1.当Min(p1) > Max(p2) =======> O(m)
* 2.当Max(p1) < Min(p2) =======> O(n)
* 3.否则结果             =======> O(n + m)
*/
void addPolyn(ploynomial& p1, ploynomial& p2);

//一元多项式减法，并销毁B表。
/*
* 初始条件：传入的两表不能相同
* 时间复杂度(记p1长度为n， p2长度为m)：
* 1.当Min(p1) > Max(p2) =======> O(m)
* 2.当Max(p1) < Min(p2) =======> O(n)
* 3.否则结果             =======> O(n + m)
*/
void SubtractPolyn(ploynomial& A, ploynomial& B);

//一元多项式乘法, 并销毁B表。
//初始条件：传入的两表不能相同
void MultiplyPolyn(ploynomial& A, ploynomial& B);