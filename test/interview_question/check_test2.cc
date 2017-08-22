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
bool suite_CheckTest2_init = false;
#include "/home/quyen/Work/eastgate/interview_question/test/check_test2.h"

static CheckTest2 suite_CheckTest2;

static CxxTest::List Tests_CheckTest2 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CheckTest2( "/home/quyen/Work/eastgate/interview_question/test/check_test2.h", 6, "CheckTest2", suite_CheckTest2, Tests_CheckTest2 );

static class TestDescription_suite_CheckTest2_testExample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_testExample() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 8, "testExample" ) {}
 void runTest() { suite_CheckTest2.testExample(); }
} testDescription_suite_CheckTest2_testExample;

static class TestDescription_suite_CheckTest2_testExampleSingleDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_testExampleSingleDouble() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 12, "testExampleSingleDouble" ) {}
 void runTest() { suite_CheckTest2.testExampleSingleDouble(); }
} testDescription_suite_CheckTest2_testExampleSingleDouble;

static class TestDescription_suite_CheckTest2_testThreeElems : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_testThreeElems() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 16, "testThreeElems" ) {}
 void runTest() { suite_CheckTest2.testThreeElems(); }
} testDescription_suite_CheckTest2_testThreeElems;

static class TestDescription_suite_CheckTest2_testTwentyElems : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_testTwentyElems() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 20, "testTwentyElems" ) {}
 void runTest() { suite_CheckTest2.testTwentyElems(); }
} testDescription_suite_CheckTest2_testTwentyElems;

static class TestDescription_suite_CheckTest2_testMedium : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_testMedium() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 25, "testMedium" ) {}
 void runTest() { suite_CheckTest2.testMedium(); }
} testDescription_suite_CheckTest2_testMedium;

static class TestDescription_suite_CheckTest2_testMedium2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_testMedium2() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 30, "testMedium2" ) {}
 void runTest() { suite_CheckTest2.testMedium2(); }
} testDescription_suite_CheckTest2_testMedium2;

static class TestDescription_suite_CheckTest2_test1KElems : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest2_test1KElems() : CxxTest::RealTestDescription( Tests_CheckTest2, suiteDescription_CheckTest2, 35, "test1KElems" ) {}
 void runTest() { suite_CheckTest2.test1KElems(); }
} testDescription_suite_CheckTest2_test1KElems;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
