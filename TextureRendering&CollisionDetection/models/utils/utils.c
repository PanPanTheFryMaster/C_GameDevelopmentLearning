#include "utils.h"

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
