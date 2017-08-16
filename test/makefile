USER=$(shell echo $(shell whoami) | sed 's/[ ]//g')

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CXX := clang -arch x86_64
else
  CXX := gcc
endif

GCCFLAGS := -std=c++11 -ggdb
LIBS := -levent -lcurl

CXXFLAGS := $(GCCFLAGS) $(LIBS)

SRC := test_mk.c
TARGET := run_test get put http-server http-client http-client-1 https-client \
		proxy-server stat1 rot13

.PHONY: all clean
test_mk:
	$(CXX) $(SRC) -o build/$(TARGET) $(CXXFLAGS)

get:
	$(CXX) curl_sample.c -o build/$@ $(CXXFLAGS)

put:
	$(CXX) httpput.c -o build/$@ $(CXXFLAGS)

http-server:
	$(CXX) http-server.c -o build/$@ $(CXXFLAGS)

http-client:
	$(CXX) http-client.c -o build/$@ $(CXXFLAGS)

http-client-1:
	$(CXX) http-client-1.c -o build/$@ $(CXXFLAGS)

https-client:
	$(CXX) https-client.c -o build/$@ $(CXXFLAGS)

proxy-server:
	$(CXX) proxy-server.c -o build/$@ $(CXXFLAGS)

stat1:
	$(CXX) basic_statistic.c -o build/basic_statistic $(CXXFLAGS)

hello_world:
	$(CXX) hello_world.c -o build/$@ $(CXXFLAGS)

rot13: 
	$(CXX) $(CXXFLAGS)  $@.cpp -o build/$@ -levent_core

all: $(TARGET)
	echo Make all

clean:
	rm -f *.exe $(TARGET) build/*


FORCE:
