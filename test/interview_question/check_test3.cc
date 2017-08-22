/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_CheckTest3_init = false;
#include "/home/quyen/Work/eastgate/interview_question/test/check_test3.h"

static CheckTest3 suite_CheckTest3;

static CxxTest::List Tests_CheckTest3 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CheckTest3( "/home/quyen/Work/eastgate/interview_question/test/check_test3.h", 6, "CheckTest3", suite_CheckTest3, Tests_CheckTest3 );

static class TestDescription_suite_CheckTest3_testExample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testExample() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 8, "testExample" ) {}
 void runTest() { suite_CheckTest3.testExample(); }
} testDescription_suite_CheckTest3_testExample;

static class TestDescription_suite_CheckTest3_testExampleNoPit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testExampleNoPit() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 12, "testExampleNoPit" ) {}
 void runTest() { suite_CheckTest3.testExampleNoPit(); }
} testDescription_suite_CheckTest3_testExampleNoPit;

static class TestDescription_suite_CheckTest3_testSimple1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testSimple1() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 16, "testSimple1" ) {}
 void runTest() { suite_CheckTest3.testSimple1(); }
} testDescription_suite_CheckTest3_testSimple1;

static class TestDescription_suite_CheckTest3_testSimple2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testSimple2() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 20, "testSimple2" ) {}
 void runTest() { suite_CheckTest3.testSimple2(); }
} testDescription_suite_CheckTest3_testSimple2;

static class TestDescription_suite_CheckTest3_testSimple3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testSimple3() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 24, "testSimple3" ) {}
 void runTest() { suite_CheckTest3.testSimple3(); }
} testDescription_suite_CheckTest3_testSimple3;

static class TestDescription_suite_CheckTest3_testRetries : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testRetries() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 28, "testRetries" ) {}
 void runTest() { suite_CheckTest3.testRetries(); }
} testDescription_suite_CheckTest3_testRetries;

static class TestDescription_suite_CheckTest3_testMedium1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testMedium1() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 33, "testMedium1" ) {}
 void runTest() { suite_CheckTest3.testMedium1(); }
} testDescription_suite_CheckTest3_testMedium1;

static class TestDescription_suite_CheckTest3_testMedium2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testMedium2() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 38, "testMedium2" ) {}
 void runTest() { suite_CheckTest3.testMedium2(); }
} testDescription_suite_CheckTest3_testMedium2;

static class TestDescription_suite_CheckTest3_testMediumPit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testMediumPit() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 43, "testMediumPit" ) {}
 void runTest() { suite_CheckTest3.testMediumPit(); }
} testDescription_suite_CheckTest3_testMediumPit;

static class TestDescription_suite_CheckTest3_testLargePit1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testLargePit1() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 48, "testLargePit1" ) {}
 void runTest() { suite_CheckTest3.testLargePit1(); }
} testDescription_suite_CheckTest3_testLargePit1;

static class TestDescription_suite_CheckTest3_testLargePit2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testLargePit2() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 53, "testLargePit2" ) {}
 void runTest() { suite_CheckTest3.testLargePit2(); }
} testDescription_suite_CheckTest3_testLargePit2;

static class TestDescription_suite_CheckTest3_testBigPit1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testBigPit1() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 58, "testBigPit1" ) {}
 void runTest() { suite_CheckTest3.testBigPit1(); }
} testDescription_suite_CheckTest3_testBigPit1;

static class TestDescription_suite_CheckTest3_testBigPit2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testBigPit2() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 63, "testBigPit2" ) {}
 void runTest() { suite_CheckTest3.testBigPit2(); }
} testDescription_suite_CheckTest3_testBigPit2;

static class TestDescription_suite_CheckTest3_testBig3_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testBig3_1() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 68, "testBig3_1" ) {}
 void runTest() { suite_CheckTest3.testBig3_1(); }
} testDescription_suite_CheckTest3_testBig3_1;

static class TestDescription_suite_CheckTest3_testBig3_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest3_testBig3_2() : CxxTest::RealTestDescription( Tests_CheckTest3, suiteDescription_CheckTest3, 73, "testBig3_2" ) {}
 void runTest() { suite_CheckTest3.testBig3_2(); }
} testDescription_suite_CheckTest3_testBig3_2;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
