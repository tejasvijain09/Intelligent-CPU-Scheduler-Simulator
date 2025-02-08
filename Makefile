CC = g++
CFLAGS = -std=c++11 -Wall

# All files needed for the final build
all: scheduler

# Link all the necessary source files to create the executable
scheduler: src/main.cpp src/process.cpp src/scheduler.cpp
	$(CC) $(CFLAGS) $^ -o $@

# Clean up any generated files
clean:
	rm -f scheduler
