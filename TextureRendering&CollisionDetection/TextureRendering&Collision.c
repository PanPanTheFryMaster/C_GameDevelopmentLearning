#include <SDL3/SDL.h>
#include <stdio.h>
#include "character.h"
#include <SDL3/SDL_image.h>
#include "utils.h"



// Handle user HID inputs
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
        .rect = { 300, 350, 100, 100 },
        .texture = loadTexture(renderer, "hero.png")
    };

    while (!done) {
        done = processEvents(window, &hero);

        doRender(renderer, &hero);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
