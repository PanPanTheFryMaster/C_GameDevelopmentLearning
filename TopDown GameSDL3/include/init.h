#pragma once
#define SDL_MAIN_USE_CALLBACKS
#include "SDL_main.h"
#include "common.h"
#include "player.h"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv);