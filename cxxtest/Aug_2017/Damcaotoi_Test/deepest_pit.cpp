#include <stdio.h>
#include <iostream>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define TANG 1
#define GIAM -1
#define START 0

using namespace std;

int solution(std::vector<int> &A) {
    int n = A.size();
    std::vector<int> L;

    for (int i = 0; i < n; i++) {
        L.push_back(A[i]);
    }
	int first = START ,mid = START ,last = START, status = START;
	int answer=0;
	for (int i = 1; i < n; i++) {
		if(status == START)
		{
			if(L[i]<L[i-1])// true
			{
				first = i-1;
				status = GIAM;
			}
		}else if(status == TANG)
		{
			if(L[i] < L[i-1] || i == n-1)// fale
			{
				last = i-1;
				answer = max(answer, min(L[first]-L[mid] , L[last] - L[mid]));
				status = GIAM;
				first = i-1;
			}
			
		}else {//day GIAM
			if(L[i]>L[i-1])// flase
			{
				mid = i-1;
				status = TANG;
			}
		}
	}

    return answer;
}
int main(){
	vector <int> B;
	B.push_back(0);
	B.push_back(1);
	B.push_back(3);
	B.push_back(-2);
	B.push_back(0);
	B.push_back(1);
	B.push_back(0);
	B.push_back(-3);
	B.push_back(2);
	B.push_back(3);
	cout << "Answer is : " << solution(B)<< endl; 
	return 0;
}