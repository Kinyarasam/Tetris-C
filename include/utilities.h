#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int renderText(SDL_Renderer *renderer, TTF_Font *font, const char* text, SDL_Color color, int x, int y);

#endif /** __UTILITIES_H__ */
