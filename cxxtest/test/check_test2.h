#include <cxxtest/TestSuite.h>
#include <vector>

#include "test2.h"
#include "ref_test2.h"

class CheckTest2 : public CxxTest::TestSuite {
    IntList * prepareList(int size) {
        if (0 >= size || 5000 < size) {
            return NULL;
        }
        IntList* A = new IntList();
        IntList* l = A;
        for (int i = 1; i < size; i++) {
            IntList* temp = new IntList();
            l->next = temp;
            l = l->next;
        }
        return A;
    }

    void releaseList(IntList* A) {
        while (A != NULL) {
            IntList* l = A->next;
            delete(A);
            A = l;
        }
    }
public:
    void testExample(void) {
        int size = 4;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }

    void testExampleSingleDouble(void) {
        int size = 1;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }

    void testThreeElems(void) {
        int size = 3;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }

    void testTwentyElems(void) {
        int size = 20;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
        TS_ASSERT(true);

    }

    void testMedium(void) {
        int size = 93;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
        TS_ASSERT(true);

    }

    void testMedium2(void) {
        int size = 999;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }

    void test1KElems(void) {
        int size = 1000;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }

    void testQuiteLong(void) {
        int size = 4000;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }

    void testLong(void) {
        int size = 5000;
        IntList* A = prepareList(size);
        int sol = solution(A);
        releaseList(A);
        TS_ASSERT_EQUALS(size, sol);
    }
};

