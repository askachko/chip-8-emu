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

typedef enum {
  QUIT,
  RUNNING,
  PAUSED
} emulator_state_t;

typedef struct {
  emulator_state_t state;
} chip8_t;

bool init_chip8(chip8_t *chip8) {
    chip8->state = RUNNING;
    return true;
};

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

void final_cleanup(const sdl_t *sdl) {
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->window);
  SDL_Quit();
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

void update_screen(const sdl_t *sdl) {
    SDL_RenderPresent(sdl->renderer);
}

void clear_screen(const config_t *config, const sdl_t *sdl) {
  const uint8_t r = (config->bg_color >> 24) & 0xFF;
  const uint8_t g = (config->bg_color >> 16) & 0xFF;
  const uint8_t b = (config->bg_color >> 8) & 0xFF;
  const uint8_t a = config->bg_color & 0xFF;

  SDL_SetRenderDrawColor(sdl->renderer, r, g, b, a); // red
  SDL_RenderClear(sdl->renderer);
}

void handle_input(chip8_t *chip8) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      chip8->state = QUIT;
      return;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case (SDLK_ESCAPE): chip8->state = QUIT ;

        };
        break;

    case SDL_KEYUP:
      break;

    default:
      break;
    }
  }
}

int main(int argc, char **argv) {
  config_t config = {0};
  if (!set_config_from_cli_args(&config, argc, argv))
    exit(EXIT_FAILURE);

  // Init SDL
  sdl_t sdl = {0};
  if (!init_sdl(&sdl, config))
    exit(EXIT_FAILURE);

  chip8_t chip8 = {0};
  if (!init_chip8(&chip8))
    exit(EXIT_FAILURE);

  clear_screen(&config, &sdl);

  while (chip8.state != QUIT) {
    // Get_time();
    handle_input(&chip8);

    clear_screen(&config, &sdl);
    update_screen(&sdl);

    // 60 fps dela
    SDL_Delay(16); // 16 - actual time elapsed
  }

  final_cleanup(&sdl);
  printf("No errors");
  exit(EXIT_SUCCESS);

  return 0;
}
