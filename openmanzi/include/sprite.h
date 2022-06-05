#ifndef OPENMANZI_SPRITE_H
#define OPENMANZI_SPRITE_H

#include "SDL.h"
#include "SDL_image.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OpenManzi_Sprite
{
    SDL_Rect dimensions;
    SDL_Texture *image;
};
typedef struct OpenManzi_Sprite OpenManzi_Sprite;

/**
 * @brief
 *
 * @param renderer
 * @param imagePath
 * @return OpenManzi_Sprite*
 */
OpenManzi_Sprite* OpenManzi_CreateSprite(SDL_Renderer *renderer, const char *imagePath);

/**
 * @brief Free the sprite and its texture once it has been used.
 *
 * @param sprite
 */
void OpenManzi_DeleteSprite(OpenManzi_Sprite *sprite);

/**
 * @brief Set the location of the sprite and its size.
 *
 * @param sprite
 * @param x
 * @param y
 * @param width
 * @param height
 */
void OpenManzi_setSpriteDimensions(OpenManzi_Sprite *sprite, int x, int y, int width, int height);

/**
 * @brief
 *
 * @param sprite
 * @param renderer The SDL renderer context to draw the sprite.
 * @param x
 * @param y The y coordinate of the
 * @param w
 * @param h
 */
void OpenManzi_RenderSprite(OpenManzi_Sprite *sprite, SDL_Renderer *renderer, int x, int y);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* OPENMANZI_SPRITE_H */
