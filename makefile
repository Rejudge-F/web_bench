src=$(wildcard *.cpp) 
dir=$(notdir $(src)) 
objs=$(patsubst %.cpp,%.o,$(dir)) 
logs=./log/*
CC=g++
CFLAGS=-Wall -O3 -g -lpthread


target=./bin/App

$(target):$(objs)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.cpp 
	$(CC) $(CFLAGS) $^ -o $@

.phony:clean run
clean:
	rm -rf $(objs) $(target) $(logs) 
run:
	./bin/App
