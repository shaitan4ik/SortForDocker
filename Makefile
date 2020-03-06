#This is makefile for builf CLI versions for example
#HanoiTowel
SHELL =/bin/sh
CC=clang++
CFLAGS=-c -Wall
LDFLAGS= 
SOURCES=main.cpp help_func.cpp
OBJ = main.o help_func.o
EXECUTABLE = cliHanoiTowel
all:cliHanoiTowel

cliHanoiTowel: $(OBJ)
	$(CC) -g $(OBJ) -o $(EXECUTABLE)
main.o:main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o
help_func.o:help_func.cpp help_func.h
	$(CC) $(CFLAGS) help_func.cpp -o help_func.o 
.PHONY: clean
clean:
	rm -rf $(OBJ)
