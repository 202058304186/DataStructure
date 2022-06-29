#ifdef  element term
#include"DataCollection.h"
#include <iostream>
#else
#include"Ploynomial.h"
#include<iostream>
#endif //  element term
using namespace std;



//- - - - - - - - - -������������ʵ��- - - - - - - - - - - -
/*
* �ú�����CreatPolyn�е��ã������ҵ���������ʽʱ������λ��
* ��һ��λ�ò����ǵ������еĽڵ�������򣬺���Ϊ������ڵ�������
* ����������ж�������ڵ��ָ���Ƿ���ڴ�����ڵ��������������򷵻�ture�����򷵻�false;
*/
bool compare(element f, const element s) {
	return f.expn > s.expn;
}
/*
* ����m���ϵ����ָ����������ʾһԪ����ʽ����������P��
*/
void CreatPolyn(ploynomial& P, int m) {
	InitLinkList(P);
	P->data.expn = INT_MIN;
	for (int i = 0; i < m; ++i) {
		term data;//�������ݽṹ�壺ϵ��ָ���ṹ��
		cout << "������ϵ����";
		cin >> data.coef;
		cout << "������ָ����";
		cin >> data.expn;
		cout << "============endl" << endl;
		//��ӡ�������
		LinkList pos = LocateElem(P, data, compare);//posΪ����λ��

		if (pos) {
			ploynomial q = (LinkList)malloc(sizeof(LNode));
			if (!q) { exit(OVERFLOW); }
			q->data = data;
			q->next = pos->next;
			pos->next = q;
		}//���λ��Ϊĳһ��㣬����뵽�ýڵ��
		else {
			InsLast(P, data);
		}//���λ��ΪNULL����˵�������Ԫ��ָ�����
	}
}

//����һԪ����ʽ
void DeletePolyn(ploynomial& P) {
	DeleteLinkList(P);
}

//��ӡһԪ����ʽ
void PrintPolyn(ploynomial P) {
	ploynomial next = P->next;
	cout << "y = ";
	while (next) {
		cout << next->data.coef << "*x^" << next->data.expn;
		if (next->next) cout << " + ";
		next = next->next;
	}
	cout << endl;
}

//һԪ����ʽ�ӷ�
void addPolyn(ploynomial& p1, ploynomial& p2) {
	if (p1 == p2) {
		cout << "\nA��B����ʽ������ͬһ�����뽫���������Ϊ�ڶ����������룬"
			"���ߵ��÷�ԭ�ط�����\n";
		return;
	}
	/*
	* ���ù鲢�㷨��˼�룺p1��p2���������
	*/
	ploynomial lpre = p1;//��һ������ʽ��ǰ��
	ploynomial r = p2->next;//�ڶ�������ʽ�ĵ�ǰ��

	while (lpre->next && r) {
		if (lpre->next->data.expn < r->data.expn) {
			lpre = lpre->next;
		}
		else if (lpre->next->data.expn == r->data.expn) {
			lpre->next->data.coef += r->data.coef;//�ϲ�
			if (lpre->next->data.coef) {
				ploynomial cur = r;//����ڶ�����ʽ��ǰ��
				r = r->next;//�ƶ��ڶ�������ʽ��ָ��
				free(cur);//�ͷŵ�ǰ�
				lpre = lpre->next;//�ƶ���һ������ʽ��ǰ��ָ��
			}//���ϵ����0�������
			else {
				ploynomial cur1 = lpre->next;//�����һ����ʽ��ǰ��
				ploynomial cur2 = r;//����ڶ�����ʽ��ǰ��
				r = r->next;//�ƶ�
				lpre->next = lpre->next->next;//�ƶ�
				//�ͷ�
				free(cur1);
				free(cur2);
			}//�����������ڵ�ȡ��
		}
		else {
			ploynomial cur = r;//����ڶ�����ʽ��ǰ��
			r = r->next;//�ƶ��ڶ�������ʽ��ָ��
			cur->next = lpre->next;
			lpre->next = cur;//����ڶ�������ʽ����һ������ʽ
		}
	}
	if (r) {
		lpre->next = r;
	}
	free(p2);//�ͷŵڶ�������ʽͷ�ڵ�
}

//һԪ����ʽ����
void SubtractPolyn(ploynomial& A, ploynomial& B) {
	/*
	* ���ù鲢�㷨��˼�룺p1��p2���������
	*/
	if (A == B) {
		cout << "\nA��B����ʽ������ͬһ�����뽫���������Ϊ�ڶ����������룬"
			"���ߵ��÷�ԭ�ط�����\n";
		return;
	}
	ploynomial pA = A;//��һ������ʽ��ǰ��
	ploynomial r = B->next;//�ڶ�������ʽ�ĵ�ǰ��

	while (pA->next && r) {
		if (pA->next->data.expn < r->data.expn) {
			pA = pA->next;
		}
		else if (pA->next->data.expn == r->data.expn) {
			pA->next->data.coef -= r->data.coef;//�ϲ�
			if (pA->next->data.coef) {
				ploynomial cur = r;//����ڶ�����ʽ��ǰ��
				r = r->next;//�ƶ��ڶ�������ʽ��ָ��
				free(cur);//�ͷŵ�ǰ�
				pA = pA->next;//�ƶ���һ������ʽ��ǰ��ָ��
			}//���ϵ����0�������
			else {
				ploynomial cur1 = pA->next;//�����һ����ʽ��ǰ��
				ploynomial cur2 = r;//����ڶ�����ʽ��ǰ��
				r = r->next;//�ƶ�
				pA->next = pA->next->next;//�ƶ�
				//�ͷ�
				free(cur1);
				free(cur2);
			}//�����������ڵ�ȡ��
		}
		else {
			ploynomial cur = r;//����ڶ�����ʽ��ǰ��
			cur->data.coef *= -1;
			r = r->next;//�ƶ��ڶ�������ʽ��ָ��
			cur->next = pA->next;
			pA->next = cur;//����ڶ�������ʽ����һ������ʽ
		}
	}
	if (r) {
		pA->next = r;
	}
	free(B);//�ͷŵڶ�������ʽͷ�ڵ�
}

//һԪ����ʽ�˷�
void MultiplyPolyn(ploynomial& A, ploynomial& B) {
	if (A == B) {
		cout << "\nA��B����ʽ������ͬһ�����뽫���������Ϊ�ڶ����������룬"
			"���ߵ��÷�ԭ�ط�����\n";
		return;
	}
	//A * B = ��(n, i=1) bi * A(x) * x ^ e ^ i;
	ploynomial cur = B->next;//cur: B����Ч��ǰ����ڵ㣬�൱�ڹ�ʽ�е�i

	int ALen = GetLength(A);//��ȡA����ʽ����

	term* terms = (term*)malloc(sizeof(term) * ALen);
	//���ڴ�ű�ԭ���޸ĵ�A�е�ֵ
	if (!terms) { exit(OVERFLOW); }

	ploynomial terms_A = A->next;//���ڱ���A����ʽ��ͬʱ�ͷű������Ľڵ�
	A->next = NULL;
	for (int i = 0; i < ALen; ++i) {
		(terms + i)->coef = terms_A->data.coef;
		(terms + i)->expn = terms_A->data.expn;
		ploynomial fre = terms_A;
		terms_A = terms_A->next;
		free(fre);
	}//��ű�ԭ���޸ĵ�A�е�ֵ��terms����
	free(terms_A);
	
	while (cur) {
		if (fabs(cur->data.coef - 0) <= 0.000001) {
			cur = cur->next;
		}//��B��ϵ��Ϊ0ʱ, �ж��䵱ǰ�ۼ���ֵһ��Ϊ0�����Բ������
		else {
			ploynomial res;//�ݴ�cur * A�Ľ��
			InitLinkList(res);

			float coef = cur->data.coef;
			int expn = cur->data.expn;

			for (int i = 0; i < ALen; ++i) {
				term a;
				a.coef = terms[i].coef * coef;
				a.expn = terms[i].expn + expn;
				InsLast(res, a);
			}//��terms�����ж�ֵ�������õ�ÿ���ֽ��
			addPolyn(A, res);//�ۼӷֽ��

			ploynomial fre = cur;
			cur = cur->next;//������һ��
			free(fre);
		}
	}

	free(B);
	free(terms);
}