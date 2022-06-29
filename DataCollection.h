#pragma once
#include <cstddef>

/*
* ==========================================================================SqList
* �������Ա�
*/

typedef struct term{
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
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct SqList {
	element* data;
	int length;
	int maxSize;
}SqList;

/*
��ʼ��һ�����Ա�
��Ҫ�󣬽��᷵��һ����ʼ�������
*/
bool InitSqList(SqList &);

/*
���һ�����Ա�
Ҫ�����Ա���ڣ����᷵��һ����������
��������Ὣ�ͷ����Ա��ڲ�ֵ�������Ա���Ϊ�ձ�
*/
bool ClearSqList(SqList&);

/*
�ݻ�һ�����Ա�
Ҫ�����Ա���ڣ����᷵��һ���ݻٽ����
��������᳹���ͷ����Ա���ռ�ռ�
*/
/*���غ���
* �ݻ�һ�����Ա�����洢��������Ҫ�ֶ��ͷſռ�ʱ��
*/
bool DeleteSqList(SqList& L);

/*
* �ж�һ�����Ա��Ƿ�Ϊ��
* Ҫ�����Ա���ڣ����Ϊ�ձ�᷵��ture�����򷵻�false��
*/
bool SqListEmpty(SqList);

/*
* ��ȡһ�����Ա�ĳ���
* Ҫ�����Ա���ڣ��������Ա��ȡ�
*/
int SqListLength(SqList);

/*
* ��ȡ���Ա�ĳ��λ�õ�ֵ
* Ҫ�����Ա���ڣ�λ���ڶ������ڡ�
* ���ؽ����ͨ�����õ�Ԫ�ض���element&������
*/
bool GetElem(SqList, int, element&);

/*
* ��λ������������
* ��ʼ���������Ա��Ѵ��ڣ�compare()������Ԫ���жϺ���
* �������������L�е�һ����e�����ж�����������Ԫ�ص��߼�λ�ã���������Ԫ�ز����ڣ��򷵻�0;
*/
int LocateElem(SqList L, element e, bool (*Compare)(element, element) = NULL);

/*
* ��ȡǰ��Ԫ��
* ��ʼ���������Ա����
* �����������cur_e��L��Ԫ�أ��Ҳ��ǵ�һ��Ԫ�أ�����pre_e���أ��������ʧ�ܣ�pre_eδ���塣
*/
bool PriorElem(SqList L, element cur_e, element &pre_e);

/*
* ��ȡ����Ԫ��
* ��ʼ���������Ա����
* �����������cur_e��L��Ԫ�أ��Ҳ�������Ԫ�أ�����pre_e���أ��������ʧ�ܣ�pre_eδ���塣
*/
bool NextElem(SqList L, element cur_e, element& next_e);

/*
* �����Ա����һ��ֵ
* ��ʼ���������Ա��Ѿ�����, 1 �� pos �� SqListLength(L)
* �����������L�еĵ�pos��λ��֮ǰ�����µ�����Ԫ��data��L�ĳ��ȼ�1
*/
bool SqListInsert(SqList&, int pos, element data);

/*
* ɾ�����������Ա���ĳ��λ�õ�����
* ��ʼ���������Ա���ڣ�ɾ��λ�úϷ�
* ���ؽ����ɾ�����
*/
bool SqListDelete(SqList&, int pos, element& data);

/*
* ��������
* ���Ϻϲ��������Ա���һ�����Ա�
* ��ʼ���������Ա����ڣ�compare����Ϊ���ݴ�С����жϣ�Ĭ��ֵΪNULLʱ�����м򵥵����жϣ�==
* ������������������Ա�֮����м��ϡ����㣬����������һ�����Ա�
*/
void Union(SqList& first, SqList second, bool (*compare)(element, element) = NULL);


/*
* �������Ա�ϲ�
* �ϲ��������Ա�õ�Ҫ���µ����Ա�
* ��ʼ���������Ա����ڣ�compare����Ϊ���ݴ�С����жϣ�Ĭ��ֵΪNULLʱ�����м򵥵����жϣ�==
* ���������ֱ�Ӻϲ��������Ա���������һ���µ����Ա�
*/
void MergeSqList(SqList a, SqList b, SqList &c, 
	int (*compare)(element, element) = NULL);

/*
* ========================================================================LinkList
* ������
*/


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
void InitLinkList(LinkList &);

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
bool GetElem(LinkList L, int pos, element &e);

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
void CreatPolyn(ploynomial &P, int m);

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
void addPolyn(ploynomial &p1, ploynomial &p2);

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