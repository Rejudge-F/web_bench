src=$(wildcard *.cpp) 
dir=$(notdir $(src)) 
objs=$(patsubst %.cpp,%.o,$(dir)) 
CC=g++
CFLAGS=-Wall -O3 -g

$(objs):$(src) 
	$(CC) $(CFLAGS) $< -c 

.phony:clean 
clean:
	rm -rf $(objs) 
	
