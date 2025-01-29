#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_video.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} sdl_t;

typedef struct {
  uint32_t window_height;
  uint32_t window_width;
  uint32_t bg_color; // rgba(8b, 8b, 8b, 8b);
  uint32_t fg_color; // rgba(8b, 8b, 8b, 8b);
  uint32_t scale_factor;
} config_t;


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

bool set_config_from_cli_args(config_t *config, const int argc, char **argv) {

  // set default:
  config->window_width = 64;  // CHIP8 original X resolution
  config->window_height = 32; // CHIP8 original Y resolution
  config->bg_color = 0xFFFF00FF;
  config->fg_color = 0x27F5C6CC;
  config->scale_factor = 20;

  for (int i = 1; i < argc; i++) {
    (void)argv[i];
  }

  return true;
}

int main(int argc, char **argv){
  (void)argc;
  (void)argv;
int main(int argc, char **argv) {
  config_t config = {0};
  if (!set_config_from_cli_args(&config, argc, argv))
    exit(EXIT_FAILURE);

  // Init SDL
  sdl_t sdl = {0};
  if (!init_sdl(&sdl, config))
    exit(EXIT_FAILURE);

  printf("Hello world");
  chip8_t chip8 = {0};
  if (!init_chip8(&chip8))
    exit(EXIT_FAILURE);

  printf("No errors");
  exit(EXIT_SUCCESS);

  return 0;
}
