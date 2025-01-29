CFLAGS = -std=c17 -Wall -Wextra -Werror `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

all: main

main: main.c
	gcc $(CFLAGS) main.c -o main $(LDFLAGS)

