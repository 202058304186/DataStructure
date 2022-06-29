#pragma once
/*
* ========================================================================LinkList
* ������
*/


typedef struct term {
	float coef; //ϵ��
	int expn;//ָ��
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

//�������������Ա��ʼֵ
#define element term
/*
* ���Թ�Լ��
* element dataΪ�������������
* nextָ��ָ����һ�ڵ�λ�ã��������һ�ڵ���Ϊ�ա�
* �涨ͷ����������洢�������ȡ�
*/
typedef struct LNode {
	element data;
	struct LNode* next;
}LNode, * LinkList;

/*
* �ͷ�һ���ڵ�:��ָ����������ʱ������������
*/
void freeNode(LinkList p, bool (*clear)(LinkList& p));

/*
* ��ʼ��������
* ����Ҫ����
* ���������
* 1.��ʼ��ͷ�ڵ������򳤶�Ϊ0��
* 2.nextָ��ָ��NULL��
*/
void InitLinkList(LinkList&);

/*
* ��յ�����
* ����Ҫ�󣺵��������
* ��ʼ���������������ʹ洢����������Ҫ�ֶ��ͷſռ䣬���贫���Զ���clear����
* ���������
* 1.�������ڲ��ڵ㱻�ͷ�
* 2.������ͷ�ڵ㳤�ȸ���
*/
void ClearLinkList(LinkList&);
void ClearLinkList(LinkList& L, bool (*clear)(element&));

/*
* �ݻٵ�����
* ����Ҫ�󣺵��������
* ��ʼ���������������ʹ洢����������Ҫ�ֶ��ͷſռ䣬���贫���Զ���clear����
* ���������
* 1.�������ڲ��ڵ㱻�ͷ�
* 2.������ͷ�ڵ㳤�ȸ���
* 3.�ͷ�ͷ�ڵ�
*/
void DeleteLinkList(LinkList&);
void DeleteLinkList(LinkList&, bool (*clear)(element&));

/*
* ͷ�巨�������ݶ��󵽵�����
* ��ʼ���������������
* ��������������ݶ�����뵽��һ��λ��,���ز�����
*/
bool InsFirst(LinkList& L, element e);

/*
* β�巨�������ݶ��󵽵�����
* ��ʼ���������������
* ��������������ݶ�����뵽�����һ��λ��,���ز�����
*/
bool InsLast(LinkList& L, element e);

/*
* ���ҵ�pos���ڵ��ֵ
* ��ʼ��������������ڣ��ڵ����
* ���������������ֵ�����ö���e���أ��������ز��ҽ��״̬��
*
*/
bool GetElem(LinkList L, int pos, element& e);

/*
* ȡ����������һ���ڵ�
* ��ʼ��������������ڣ�����β�ڵ㣬L->next ��= NULL
* ���������ɾ������������һ���ڵ㲢��q����
*/
bool Remove(LinkList& L, LNode* q, bool (*clear)(LinkList&));

/*
* �������������ӵ�һ��
* ��ʼ�������������������
* ������������ڶ����������ӵ���һ���������󣬲����ٵڶ��������ͷ�ڵ�
*/
bool Append(LinkList& fir, LinkList& sec);

/*
* ����������Ԫ�صĸ���
*/
int GetLength(LinkList L);

/*
*
*/
LinkList LocateElem(LinkList P, element data, bool (*compare)(element f, element s));

//===========================================================================����ʽ

typedef LinkList ploynomial;
//- - - - - - - - - -����������������- - - - - - - - - - - -.



/*
* ����m���ϵ����ָ����������ʾһԪ����ʽ����������P��
*/
void CreatPolyn(ploynomial& P, int m);

//����һԪ����ʽ
void DeletePolyn(ploynomial& P);

//��ӡһԪ����ʽ
void PrintPolyn(ploynomial P);

//һԪ����ʽ�ӷ�,������p2��
/*
* ��ʼ�������������������ͬ
* ʱ�临�Ӷ�(��p1����Ϊn�� p2����Ϊm)��
* 1.��Min(p1) > Max(p2) =======> O(m)
* 2.��Max(p1) < Min(p2) =======> O(n)
* 3.������             =======> O(n + m)
*/
void addPolyn(ploynomial& p1, ploynomial& p2);

//һԪ����ʽ������������B��
/*
* ��ʼ�������������������ͬ
* ʱ�临�Ӷ�(��p1����Ϊn�� p2����Ϊm)��
* 1.��Min(p1) > Max(p2) =======> O(m)
* 2.��Max(p1) < Min(p2) =======> O(n)
* 3.������             =======> O(n + m)
*/
void SubtractPolyn(ploynomial& A, ploynomial& B);

//һԪ����ʽ�˷�, ������B��
//��ʼ�������������������ͬ
void MultiplyPolyn(ploynomial& A, ploynomial& B);