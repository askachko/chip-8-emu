#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
bool init_sdl(sdl_t *sdl, const config_t config) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
    SDL_Log("Error with initializing: %s\n", SDL_GetError());
    return false;
  }

  sdl->window = SDL_CreateWindow("Chip 8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       config.window_width * config.scale_factor,
                       config.window_height * config.scale_factor,
                       0);

  if (!sdl->window) {
    SDL_Log("Could not create SDL window %s\n", SDL_GetError());
    return false;
  }

  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);

  if (!sdl->renderer) {
    SDL_Log("Could not create SDL renderer %s\n", SDL_GetError());
    return false;
  }

  return true;
}

bool init_sdl (void){
  return true;
}

int main(int argc, char **argv){
  (void)argc;
  (void)argv;
int main(int argc, char **argv) {
  if (!init_sdl(&sdl, config))
    exit(EXIT_FAILURE);

  printf("Hello world");

  return 0;
}
