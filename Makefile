IMPORTANT_FLAGS=-std=c++20 -g -O2
DEBUGGER_FLAGS=-Wall -fsanitize=address,undefined

EPOCHS=100000

ifeq ($(OS), Windows_NT)
CLEAR=cls
PREFIX=.\\
else
CLEAR=clear
PREFIX=./
endif

all:
	g++ $(IMPORTANT_FLAGS) main.cpp -o nn
	$(CLEAR)
	$(PREFIX)nn "none" $(EPOCHS)