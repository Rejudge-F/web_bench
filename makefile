src=$(wildcard *.cpp) 
dir=$(notdir $(src)) 
objs=$(patsubst %.cpp,%.o,$(dir)) 
logs=./logs/*
CC=g++
CFLAGS=-Wall -g -O3 
LINK=-lpthread


target=./bin/App

$(target):$(objs)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)
%.o:%.cpp 
	$(CC) $(CFLAGS) -c -o $@ $^ $(LINK)

.phony:clean run
clean:
	rm -rf $(objs) $(target) $(logs) 
run:
	./bin/App -r -t 50 -u http://localhost:80/hello.html -c 50000 --get
cleanlog:
	rm -rf ./logs/*
