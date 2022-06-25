#include "DataCollection.h"
#include <iostream>
using namespace std;

int main(void) {

	for (int i = 0; i < 3; ++i) {
		SqList F;
		InitSqList(F);
		SqList a;
		InitSqList(a);
		SqListInsert(F, 1, a);
		SqList b;
		InitSqList(b);
		SqListInsert(F, 1, b);
		DeleteSqList(F);
	}
	return 0;
}