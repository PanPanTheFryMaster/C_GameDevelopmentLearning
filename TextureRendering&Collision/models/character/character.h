
#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
typedef struct {
	int x;
	int y;
	int hp;
	char* name;
	SDL_Texture* texture;
	SDL_FRect rect;
}character;


typedef enum {
	exit_success = 0,
	character_is_null,
	character_stuck_on_x,
	character_stuck_on_y,
	character_name_missing,
	character_invalid_name,
	character_increasing_hp_failed,
	character_decreasing_hp_failed,
	character_deallocate_failed,
	character_is_dead

}character_error_code;

character_error_code moveOnX(character* ch, int x);
character_error_code moveOnY(character* ch, int y);
character_error_code getName(character* ch, char* destination);
character_error_code setName(character* ch, const char* newName);
character_error_code increaseHp(character* ch, int hp);
character_error_code decreaseHp(character* ch, int hp);
character_error_code deallocateCharacter(character* ch);



