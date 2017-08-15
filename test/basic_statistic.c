#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void print_array(int N, long A[]) {
    for (int i=0; i<N; i++) {
        printf("%ld ", A[i]);
    }
    printf("\n");
}

int main() {
    int N;
    long *arr;
    int *appearance;
    long sum = 0;
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    scanf("%d", &N);
    arr = (long*)malloc(N * sizeof(long));
    appearance = (int*)malloc(N * sizeof(int));
    
    memset(appearance, 1, N * sizeof(int));
    
    for (int i=0; i<N; i++) {
        scanf("%ld", & (arr[i]));
        sum += arr[i];
    }
    printf("%f\n", (sum*1.0)/N);
    printf("Input array\n");
    print_array(N, arr);
    
    /* Arrange vector accending */
    for (int i=0; i<N-1; i++) {
        for (int j=i+1; j<N; j++) {
            if (arr[i] > arr[j]) {
                long temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        print_array(N, arr);
    }

    printf("\nArrange array\n");
    print_array(N, arr);
    
    if (N % 2 == 1) {
        printf("%ld\n", arr[N/2+1]);
    } else {
        printf("%f\n", (arr[N/2-1] + arr[N/2])/2.0);
    }
    
    for (int i=0; i<N-1; i++) {
        if (arr[i] == arr[i+1]) {
            appearance[i] = appearance[i+1] = appearance[i] + 1;
        }
    }
    long mode = arr[0];
    int mode_idx = 0;
    for (int i=0; i<N; i++) {
        if (appearance[i] > appearance[mode_idx]) {
            mode_idx = i; mode = arr[i];
        } 
    }
    printf("%ld", mode);
    return 0;
}