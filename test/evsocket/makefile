
USER=$(shell echo $(shell whoami) | sed 's/[ ]//g')

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CXX := clang -arch x86_64
else
  CXX := gcc
endif

GCCFLAGS := -std=c++11 -ggdb
LIBS := -levent -lcurl -lpthread

CXXFLAGS := $(GCCFLAGS) $(LIBS)

SRC := DataReceiver.cpp EvSocket.cpp EvSocketTest.cpp
TARGET := EvSocketTest

%.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)

$(TARGET): %.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f *.o $(TARGET)