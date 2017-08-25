#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>


//#include "test1.h"
using namespace std;


struct IntList {
    int value;
    IntList * next;
};

int solution(IntList * L) {
	if(L->next == NULL)
		return 1;
	return 1+ solution(L->next);
}
int main()
{

	IntList *a , *b, * c, *d;
	
	d = (IntList *) malloc (sizeof (IntList));
	d->next = NULL;
	d->value = 4;

	c = (IntList *) malloc (sizeof (IntList));
	c->next = d;
	c->value = 3;
	
	b = (IntList *) malloc (sizeof (IntList));
	b->next = c;
	b->value = 2;

	a = (IntList *) malloc (sizeof (IntList));
	a->next = b;
	a->value = 1;


	cout <<"length is : "<<  solution(a) << endl;
   return 0;
}