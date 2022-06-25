#pragma once
#define element int
/*
* 声明线性表
*/
typedef struct SqList{
	SqList* data;
	int length;
	int maxSize;
}SqList;


//声明并定义线性表初始值
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

/*
* =====================================================SqList
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
bool DeleteSqList(SqList&);

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
int LocateElem(SqList, element, int (int, int));

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