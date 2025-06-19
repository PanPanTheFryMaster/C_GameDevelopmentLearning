#define SDL_MAIN_USE_CALLBACKS
#include "SDL_main.h"
#include "SDL.h"
#include "SDL_image.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* player_texture;


// Inizializza applicazione e variabili
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Error initializing SDL: %s", SDL_GetError);
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("SDL 3 GAME", 800, 600, NULL);
    if (!window) {
        SDL_Log("Error creating window: %s", SDL_GetError);
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Error creating renderer: %s", SDL_GetError);
        return SDL_APP_FAILURE;
    }

    const char path[] = "./char_spritesheet.png";
    player_texture = IMG_LoadTexture(renderer, path);
    return SDL_APP_CONTINUE;
}





// Registra eventi
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}


void update() {}

void render() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // Draw Character
    SDL_FRect sprite_portion = { 17, 14, 15, 18 };
    SDL_FRect player_position = { 250, 250, 15, 18 };
    SDL_GetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);

    SDL_RenderTexture(renderer, player_texture, &sprite_portion, &player_position);
    SDL_RenderPresent(renderer);
}

// Loop di esecuzione
SDL_AppResult SDL_AppIterate(void* appstate) { 
    render();
    return SDL_APP_CONTINUE;
}




// Deallocazione
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

