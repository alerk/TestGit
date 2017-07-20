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

http-server:
	$(CXX) http-server.c -o $@ $(CXXFLAGS)

http-client:
	$(CXX) http-client-1.c -o $@ $(CXXFLAGS)

https-client:
	$(CXX) https-client.c -o $@ $(CXXFLAGS)

proxy-server:
	$(CXX) proxy-server.c -o $@ $(CXXFLAGS)

all: test_mk sample http-server http-client
	echo Make all

clean:
	rm -f *.exe


FORCE: