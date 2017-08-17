
USER=$(shell echo $(shell whoami) | sed 's/[ ]//g')

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CXX := clang -arch x86_64
else
  CXX := g++
endif

GCCFLAGS := -std=c++11 -ggdb
LIBS := -levent -lcurl -lpthread

CXXFLAGS := $(GCCFLAGS) $(LIBS)

SRC := DataReceiver.cpp EvSocket.cpp EvSocketTest.cpp
OBJ := $(patsubst %.cpp, %.o, $(SRC))
TARGET := ../build/EvSocketTest

build/%.o:
	$(CXX) $(CXXFLAGS) -c $(SRC) 

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)