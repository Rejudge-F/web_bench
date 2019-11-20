src=$(wildcard *.cpp) 
dir=$(notdir $(src)) 
objs=$(patsubst %.cpp,%.o,$(dir)) 
logs=./log/*
CC=g++
CFLAGS=-Wall -g -O3 
LINK=-lpthread


target=./bin/App

$(target):$(objs)
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.cpp 
	$(CC) $(CFLAGS) -c -o $@ $^ $(LINK)

.phony:clean run
clean:
	rm -rf $(objs) $(target) $(logs) 
run:
	./bin/App
