#include <stdio.h>
#include <stdlib.h>

#include "ref_test2.h"

int solution(IntList * L)
{
    // write your code in C++14 (g++ 6.2.0)
    IntList * A = L;
    int count = 0;
    while (A != NULL)
    {
        ++count;
        A = A->next;
    }
    return count;
}