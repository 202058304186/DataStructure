#include "DataCollection.h"
#include <iostream>

#ifdef _DEBUG
#define New   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
using namespace std;

//���庯����
inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
//�ú������Է���������������λ�ã�������ȷ�Ĵ����ڴ�й¶���


int main(void) {

	//SqList A;
	//InitSqList(A);
	//SqListInsert(A, 1, 2);

	//SqList B;
	//InitSqList(B);
	//SqListInsert(B, 1, 1);
	//SqListInsert(B, 2, 2);
	//SqListInsert(B, 3, 3);
	//SqListInsert(B, 4, 4);
	//SqListInsert(B, 5, 5);
	//SqListInsert(B, 6, 6);

	////�鲢��������
	//SqList C;
	//MergeSqList(A, B, C);
	//for (int i = 0; i < C.length; ++i) {
	//	cout << C.data[i] << '\t';
	//}
	//cout << endl;

	////���ϡȲ���
	//Union(A, B);
	//for (int i = 0; i < A.length; ++i) {
	//	cout << A.data[i] << '\t';
	//}
	//cout << endl;

	////ɾ��Ԫ�ع��ܲ�ʽ
	//element e;
	//SqListDelete(A, 1, e);
	//cout << "e:" << e << endl;
	//SqListDelete(A, 1, e);
	//cout << "e:" << e << endl;


	//DeleteSqList(C);
	//DeleteSqList(A);
	//DeleteSqList(B);

	/*��������Խ׶�*/
	/*LinkList L;
	InitLinkList(L);
	InsFirst(L, 5);
	InsFirst(L, 5);
	LinkList L2;
	InitLinkList(L2);
	InsFirst(L2, 4);
	InsFirst(L2, 4);
	Append(L, L2);
	LNode z;
	Remove(L, &z, NULL);
	DeleteLinkList(L);*/

	
	ploynomial A;
	CreatPolyn(A, 4);
	PrintPolyn(A);

	ploynomial B;
	CreatPolyn(B, 3);
	PrintPolyn(B);
	ploynomial B_COPY;
	CreatPolyn(B_COPY, 3);
	PrintPolyn(B_COPY);
	ploynomial B_COPY_;
	CreatPolyn(B_COPY_, 3);
	PrintPolyn(B_COPY_);

	addPolyn(A, B);
	PrintPolyn(A);

	SubtractPolyn(A, B_COPY);
	PrintPolyn(A);

	MultiplyPolyn(A, B_COPY_);
	PrintPolyn(A);

	DeletePolyn(A);
	fflush(stdin);
	
	EnableMemLeakCheck();
	return 0;
	
}