#ifdef  element term
#include"DataCollection.h"
#include <iostream>
#else
#include"Ploynomial.h"
#include<iostream>
#endif //  element term
using namespace std;



//- - - - - - - - - -基础操作函数实现- - - - - - - - - - - -
/*
* 该函数在CreatPolyn中调用，用于找到创建多项式时的有序位置
* 第一个位置参数是单链表中的节点的数据域，后面为待插入节点数据域
* 操作结果：判定单链表节点的指数是否大于待插入节点的数据域，如果是则返回ture，否则返回false;
*/
bool compare(element f, const element s) {
	return f.expn > s.expn;
}
/*
* 输入m项的系数和指数，建立表示一元多项式的有序链表P；
*/
void CreatPolyn(ploynomial& P, int m) {
	InitLinkList(P);
	P->data.expn = INT_MIN;
	for (int i = 0; i < m; ++i) {
		term data;//定义数据结构体：系数指数结构体
		cout << "请输入系数：";
		cin >> data.coef;
		cout << "请输入指数：";
		cin >> data.expn;
		cout << "============endl" << endl;
		//打印输入框体
		LinkList pos = LocateElem(P, data, compare);//pos为插入位置

		if (pos) {
			ploynomial q = (LinkList)malloc(sizeof(LNode));
			if (!q) { exit(OVERFLOW); }
			q->data = data;
			q->next = pos->next;
			pos->next = q;
		}//如果位置为某一结点，则插入到该节点后
		else {
			InsLast(P, data);
		}//如果位置为NULL，则说明插入的元素指数最大
	}
}

//销毁一元多项式
void DeletePolyn(ploynomial& P) {
	DeleteLinkList(P);
}

//打印一元多项式
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

//一元多项式加法
void addPolyn(ploynomial& p1, ploynomial& p2) {
	if (p1 == p2) {
		cout << "\nA和B多项式不能是同一个，请将它的深拷贝作为第二个参数传入，"
			"或者调用非原地方法。\n";
		return;
	}
	/*
	* 利用归并算法的思想：p1、p2都是有序的
	*/
	ploynomial lpre = p1;//第一个多项式的前项
	ploynomial r = p2->next;//第二个多项式的当前项

	while (lpre->next && r) {
		if (lpre->next->data.expn < r->data.expn) {
			lpre = lpre->next;
		}
		else if (lpre->next->data.expn == r->data.expn) {
			lpre->next->data.coef += r->data.coef;//合并
			if (lpre->next->data.coef) {
				ploynomial cur = r;//保存第二多项式当前项
				r = r->next;//移动第二个多项式的指针
				free(cur);//释放当前项；
				lpre = lpre->next;//移动第一个多项式的前项指针
			}//如果系数非0，则插入
			else {
				ploynomial cur1 = lpre->next;//保存第一多项式当前项
				ploynomial cur2 = r;//保存第二多项式当前项
				r = r->next;//移动
				lpre->next = lpre->next->next;//移动
				//释放
				free(cur1);
				free(cur2);
			}//否则则将两个节点取消
		}
		else {
			ploynomial cur = r;//保存第二多项式当前项
			r = r->next;//移动第二个多项式的指针
			cur->next = lpre->next;
			lpre->next = cur;//插入第二个多项式到第一个多项式
		}
	}
	if (r) {
		lpre->next = r;
	}
	free(p2);//释放第二个多项式头节点
}

//一元多项式减法
void SubtractPolyn(ploynomial& A, ploynomial& B) {
	/*
	* 利用归并算法的思想：p1、p2都是有序的
	*/
	if (A == B) {
		cout << "\nA和B多项式不能是同一个，请将它的深拷贝作为第二个参数传入，"
			"或者调用非原地方法。\n";
		return;
	}
	ploynomial pA = A;//第一个多项式的前项
	ploynomial r = B->next;//第二个多项式的当前项

	while (pA->next && r) {
		if (pA->next->data.expn < r->data.expn) {
			pA = pA->next;
		}
		else if (pA->next->data.expn == r->data.expn) {
			pA->next->data.coef -= r->data.coef;//合并
			if (pA->next->data.coef) {
				ploynomial cur = r;//保存第二多项式当前项
				r = r->next;//移动第二个多项式的指针
				free(cur);//释放当前项；
				pA = pA->next;//移动第一个多项式的前项指针
			}//如果系数非0，则插入
			else {
				ploynomial cur1 = pA->next;//保存第一多项式当前项
				ploynomial cur2 = r;//保存第二多项式当前项
				r = r->next;//移动
				pA->next = pA->next->next;//移动
				//释放
				free(cur1);
				free(cur2);
			}//否则则将两个节点取消
		}
		else {
			ploynomial cur = r;//保存第二多项式当前项
			cur->data.coef *= -1;
			r = r->next;//移动第二个多项式的指针
			cur->next = pA->next;
			pA->next = cur;//插入第二个多项式到第一个多项式
		}
	}
	if (r) {
		pA->next = r;
	}
	free(B);//释放第二个多项式头节点
}

//一元多项式乘法
void MultiplyPolyn(ploynomial& A, ploynomial& B) {
	if (A == B) {
		cout << "\nA和B多项式不能是同一个，请将它的深拷贝作为第二个参数传入，"
			"或者调用非原地方法。\n";
		return;
	}
	//A * B = Σ(n, i=1) bi * A(x) * x ^ e ^ i;
	ploynomial cur = B->next;//cur: B中有效当前运算节点，相当于公式中的i

	int ALen = GetLength(A);//获取A多项式长度

	term* terms = (term*)malloc(sizeof(term) * ALen);
	//用于存放被原地修改的A中的值
	if (!terms) { exit(OVERFLOW); }

	ploynomial terms_A = A->next;//用于遍历A多项式，同时释放遍历过的节点
	A->next = NULL;
	for (int i = 0; i < ALen; ++i) {
		(terms + i)->coef = terms_A->data.coef;
		(terms + i)->expn = terms_A->data.expn;
		ploynomial fre = terms_A;
		terms_A = terms_A->next;
		free(fre);
	}//存放被原地修改的A中的值到terms数组
	free(terms_A);
	
	while (cur) {
		if (fabs(cur->data.coef - 0) <= 0.000001) {
			cur = cur->next;
		}//当B的系数为0时, 判定其当前累加项值一定为0，所以不用添加
		else {
			ploynomial res;//暂存cur * A的结果
			InitLinkList(res);

			float coef = cur->data.coef;
			int expn = cur->data.expn;

			for (int i = 0; i < ALen; ++i) {
				term a;
				a.coef = terms[i].coef * coef;
				a.expn = terms[i].expn + expn;
				InsLast(res, a);
			}//从terms数组中读值，运算后得到每个分结果
			addPolyn(A, res);//累加分结果

			ploynomial fre = cur;
			cur = cur->next;//运算下一个
			free(fre);
		}
	}

	free(B);
	free(terms);
}