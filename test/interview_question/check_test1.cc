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
bool suite_CheckTest1_init = false;
#include "/home/quyen/Work/eastgate/interview_question/test/check_test1.h"

static CheckTest1 suite_CheckTest1;

static CxxTest::List Tests_CheckTest1 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CheckTest1( "/home/quyen/Work/eastgate/interview_question/test/check_test1.h", 6, "CheckTest1", suite_CheckTest1, Tests_CheckTest1 );

static class TestDescription_suite_CheckTest1_testExample1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest1_testExample1() : CxxTest::RealTestDescription( Tests_CheckTest1, suiteDescription_CheckTest1, 12, "testExample1" ) {}
 void runTest() { suite_CheckTest1.testExample1(); }
} testDescription_suite_CheckTest1_testExample1;

static class TestDescription_suite_CheckTest1_testExample2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest1_testExample2() : CxxTest::RealTestDescription( Tests_CheckTest1, suiteDescription_CheckTest1, 20, "testExample2" ) {}
 void runTest() { suite_CheckTest1.testExample2(); }
} testDescription_suite_CheckTest1_testExample2;

static class TestDescription_suite_CheckTest1_testSimple1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CheckTest1_testSimple1() : CxxTest::RealTestDescription( Tests_CheckTest1, suiteDescription_CheckTest1, 28, "testSimple1" ) {}
 void runTest() { suite_CheckTest1.testSimple1(); }
} testDescription_suite_CheckTest1_testSimple1;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
