#include <SDL3/SDL.h>
#include <stdio.h>
#include "character.h"
#include <SDL3/SDL_image.h>


int processEvents(SDL_Window* window, character* ch) {
    SDL_Event event;
    int done = 0;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            done = 1;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
        ch->x -= 10;
    if (state[SDL_SCANCODE_RIGHT])
        ch->x += 10;
    if (state[SDL_SCANCODE_UP])
        ch->y -= 10;
    if (state[SDL_SCANCODE_DOWN])
        ch->y += 10;

    // aggiorna la posizione del rettangolo SDL
    ch->rect.x = (float)ch->x;
    ch->rect.y = (float)ch->y;

    return done;
}


void doRender(SDL_Renderer* renderer, character* ch) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (ch->texture)
        SDL_RenderTexture(renderer, ch->texture, NULL, &ch->rect);

    SDL_RenderPresent(renderer);
}


SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);  // Carica l'immagine da file
    if (!surface) {
        printf("Errore caricamento immagine: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex) {
        printf("Errore creazione texture: %s\n", SDL_GetError());
        SDL_DestroySurface(surface);
        return NULL;
    }

    SDL_DestroySurface(surface);
    return tex;
}



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Errore SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Rettangolo", 700, 700, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Errore finestra: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Errore renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_FRect rect;
    rect.w = 100.0f;
    rect.h = 100.0f;
    rect.x = 300.0f;
    rect.y = 300.0f;

    int done = 0;

    character hero = {
    .x = 300,
    .y = 300,
    .hp = 100,
    .name = "Ciro",
    .rect = { 300, 300, 100, 100 },
    .texture = loadTexture(renderer, "hero.png")  // metti una PNG qui
    };

    while (!done) {
        done = processEvents(window, &hero);

        doRender(renderer, &hero);
        SDL_Delay(16);
    }

    deallocateCharacter(&hero);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
