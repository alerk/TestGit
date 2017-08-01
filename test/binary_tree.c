#include <stdio.h>

int getNumPermutation(int X) {    
    if (1==X) {
        return 1;
    } else {
        int sum = 0;
        sum += 2 * getNumPermutation(X-1);
        for (int i=1; i<X-1; i++) {
            sum += (getNumPermutation(i)*getNumPermutation(X-1-i));
        }
        return sum;
    }
}

int main(int argc, char *argv[]) {
    for (int i = 1; i <= 5; i++) {
        printf("%d: %d random\n", i, getNumPermutation(i));
    }
    return 0;
}
