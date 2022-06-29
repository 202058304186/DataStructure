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
	free((void *)L.data);
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
		cout << pos << endl;

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
int LocateElem(SqList L, element e, bool (*Compare)(element, element)) {
	if (!L.data) {
		cout << "线性表未经初始化";
		return false;
	}
	if (Compare) {
		for (int i = 0; i < SqListLength(L); ++i) {
			if (Compare(e, L.data[i])) {
				return i + 1;
			}
		}
	}
	else {
		for (int i = 0; i < SqListLength(L); ++i) {
			if (e == L.data[i]) {
				return i + 1;
			}
		}
	}
	return 0;
}


/*
* 获取前驱元素
* 初始条件：线性表存在
* 操作结果：若cur_e是L的元素，且不是第一个元素，则用pre_e返回，否则操作失败，pre_e未定义。
*/
bool PriorElem(SqList L, element cur_e, element& pre_e) {
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
	return true;
}

/*
* 删除并保存线性表中某个位置的数据
* 初始条件：线性表存在，删除位置合法
* 返回结果：删除结果
*/
bool SqListDelete(SqList& L, int pos, element& data) {
	if (!L.data || pos < 1 || pos > SqListLength(L)) {
		if(!L.data) {
			cout << "无法删除：线性表不存在。";
		}
		else {
			cout << "无法删除：删除位置非法。";
		}
	}
	int length = SqListLength(L);
	
	element* start = &L.data[pos - 1];

	data = *start;
	element* end = L.data + length - 1;
	for (start; start < end; ++start) {
		*start = *(start + 1);
	}
	--L.length;
	return true;
}

/*
* 集合运算
* 合并两个线性表到第一个线性表
* 初始条件：线性表都存在
* 操作结果：在两个线性表之间进行集合∪运算，保存结果到第一个线性表
*/
void Union(SqList& first, SqList second, bool (* compare)(element, element)) {
	int LFirst = first.length, LSecond = second.length;
	for (int i = 1; i <= LSecond; ++i) {
		element e;
		GetElem(second, i, e);
		if (!LocateElem(first, e, compare)){
			SqListInsert(first, ++LFirst, e);
		}
	}
}

/*
* 两个线性表合并
* 合并两个线性表得到要给新的线性表
* 初始条件：线性表都存在，compare函数为数据大小相等判断，默认值为NULL时，进行简单等于判断：==
* 操作结果：直接合并两个线性表，保存结果到一个新的线性表
*/
void MergeSqList(SqList a, SqList b, SqList& c,
	int (*compare)(element, element)) {
	element* pa = a.data;//第一个表的数据指针
	element* pb = b.data;//第二个表的数据指针
	element* pc;//第三个表的数据指针
	//为C表分配空间
	c.length = c.maxSize = a.length + b.length;
	c.data = (element*)malloc(sizeof(element) * c.length);
	if (!c.data) exit(OVERFLOW);
	pc = c.data;

	//获取a、b表的表末位置
	element* pa_last = pa + a.length - 1;
	element* pb_last = pb + b.length - 1;
	int curror = 0;//控制移动的游标
	if (compare) {
		while (pa <= pa_last && pb <= pb_last) {
			if (compare(*pa, *pb) < 1) *pc++ = *pa++;
			else *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;
		while (pb <= pb_last) *pc++ = *pb++;
	}
	else {
		while (pa <= pa_last && pb <= pb_last) {
			if (*pa < *pb) *pc++ = *pa++;
			else *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;
		while (pb <= pb_last) *pc++ = *pb++;
	}
}