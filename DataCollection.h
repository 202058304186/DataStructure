#pragma once
#include <cstddef>

/*
* ==========================================================================SqList
* 声明线性表
*/

typedef struct term{
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
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct SqList {
	element* data;
	int length;
	int maxSize;
}SqList;

/*
初始化一个线性表
无要求，将会返回一个初始化结果。
*/
bool InitSqList(SqList &);

/*
清除一个线性表
要求线性表存在，将会返回一个清除结果。
这个函数会将释放线性表内部值，将线性表置为空表。
*/
bool ClearSqList(SqList&);

/*
摧毁一个线性表
要求线性表存在，将会返回一个摧毁结果。
这个函数会彻底释放线性表所占空间
*/
/*重载函数
* 摧毁一个线性表，当其存储的数据需要手动释放空间时。
*/
bool DeleteSqList(SqList& L);

/*
* 判断一个线性表是否为空
* 要求线性表存在，如果为空表会返回ture，否则返回false。
*/
bool SqListEmpty(SqList);

/*
* 获取一个线性表的长度
* 要求线性表存在，返回线性表长度。
*/
int SqListLength(SqList);

/*
* 获取线性表某个位置的值
* 要求线性表存在，位置在定义域内。
* 返回结果：通过引用的元素对象（element&）返回
*/
bool GetElem(SqList, int, element&);

/*
* 定位符合条件函数
* 初始条件：线性表已存在，compare()是数据元素判断函数
* 操作结果：返回L中第一个与e满足判定函数的数据元素的逻辑位置，若这样的元素不存在，则返回0;
*/
int LocateElem(SqList L, element e, bool (*Compare)(element, element) = NULL);

/*
* 获取前驱元素
* 初始条件：线性表存在
* 操作结果：若cur_e是L的元素，且不是第一个元素，则用pre_e返回，否则操作失败，pre_e未定义。
*/
bool PriorElem(SqList L, element cur_e, element &pre_e);

/*
* 获取后驱元素
* 初始条件：线性表存在
* 操作结果：若cur_e是L的元素，且不是最后个元素，则用pre_e返回，否则操作失败，pre_e未定义。
*/
bool NextElem(SqList L, element cur_e, element& next_e);

/*
* 在线性表插入一个值
* 初始条件：线性表已经存在, 1 ≤ pos ≤ SqListLength(L)
* 操作结果：在L中的第pos个位置之前插入新的数据元素data，L的长度加1
*/
bool SqListInsert(SqList&, int pos, element data);

/*
* 删除并保存线性表中某个位置的数据
* 初始条件：线性表存在，删除位置合法
* 返回结果：删除结果
*/
bool SqListDelete(SqList&, int pos, element& data);

/*
* 集合运算
* 集合合并两个线性表到第一个线性表
* 初始条件：线性表都存在，compare函数为数据大小相等判断，默认值为NULL时，进行简单等于判断：==
* 操作结果：在两个线性表之间进行集合∪运算，保存结果到第一个线性表
*/
void Union(SqList& first, SqList second, bool (*compare)(element, element) = NULL);


/*
* 两个线性表合并
* 合并两个线性表得到要给新的线性表
* 初始条件：线性表都存在，compare函数为数据大小相等判断，默认值为NULL时，进行简单等于判断：==
* 操作结果：直接合并两个线性表，保存结果到一个新的线性表
*/
void MergeSqList(SqList a, SqList b, SqList &c, 
	int (*compare)(element, element) = NULL);

/*
* ========================================================================LinkList
* 单链表
*/


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
void InitLinkList(LinkList &);

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
bool GetElem(LinkList L, int pos, element &e);

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
void CreatPolyn(ploynomial &P, int m);

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
void addPolyn(ploynomial &p1, ploynomial &p2);

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