IMPORTANT_FLAGS=-std=c++20 -g -O2
DEBUGGER_FLAGS=-Wall -fsanitize=address,undefined

all:
	g++ $(IMPORTANT_FLAGS) main.cpp -o nn