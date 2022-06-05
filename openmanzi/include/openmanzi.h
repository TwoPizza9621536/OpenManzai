#ifndef OPENMANZI_H
#define OPENMANZI_H

#include <stdio.h>
#include <stdbool.h>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct OpenManzi_Sprite
{
    SDL_Texture *image;
    SDL_Rect dimensions;
};
typedef struct OpenManzi_Sprite OpenManzi_Sprite;

OpenManzi_Sprite* OpenManzi_CreateSprite(SDL_Renderer *renderer, const char* imagePath);
void OpenManzi_DeleteSprite(OpenManzi_Sprite *sprite);
void OpenManzi_setSpriteDimensions(OpenManzi_Sprite *sprite, int x, int y, int width, int height);
void OpenManzi_RenderSprite(OpenManzi_Sprite *sprite, SDL_Renderer *renderer, int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* OPENMANZI_H */
