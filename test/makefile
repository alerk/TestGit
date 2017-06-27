USER=$(shell echo $(shell whoami) | sed 's/[ ]//g')

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CXX := clang -arch x86_64
else
  CXX := gcc
endif

CXXFLAGS := -levent -lcurl

SRC := test_mk.c
TARGET := run_test

.PHONY: all clean
test_mk:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

get:
	$(CXX) curl_sample.c -o $@ $(CXXFLAGS)

put:
	$(CXX) httpput.c -o $@ $(CXXFLAGS)

all: test_mk sample
	echo Make all

clean:
	rm -f *.exe


FORCE: