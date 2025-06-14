#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "character.h"
void doRender(SDL_Renderer* renderer, character* ch);
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);