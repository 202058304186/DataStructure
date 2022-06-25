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
	free(L.data);
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
int LocateElem(SqList L, element e, int Compare(int, int)) {
	if (!L.data) {
		cout << "���Ա�δ����ʼ��";
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
* ��ȡǰ��Ԫ��
* ��ʼ���������Ա����
* �����������cur_e��L��Ԫ�أ��Ҳ��ǵ�һ��Ԫ�أ�����pre_e���أ��������ʧ�ܣ�pre_eδ���塣
*/
bool PriorElem(SqList L, element cur_e, element &pre_e) {
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
	cout << *q << endl;
	return true;
}