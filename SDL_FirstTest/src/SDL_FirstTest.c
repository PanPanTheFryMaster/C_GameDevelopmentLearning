#include <SDL3/SDL.h>
#include <stdio.h>

int processEvents(SDL_Window* window, SDL_FRect* rect) {
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
        rect->x -= 10;
    if (state[SDL_SCANCODE_RIGHT])
        rect->x += 10;
    if (state[SDL_SCANCODE_UP])
        rect->y -= 10;
    if (state[SDL_SCANCODE_DOWN])
        rect->y += 10;

    return done;
}

void doRender(SDL_Renderer* renderer, SDL_FRect* rect, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, rect);

    SDL_RenderPresent(renderer);
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
    int colorIndex = 0;
    Uint64 lastChange = SDL_GetTicksNS();

    while (!done) {
        done = processEvents(window, &rect);
        doRender(renderer, &rect, 255, 0, 0, 255);
        /*Uint64 now = SDL_GetTicksNS();
        if ((now - lastChange) >= 1000000000ULL) {
            colorIndex = (colorIndex + 1) % 3;
            lastChange = now;
        }

        switch (colorIndex) {
        case 0: doRender(renderer, &rect, 255, 0, 0, 255); break;
        case 1: doRender(renderer, &rect, 0, 255, 0, 255); break;
        case 2: doRender(renderer, &rect, 0, 0, 255, 255); break;
        }*/

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
