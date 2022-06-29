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
* ��ʼ��������
* ����Ҫ����
* ���������
* 1.��ʼ��ͷ�ڵ������򳤶�Ϊ0��
* 2.nextָ��ָ��NULL��
*/
void InitLinkList(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) exit(OVERFLOW);
	L->next = NULL;//��ָ������ΪNULL
}

/*
* ��յ�����
* ����Ҫ�󣺵��������
* ��ʼ���������������ʹ洢����������Ҫ�ֶ��ͷſռ䣬���贫���Զ���clear����
* ���������
* 1.�������ڲ��ڵ㱻�ͷ�
* 2.�޸�ָ����
*/
void ClearLinkList(LinkList& L) {
	if (!L) {
		cout << "�����ͷſ�ָ�룡" << endl;
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
		cout << "�����ͷſ�ָ�룡" << endl;
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
* �ݻٵ�����
* ����Ҫ�󣺵��������
* ��ʼ���������������ʹ洢����������Ҫ�ֶ��ͷſռ䣬���贫���Զ���clear����
* ���������
* 1.�������ڲ��ڵ㱻�ͷ�
* 2.������ͷ�ڵ㳤�ȸ���
* 3.�ͷ�ͷ�ڵ�
*/
void DeleteLinkList(LinkList& L) {
	if (!L) {
		cout << "�����ͷſ�ָ�룡" << endl;
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
		cout << "�����ͷſ�ָ�룡" << endl;
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
* ͷ�巨�������ݶ��󵽵�����
* ��ʼ���������������
* ��������������ݶ�����뵽��һ��λ��,���ز�����
* ʱ�临�Ӷȣ�O(1)
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
* β�巨�������ݶ��󵽵�����
* ��ʼ���������������
* ��������������ݶ�����뵽�����һ��λ��,���ز�����
* ʱ�临�Ӷ�O(N)
*/
bool InsLast(LinkList& L, element e) {
	LinkList p = L;
	while (p->next) {
		p = p->next;
	}//�ҵ����һ���ڵ�
	LinkList node = (LinkList)malloc(sizeof(LNode));
	if (!node) exit(OVERFLOW);
	node->data = e;
	node->next = NULL;
	p->next = node;
	return true;
}

/*
* ���ҵ�pos���ڵ��ֵ
* ��ʼ��������������ڣ��ڵ����
* ���������������ֵ�����ö���e���أ��������ز��ҽ��״̬��
*
*/
bool GetElem(LinkList L, int pos, element* e) {
	LinkList p = L->next;//������ & ������
	while (p && pos-- > 1) {
		p = p->next;
	}//�ҵ������Ӧλ�õĽڵ�
	e = p == NULL ? NULL : &p->data;//��������������e����
	return p;//����ִ�н��
}


/*
* ȡ����������һ���ڵ�
* ��ʼ��������������ڣ�����β�ڵ㣬L->next ��= NULL
* ���������ɾ������������һ���ڵ㲢��q����
* ����ϸ�ڣ����ҽ����Զ���Ԫ��Ϊջ������ʱ��������ָ��������������Ҫָ����������
*/
bool Remove(LinkList& L, LNode* q, bool (* clear)(LinkList&)) {
	if (!L->next) {
		return false;
	}
	LinkList pre = L;//��¼��һ���
	LinkList p = L->next;//��¼β�ڵ�
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
* �������������ӵ�һ��
* ��ʼ�������������������
* ������������ڶ����������ӵ���һ���������󣬲����ٵڶ��������ͷ�ڵ�
* ʱ�临�Ӷ�O��1��
*/
bool Append(LinkList& fir, LinkList& sec) {
	if (fir == NULL) {
		cout << "��һ��������Ϊ�ա�" << endl;
		return false;
	}
	//�ҵ���һ�������β��
	LinkList p = fir;
	while (p->next) {
		p = p->next;
	}
	//����
	p->next = sec->next;
	//�ͷ�
	free(sec);
	sec = NULL;
	return true;
}

/*
* ������������L�е�1����e���㺯��compare�ж���ϵ��Ԫ��λ��
* ��ʼ���������Ա���ڣ�Ԫ��e�Ϸ����ж���ϵ�Զ���
* ��������������������򷵻ؽڵ㣬�����㷵��NULL
*/
LinkList LocateElem(LinkList L, element e, 
	bool (*compare)(element f, element s)) {
	LinkList p = L;//�ڵ�ָ��
	while (p->next) {
		if (compare(p->next->data, e)) { return p; }
		p = p->next;
	}
	return NULL;
}

/*
* ����������Ԫ�صĸ���
*/
int GetLength(LinkList L) {
	int x = 0;
	while (L->next) {
		L = L->next;
		x++;
	}
	return x;
}