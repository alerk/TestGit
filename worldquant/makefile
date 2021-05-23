USER=$(shell echo $(shell whoami) | sed 's/[ ]//g')

UNAME_S := $(shell uname -s)
CXX := g++
# ifeq ($(UNAME_S),Darwin)
# 	CXX := clang -arch x86_64
# else
# 	CXX := g++
# endif

GCCFLAGS := -std=c++11 -ggdb
LIBS := -levent -lcurl -lpthread

CXXFLAGS := $(GCCFLAGS) $(LIBS)

SRC := StockRecorder.cpp
# SERVER_SRC := DataReceiver.cpp EvSocket.cpp EvSocketTest.cpp
# CLIENT_SRC := DataReceiver.cpp EvSocket.cpp EvTestClient.cpp
Q1 := StockRecorder.cpp

# OBJ := $(patsubst %.cpp, %.o, $(SRC))
TARGET := build/Q1 # build/Q2
# # build/%.o:
# # 	$(CXX) $(CXXFLAGS) -c $(SRC) 
build/Q1:
	$(CXX) $(CXXFLAGS) $(Q1) -o $@

# build/Q2:
#	$(CXX) $(CXXFLAGS) $(CLIENT_SRC) -o $@

# $(TARGET): $(OBJ)
# 	$(CXX) $(CXXFLAGS) $^ -o $@

all: build/Q1 
# build/EvTestClient

clean:
	rm -f build/*.o $(TARGET)

