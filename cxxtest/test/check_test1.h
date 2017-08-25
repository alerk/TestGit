#include <cxxtest/TestSuite.h>
#include <vector>
#include <limits.h>

#include "test1.h"
#include "ref_test1.h"
#include "test_sample1.h"

class CheckTest1 : public CxxTest::TestSuite {
public:
    void testExample1(void) {
        int A[] = {2, 2, 2, 2, 2, 3, 4, 4, 4, 6};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // A = [1, 1, 1, 1, 50]
    void testExample2(void) {
        int A[] = {1, 1, 1, 1, 50};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // A = [2, 2, 3]
    // Value from a continuous range
    void testSimple1(void) {
        int A[] = {2, 2, 3};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // 0s / 1s only
    void testSimple2(void) {
        int A[] = {0, 0, 0, 1, 1, 1, 1};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // one element
    void testSingle(void) {
        int A[] = {2};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // two values
    void testTwoValue(void) {
        int A[] = {2, 5};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);

    }

    // extreme big values
    void testExtremeBigValue(void) {

        int A[] = {INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // medium 1: small sequence repeated many times
    void testMedium_1(void) {
        int A[] = {-1, -1, -1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 14, 14, 14, 14, 14, 14,
            14, 14, 14};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // medium 2: no leader and small sequence with values from a continuous range
    void testMedium_2(void) {
        int A[] = {1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }
    
    // cyclic sequence: no leader and small sequence repeated many times
    void testCyclicSequence(void) {
        int A[] = {-1, -1, 0, 0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 6, 7, 7, 8, 8, 8};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // medium random: random sequences
    void testMediumRandom(void) {
        // setUp
        std::vector<int> v(mediumRan, mediumRan + sizeof(mediumRan) / sizeof(mediumRan[0]));
        int sol = solution(v);
        // assert
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // large: two different values, length ~ 100_000
    void testLarge(void) {
        std::vector<int> v(largeRan, largeRan + sizeof(largeRan) / sizeof(largeRan[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }

    // large_range: values from a continuous range, length = ~100_000
    void testLargeRange(void) {
        std::vector<int> v(largeRan2, largeRan2 + sizeof(largeRan2) / sizeof(largeRan2[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        char msg[100];
        sprintf(msg, "got %d expected %d\n", sol, ref);
        // TSM_ASSERT_EQUALS(msg, ref, sol);
        TS_ASSERT_EQUALS(ref, sol);
    }
};

