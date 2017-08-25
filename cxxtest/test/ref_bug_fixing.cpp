#include <stdio.h>
#include <iostream>
#include <algorithm>

#include "ref_test1.h"

int ref_solution(std::vector<int> &A) {
    int n = A.size();
    std::vector<int> L;
    L.push_back(-1);

    for (int i = 0; i < n; i++) {
        L.push_back(A[i]);
    }

    int count = 0;
    int pos = (n + 1)/2;
    int candidate = L[pos];

    for (int i = 1; i <= n; i++) {
        if (candidate == L[i])
            count++;
    }

    if (count > n/2) { //if (count > pos) {
        return candidate;
    }
    return -1;
}
