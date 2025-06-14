#include <stdio.h>
#include "character.h"
#include <string.h>
#define max_hp 100
#define max_x 1920
#define max_y 1080
#define max_name_length 16


character_error_code moveOnX(character* ch, int x) {
	if (ch == NULL)
		return character_is_null;

	if (x > max_x) return character_stuck_on_x;

	ch->x = x;
	if (ch->x == x) {
		return exit_success;
	}
	return character_stuck_on_x;
}

character_error_code moveOnY(character* ch, int y) {
	if (ch == NULL)
		return character_is_null;

	if (y > max_y) return character_stuck_on_y;

	ch->y = y;
	if (ch->y == y) {
		return exit_success;
	}
	return character_stuck_on_y;
}

character_error_code getName(character* ch, char* destination) {
	if (ch == NULL)
		return character_name_missing;

	if (ch->name == NULL)
		return character_name_missing;
	size_t size = strlen(ch->name) + 1;
	destination = malloc(size);
	strcpy_s(destination, size ,ch->name);
	return exit_success;
}

character_error_code setName(character* ch, const char* newName) {
		size_t size = strlen(newName) + 1;
		if (ch == NULL) {
			return character_is_null;
		}

		if (newName == NULL || size > max_name_length) {
			return character_invalid_name;
		}

		if (ch->name != NULL) {
			free(ch->name);
			ch->name = NULL;
		}

		ch->name = malloc(size); 
		if (ch->name == NULL) {
			return character_invalid_name;
		}

		strcpy_s(ch->name, size, newName);

		return exit_success;
}

character_error_code increaseHp(character* ch, int hp) {
	if (ch == NULL) {
		return character_is_null;
	}
	
	if (hp < 0) return character_increasing_hp_failed;

	if ((ch->hp + hp) > max_hp) {
		ch->hp = max_hp;
		return exit_success;
	}
	
	ch->hp += hp;
	return exit_success;
}

character_error_code decreaseHp(character* ch, int hp) {
	if (ch == NULL) {
		return character_is_null;
	}

	if (hp < 0) return character_decreasing_hp_failed;

	if ((ch->hp - hp) <= 0) {
		ch->hp = 0;
		return character_is_dead;
	}

	ch->hp -= hp;
	return exit_success;
}

character_error_code deallocateCharacter(character* ch) {
	if (ch == NULL)
		return character_is_null;

	if (ch->name != NULL)
		free(ch->name);

	return exit_success;
}

