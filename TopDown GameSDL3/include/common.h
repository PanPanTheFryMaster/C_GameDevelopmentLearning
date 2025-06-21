#pragma once
#include "SDL.h"
#include "entity.h"


typedef  struct AppState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint64 last_tick;
	Uint64 current_tick;
	float delta_time;
}AppState;