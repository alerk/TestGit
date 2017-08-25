// Assignment 1
int solution(vector<int> &A)
{
    // check size A
    if (A.size() < 2)
        return -1;

    int maxValueTraversed = A[0];
    int counter = 0;

    for (int i = 1; i < A.size(); ++i)
    {
        if (A[i] > maxValueTraversed)
        {
            maxValueTraversed = A[i];
            counter = 1;
            continue;
        }

        if (A[i] == maxValueTraversed)
        {
            ++counter;
        }

        if (counter > A.size()/2)
            return 1;
        else
        {
            if (i == (A.size() - 1))
                return -1;
        }
    }

    return -1;
}

// Assignment 2
int solution(IntList * L)
{
  // get first elent in L
  struct InList* cur = L->head();
  int size = 0;

  while (cur != NULL)
  {
    ++size;
    cur = cur->Next;
  }

  return size;
}

// Assignment 3
int solution(vector<int> &A)
{
    // check size A
    if (A.size() < 3)
        return -1;
    
    int depth = -1;
    int P = 0, Q = -1, R = -1;

    for (int i = 1; i < A.size(); i++)
    {
        if (Q < 0 && A[i] >= A[i-1])
            Q = i - 1;

        if ((Q >= 0 && R < 0) && (A[i] <= A[i-1] || (i + 1) == A.size()))
        {
            if (A[i] <= A[i-1])
                R = i - 1;
            else
                R = i;
            depth = std::max(depth, std::min(A[P]-A[Q], A[R]-A[Q]));
            P = i - 1;
            Q = R = -1;
        }
    }
    if (depth == 0) depth = -1;
    return depth;
}
