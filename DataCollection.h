#pragma once
#define element int
/*
* �������Ա�
*/
typedef struct SqList{
	SqList* data;
	int length;
	int maxSize;
}SqList;


//�������������Ա��ʼֵ
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

/*
* =====================================================SqList
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
bool DeleteSqList(SqList&);

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
int LocateElem(SqList, element, int (int, int));

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