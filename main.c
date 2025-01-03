#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"

bool init_sdl (void){
  return true;
}

int main(int argc, char **argv){
  (void)argc;
  (void)argv;

  printf("Hello world");
  return 0;
}
