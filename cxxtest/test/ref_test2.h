#include <vector>
#ifndef INT_LIST
#define INT_LIST
struct IntList {
    int value;
    IntList * next;
};
#endif
int ref_solution(IntList * L);
