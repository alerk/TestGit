#include "ref_test3.h"

int MIN(int a, int b)
{
    int min;
    if (a < b)
        min = a;
    else
        min = b;
    return min;
}

int MAX(int a, int b)
{
    int max;
    if (a > b)
        max = a;
    else
        max = b;
    return max;
}

int solution(std::vector<int>& A)
{
    int depth = 0;
    int P = 0, Q = -1, R = -1;

    for (int i = 1; i < A.size(); i++)
    {
        if (Q < 0 && A[i] >= A[i - 1])
            Q = i - 1;

        if ((Q >= 0 && R < 0) 
            && (A[i] <= A[i - 1] || i + 1 == A.size()))
        {
            if (A[i] <= A[i - 1])
                R = i - 1;
            else
                R = i;
            depth = MAX(depth, MIN(A[P] - A[Q], A[R] - A[Q]));
            P = i - 1;
            Q = R = -1;
        }
    }
    if (depth == 0)
        depth = -1;
    return depth;
}