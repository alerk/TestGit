#include <cxxtest/TestSuite.h>
#include <vector>

#include "test3.h"
#include "ref_test3.h"
#include "test_sample3.h"

class CheckTest3 : public CxxTest::TestSuite {
public:
    void testExample(void) {
        int A[] = {0, 1, 3, -2, 0, 1, 0, -3, 2, 3};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testExampleNoPit(void) {
        int A[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    /* one pit */
    void testSimple2(void) {
        int A[] = {0, 1, 3, -2, 1, 1, 2, -2, -2, -3};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    /* vulcano pit */
    void testSimple3(void) {
        int A[] = {0, 1, 3, -2, -4, -6, -4, -2, 3, 1, 0};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testRetries(void) {
        int A[] = {0, 1, 3, -2, 0, 1, 0, -3, 2, 3, 1, 3, -2, 0, 1, 0, -3, 2, 3, 1, 3, -2, 0, 1, 0, -3, 2, 3, 1, 3, -2, 0, 1, 0, -3, 2, 3, 1, 3, -2, 0, 1, 0, -3, 2, 3, 1, 3, -2, 0, 1, 0, -3, 2, 3};
        std::vector<int> v(A, A + sizeof(A) / sizeof(A[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    } 

    /* 99 elements, no pit */
    void testMedium1(void) {
        std::vector<int> v(listMedium1, listMedium1 + sizeof(listMedium1) / sizeof(listMedium1[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    /* medium test 99 elements, one pit */
    void testMedium2(void) {
        std::vector<int> v(listMedium2,
             listMedium2 + sizeof(listMedium2) / sizeof(listMedium2[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testLargePit1(void) {
        std::vector<int> v(listLarge1,
             listLarge1 + sizeof(listLarge1) / sizeof(listLarge1[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testLargePit2(void) {
        std::vector<int> v(listLarge2,
             listLarge2 + sizeof(listLarge2) / sizeof(listLarge2[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testBigPit1(void) {
        std::vector<int> v(listBig1, 
            listBig1 + sizeof(listBig1) / sizeof(listBig1[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testBigPit2(void) {
        std::vector<int> v(listBig2, 
            listBig2 + sizeof(listBig2) / sizeof(listBig2[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testBig3_1(void) {
        std::vector<int> v(listBig31, 
            listBig31 + sizeof(listBig31) / sizeof(listBig31[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }

    void testBig3_2(void) {
        std::vector<int> v(listBig32, 
            listBig32 + sizeof(listBig32) / sizeof(listBig32[0]));
        int sol = solution(v);
        int ref = ref_solution(v);
        TS_ASSERT_EQUALS(ref, sol);
    }
};

