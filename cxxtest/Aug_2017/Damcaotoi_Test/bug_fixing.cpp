
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int solution(std::vector<int> &A) {
	int n = A.size();
    std::vector<int> L;
    //L.push_back(-1);

    for (int i = 0; i < n; i++) {
        L.push_back(A[i]);
    }

    int count = 0;
    int pos;
	if(n%2 == 0) {
		pos = n/2;
	}else {
		pos = (n-1)/2; // if 3 > 5/2
		//pos = (n+1)/2; // if 3 not > 5/2
	}
	 
    int candidate = L[pos];

    //for (int i = 1; i <= n; i++) {
	for (int i = 0; i < n; i++) {
        if (candidate == L[i])
            count++;
    }

    if (count > pos) {
        return candidate;
    }
    return -1;
}
int main(){
	vector <int> B;
	B.push_back(1);
	B.push_back(1);
	B.push_back(1);
	B.push_back(3);
	B.push_back(3);
	B.push_back(3);
	B.push_back(3);
	B.push_back(3);
	B.push_back(4);
	cout << "Answer is : " << solution(B)<< endl; 
	return 0;
}