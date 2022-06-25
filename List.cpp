#include "DataCollection.h"
#include <iostream>
using namespace std;

/*
初始化一个线性表
无要求，将会返回一个初始化结果。
*/
bool InitSqList(SqList &L) {
	L.data = (element*)malloc(sizeof(element) * LIST_INIT_SIZE);
	if (!L.data) exit(OVERFLOW);//检测内存分配，查看是否还有内存空间
	L.length = 0;
	L.maxSize = LIST_INIT_SIZE;
	return true;
}

/*
清除一个线性表
要求线性表存在，将会返回一个清除结果。
这个函数会将释放线性表内部值，将线性表置为空表。
*/
bool ClearSqList(SqList& L) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return false;
	}
	free((void*)L.data);
	L.length = 0;
	L.maxSize = LIST_INIT_SIZE;
	L.data = (element*)malloc(sizeof(element) * L.maxSize);
	return L.data;
}


/*
摧毁一个线性表
要求线性表存在，将会返回一个摧毁结果。
这个函数会彻底释放线性表所占空间
*/
bool DeleteSqList(SqList& L) {
	if (!L.data) {
		cout << "线性表未经初始化。";
		return false;
	}
	free(L.data);
	L.data = NULL;
	L.length = 0;
	L.maxSize = 0;
	return true;
}

/*
判断一个线性表是否为空
要求线性表存在，如果为空表会返回ture，否则返回false
*/
bool SqListEmpty(SqList L) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return false;
	}
	return !L.length;
}


/*
获取一个线性表的长度
要求线性表存在，返回线性表长度。
*/
int SqListLength(SqList L) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return -1;
	}
	return L.length;
}


/*
* 获取线性表L内第pos个元素的值
* 初始条件：要求线性表存在，位置在定义域内:1 ≤ pos ≤ SqListLength(L)。
* 返回结果：通过引用的元素对象e返回值，函数返回结果。
*/
bool GetElem(SqList L, int pos, element& e) {
	if (!L.data || pos < 1 || pos > SqListLength(L)) {
		cout << "线性表未经初始化或获取位置非法。";
		return false;
	}
	e = L.data[pos - 1];
	return true;
}


/*
* 初始条件：线性表已存在，compare()是数据元素判断函数
* 操作结果：返回L中第一个与e满足判定函数的数据元素的逻辑位置，若这样的元素不存在，则返回0;
*/
int LocateElem(SqList L, element e, int Compare(int, int)) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return false;
	}
	for (int i = 0; i < SqListLength(L); ++i) {
		if (Compare(e, L.data[i]) == 0) {
			return i + 1;
		}
	}
	return 0;
}


/*
* 获取前驱元素
* 初始条件：线性表存在
* 操作结果：若cur_e是L的元素，且不是第一个元素，则用pre_e返回，否则操作失败，pre_e未定义。
*/
bool PriorElem(SqList L, element cur_e, element &pre_e) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return false;
	}
	for (int i = 2; i < SqListLength(L); ++i) {
		if (cur_e == L.data[i]) {
			pre_e = L.data[i - 1];
			return true;
		}
	}
	return false;
}

/*
* 获取后驱元素
* 初始条件：线性表存在
* 操作结果：若cur_e是L的元素，且不是最后个元素，则用pre_e返回，否则操作失败，pre_e未定义。
*/
bool NextElem(SqList L, element cur_e, element& next_e) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return false;
	}
	for (int i = SqListLength(L) - 2; i >= 0; --i) {
		if (cur_e == L.data[i]) {
			next_e = L.data[i + 1];
			return true;
		}
	}
	return false;
}

/*
* 在线性表插入一个值
* 初始条件：线性表已经存在, 1 ≤ pos ≤ SqListLength(L)
* 操作结果：在L中的第pos个位置之前插入新的数据元素data，L的长度加1
*/
bool SqListInsert(SqList& L, int pos, element data) {
	if (!L.data || pos < 1 || pos > L.length + 1) {
		cout << "线性表未经初始化或获取位置非法。";
		return false;
	}//初始条件
	if (L.length >= L.maxSize) {
		element* newbase = (element*)realloc(L.data, sizeof(element) 
			* ((long long)L.maxSize + LISTINCREMENT));//动态内存再分配
		if (!newbase) exit(OVERFLOW);//溢出空值
		L.data = newbase;//移动到新基址
		L.maxSize += LISTINCREMENT;//最大长度增长
	}

	element* q = &(L.data[pos - 1]); //q为目标位置
	for (element* p = &(L.data[L.length - 1]); p >= q; --p) {
		*(p + 1) = *p;
	};//移动从第pos个位置开始之后的元素
	L.length++;
	*q = data;//为pos位置赋值
	cout << *q << endl;
	return true;
}