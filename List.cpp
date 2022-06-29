#include "DataCollection.h"
#include <iostream>
using namespace std;
/*
��ʼ��һ�����Ա�
��Ҫ�󣬽��᷵��һ����ʼ�������
*/
bool InitSqList(SqList &L) {
	L.data = (element*)malloc(sizeof(element) * LIST_INIT_SIZE);
	if (!L.data) exit(OVERFLOW);//����ڴ���䣬�鿴�Ƿ����ڴ�ռ�
	L.length = 0;
	L.maxSize = LIST_INIT_SIZE;
	return true;
}

/*
���һ�����Ա�
Ҫ�����Ա���ڣ����᷵��һ����������
��������Ὣ�ͷ����Ա��ڲ�ֵ�������Ա���Ϊ�ձ�
*/
bool ClearSqList(SqList& L) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
		return false;
	}
	free((void*)L.data);
	L.length = 0;
	L.maxSize = LIST_INIT_SIZE;
	L.data = (element*)malloc(sizeof(element) * L.maxSize);
	return L.data;
}


/*
�ݻ�һ�����Ա�
Ҫ�����Ա���ڣ����᷵��һ���ݻٽ����
��������᳹���ͷ����Ա���ռ�ռ�
*/
bool DeleteSqList(SqList& L) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ����";
		return false;
	}
	free((void *)L.data);
	L.data = NULL;
	L.length = 0;
	L.maxSize = 0;
	return true;
}

/*
�ж�һ�����Ա��Ƿ�Ϊ��
Ҫ�����Ա���ڣ����Ϊ�ձ�᷵��ture�����򷵻�false
*/
bool SqListEmpty(SqList L) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
		return false;
	}
	return !L.length;
}


/*
��ȡһ�����Ա�ĳ���
Ҫ�����Ա���ڣ��������Ա��ȡ�
*/
int SqListLength(SqList L) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
		return -1;
	}
	return L.length;
}


/*
* ��ȡ���Ա�L�ڵ�pos��Ԫ�ص�ֵ
* ��ʼ������Ҫ�����Ա���ڣ�λ���ڶ�������:1 �� pos �� SqListLength(L)��
* ���ؽ����ͨ�����õ�Ԫ�ض���e����ֵ���������ؽ����
*/
bool GetElem(SqList L, int pos, element& e) {
	if (!L.data || pos < 1 || pos > SqListLength(L)) {
		cout << pos << endl;

		cout << "���Ա�δ����ʼ�����ȡλ�÷Ƿ���";
		return false;
	}
	e = L.data[pos - 1];
	return true;
}


/*
* ��ʼ���������Ա��Ѵ��ڣ�compare()������Ԫ���жϺ���
* �������������L�е�һ����e�����ж�����������Ԫ�ص��߼�λ�ã���������Ԫ�ز����ڣ��򷵻�0;
*/
int LocateElem(SqList L, element e, bool (*Compare)(element, element)) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
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
* ��ȡǰ��Ԫ��
* ��ʼ���������Ա����
* �����������cur_e��L��Ԫ�أ��Ҳ��ǵ�һ��Ԫ�أ�����pre_e���أ��������ʧ�ܣ�pre_eδ���塣
*/
bool PriorElem(SqList L, element cur_e, element& pre_e) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
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
* ��ȡ����Ԫ��
* ��ʼ���������Ա����
* �����������cur_e��L��Ԫ�أ��Ҳ�������Ԫ�أ�����pre_e���أ��������ʧ�ܣ�pre_eδ���塣
*/
bool NextElem(SqList L, element cur_e, element& next_e) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
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
* �����Ա����һ��ֵ
* ��ʼ���������Ա��Ѿ�����, 1 �� pos �� SqListLength(L)
* �����������L�еĵ�pos��λ��֮ǰ�����µ�����Ԫ��data��L�ĳ��ȼ�1
*/
bool SqListInsert(SqList& L, int pos, element data) {
	if (!L.data || pos < 1 || pos > L.length + 1) {
		cout << "���Ա�δ����ʼ�����ȡλ�÷Ƿ���";
		return false;
	}//��ʼ����

	if (L.length >= L.maxSize) {
		element* newbase = (element*)realloc(L.data, sizeof(element)
			* ((long long)L.maxSize + LISTINCREMENT));//��̬�ڴ��ٷ���
		if (!newbase) exit(OVERFLOW);//�����ֵ
		L.data = newbase;//�ƶ����»�ַ
		L.maxSize += LISTINCREMENT;//��󳤶�����
	}

	element* q = &(L.data[pos - 1]); //qΪĿ��λ��
	for (element* p = &(L.data[L.length - 1]); p >= q; --p) {
		*(p + 1) = *p;
	};//�ƶ��ӵ�pos��λ�ÿ�ʼ֮���Ԫ��
	L.length++;
	*q = data;//Ϊposλ�ø�ֵ
	return true;
}

/*
* ɾ�����������Ա���ĳ��λ�õ�����
* ��ʼ���������Ա���ڣ�ɾ��λ�úϷ�
* ���ؽ����ɾ�����
*/
bool SqListDelete(SqList& L, int pos, element& data) {
	if (!L.data || pos < 1 || pos > SqListLength(L)) {
		if(!L.data) {
			cout << "�޷�ɾ�������Ա����ڡ�";
		}
		else {
			cout << "�޷�ɾ����ɾ��λ�÷Ƿ���";
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
* ��������
* �ϲ��������Ա���һ�����Ա�
* ��ʼ���������Ա�����
* ������������������Ա�֮����м��ϡ����㣬����������һ�����Ա�
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
* �������Ա�ϲ�
* �ϲ��������Ա�õ�Ҫ���µ����Ա�
* ��ʼ���������Ա����ڣ�compare����Ϊ���ݴ�С����жϣ�Ĭ��ֵΪNULLʱ�����м򵥵����жϣ�==
* ���������ֱ�Ӻϲ��������Ա���������һ���µ����Ա�
*/
void MergeSqList(SqList a, SqList b, SqList& c,
	int (*compare)(element, element)) {
	element* pa = a.data;//��һ���������ָ��
	element* pb = b.data;//�ڶ����������ָ��
	element* pc;//�������������ָ��
	//ΪC�����ռ�
	c.length = c.maxSize = a.length + b.length;
	c.data = (element*)malloc(sizeof(element) * c.length);
	if (!c.data) exit(OVERFLOW);
	pc = c.data;

	//��ȡa��b��ı�ĩλ��
	element* pa_last = pa + a.length - 1;
	element* pb_last = pb + b.length - 1;
	int curror = 0;//�����ƶ����α�
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