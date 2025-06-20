#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "entity.h"


static void handle_events();
Entity init_player(SDL_Renderer* renderer);
static void update(float delta_time);
static void render(SDL_Renderer* renderer);
static void quit();