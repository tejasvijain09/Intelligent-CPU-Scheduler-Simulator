CC = g++
CFLAGS = -std=c++11 -Wall

all: scheduler

scheduler: src/main.cpp src/process.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f scheduler