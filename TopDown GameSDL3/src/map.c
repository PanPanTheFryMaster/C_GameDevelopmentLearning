#define CUTE_TILED_IMPLEMENTATION
#include "map.h"

static cute_tiled_map_t* map;
static cute_tiled_layer_t* layer;
static cute_tiled_tileset_t* tileset;

static Texture* texture;

void render(SDL_Renderer* renderer) {

}



Entity init_map(SDL_Renderer* renderer) {
	const char map_path[] = "./tiled/map.json";
	map = cute_tiled_load_map_from_file(map_path, NULL);
	if (!map) {
		SDL_Log("Error loading the map");
	}

	layer = map->layers;
	tileset = map->tilesets;
	texture = SDL_malloc(sizeof(Texture));

	Texture* current_texture = texture;
	
	while (tileset) {
		current_texture->texture = IMG_LoadTexture(renderer, tileset->image.ptr);

		if (!current_texture->texture) {
			SDL_Log("Error loading texture for fileset");
		}
		else {
			SDL_Log("Texture loaded successfully");
		}

		current_texture->firstgid = tileset->firstgid;
		current_texture->tilecount = tileset->tilecount;
		current_texture->tileset_width = tileset->imagewidth;
		current_texture->tileset_height = tileset->imageheight;

		tileset = tileset->next;
		if (tileset) {
			current_texture->next = SDL_malloc(sizeof(Texture));
			current_texture = current_texture->next;
		}
		else {
			current_texture->next = NULL;
		}

	}

	Entity map_e = {
		.cleanup = render,
		.handle_event = render,
		.render = render,
		.update = render
	};

	return map_e;
}