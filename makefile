target = my_dht11.so
cc = gcc
srcs = $(wildcard src/my_dht11.c)
OBJS    =$(patsubst %cpp, %o, $(srcs))

CFLAGS  =-Wall -shared -lwiringPi
all: $(target)
$(target): $(OBJS)
	$(cc) $(CFLAGS) $(OBJS) -o $@
	
# %.o:%.cpp
# 	$(cc) -c -pthread $(CFLAGS) $^ -o $@
