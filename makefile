CFLAGS=-std=c17 -Wall -Wextra -Werror

all:
		gcc main.c -o main $(CFLAGS) 
