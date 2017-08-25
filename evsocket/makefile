
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
SERVER_SRC := DataReceiver.cpp EvSocket.cpp EvSocketTest.cpp
CLIENT_SRC := DataReceiver.cpp EvSocket.cpp EvTestClient.cpp

# OBJ := $(patsubst %.cpp, %.o, $(SRC))
TARGET := build/EvTestServer build/EvTestClient

# build/%.o:
# 	$(CXX) $(CXXFLAGS) -c $(SRC) 

build/EvTestServer:
	$(CXX) $(CXXFLAGS) $(SERVER_SRC) -o $@

build/EvTestClient:
	$(CXX) $(CXXFLAGS) $(CLIENT_SRC) -o $@

# $(TARGET): $(OBJ)
# 	$(CXX) $(CXXFLAGS) $^ -o $@

all: build/EvTestServer build/EvTestClient

clean:
	rm -f *.o $(TARGET)