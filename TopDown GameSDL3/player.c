#include "player.h"
static SDL_FRect sprite_portion = { 17, 14, 15, 18 };
static SDL_Texture* player_texture;


typedef struct {
    float x, y;
}Position;
Position position = { 0, 0 };



static void handle_events() {

}

Entity init_player(SDL_Renderer* renderer) {
    const char path[] = "./char_spritesheet.png";
    player_texture = IMG_LoadTexture(renderer, path);

    Entity player = { .quit = quit, .handle_event = handle_events , .update = update, . render = render };
    return player;
}


static void update(float delta_time) {
    const _Bool *kyboard_state = SDL_GetKeyboardState(NULL);

    if (kyboard_state[SDL_SCANCODE_W]) {
        position.y -= 60 * delta_time;
    }
    if (kyboard_state[SDL_SCANCODE_S]) {
        position.y += 60 * delta_time;
    }
    if (kyboard_state[SDL_SCANCODE_A]) {
        position.x -= 60 * delta_time;
    }
    if (kyboard_state[SDL_SCANCODE_D]) {
        position.x += 60 * delta_time;
    }
}

static void render(SDL_Renderer *renderer) {
    SDL_FRect player_position = { position.x, position.y, 15, 18 };

    SDL_GetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer, player_texture, &sprite_portion, &player_position);
}


static void quit() {

}