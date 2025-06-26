#pragma once
#include <common.h>
#include <SDL_image.h>
#include "external/cute_tiled.h"


typedef struct {
	SDL_Texture* texture;
	int firstgid;
	int tilecount;
	int tileset_width;
	int tileset_height;
	Texture* next;
}Texture;
