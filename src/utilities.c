#include "utilities.h"

int renderText(SDL_Renderer *renderer, TTF_Font *font, const char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        fprintf(stderr, "Error creating text surface: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Error creating texture from surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return 0;
    }

    SDL_Rect renderQuad = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);

    int textWidth = surface->w;  // Store the text width before freeing the surface

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return textWidth;
}
