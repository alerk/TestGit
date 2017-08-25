# CXXTEST for Interview questions
* Author: Nguyen Xuan Quyen
* Company: Eastgate Software
* Version: 1.0
* Released date: August 24th, 2017

## Description
* Test the programming questions for candidate using cxxtest

## Running
* The questions are placed in *src_question/* directory  
* Candidate must finish the question without changing the name of functions  

### Generate the test datas
* Run
```
$python test/createTestData1.py > include/test_sample1.h
$python test/createTestData3.py > include/test_sample3.h
```
* These scripts will generate test data for test1 and test3 randomly
* Due to the uncompleted python code, please open test_sample*.h files and remove the square braces ('[  ]') surrounding the array items  
  * By Notepad++: Replace "\n[" with "\n" and "]\n" with "\n"

### Generate the test files
* Run 
```
$make testgen
```
* This will generate 3 files check_test1.cc, check_test3.cc, check_test3.cc

### Compile the binaries from candidates
* The answers will be placed in *src/* directory  
* Run  
```
$make prepare-src
```

### Check the test result with predefined test cases
```
$make test
$./bin/check_test1
$./bin/check_test2
$./bin/check_test3
```

### Clean the generated source files and test binaries
```
$make clean
```

