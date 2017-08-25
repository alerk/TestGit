USER=$(shell echo $(shell whoami) | sed 's/[ ]//g')

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CXX := clang -arch x86_64
else
  CXX := g++
endif

INC := -I include/
SRC := src/bug_fixing.cpp src/deepest_pit.cpp src/ptr_list_len.cpp\
test/ref_bug_fixing.cpp\
test/ref_deepest_pit.cpp\
test/ref_ptr_list_len.cpp
OBJ := $(patsubst %.cpp, %.o, $(SRC))
TEST := test
TEST_SRC := test_src
TEST_BIN := bin
GCCFLAGS := -std=c++11 -ggdb
LIBS := -levent -lcurl


CXXFLAGS := $(GCCFLAGS) $(LIBS) $(INC)

testgen:
	rm -rf $(TEST_SRC)
	mkdir -p $(TEST_SRC)
	cxxtestgen --error-printer -o $(TEST_SRC)/check_test1.cc $(TEST)/check_test1.h
	cxxtestgen --error-printer -o $(TEST_SRC)/check_test2.cc $(TEST)/check_test2.h
	cxxtestgen --error-printer -o $(TEST_SRC)/check_test3.cc $(TEST)/check_test3.h

%.o:
	$(CXX) $(CXXFLAGS) -c $(SRC) 

prepare-src: $(OBJ)
	 
check_test1:
	mkdir -p $(TEST_BIN)
	$(CXX) $(CXXFLAGS) test/ref_bug_fixing.cpp src/bug_fixing.cpp \
	$(TEST_SRC)/$@.cc -o $(TEST_BIN)/$@

check_test2:
	mkdir -p $(TEST_BIN)
	$(CXX) $(CXXFLAGS) test/ref_ptr_list_len.cpp src/ptr_list_len.cpp \
	$(TEST_SRC)/$@.cc -o $(TEST_BIN)/$@

check_test3:
	mkdir -p $(TEST_BIN)
	$(CXX) $(CXXFLAGS) test/ref_deepest_pit.cpp src/deepest_pit.cpp \
	$(TEST_SRC)/$@.cc -o $(TEST_BIN)/$@

test: prepare-src check_test1 check_test2 check_test3

clean:
	rm -f $(OBJ) $(TEST_BIN)/* $(TEST_SRC)/* 