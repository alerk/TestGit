CC=/opt/toolchains/stbgcc-4.5.4-2.6/bin/mipsel-linux-gcc
#CPP=/opt/toolchains/stbgcc-4.5.4-2.6/bin/mipsel-linux-g++
CPP=g++

server_msg:
	$(CPP) -o $@ -g $@.c -lrt
	
client_msg:
	$(CPP) -o $@ -g $@.c -lrt

server_side:
	$(CPP) -o $@ -g $@.cpp
	
client_side:
	$(CPP) -o $@ -g $@.cpp
	
sender_message:
receiver_message:
	$(CPP) -o $@ -g $@.cpp
	
all: server_msg client_msg server_side client_side

clean:
	rm *_msg *_side


