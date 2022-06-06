/**
 * @file OpenManzi_sprite.h
 * @author OpenManzi Contributors
 * @brief
 * @version 0.0.0
 * @date 2022-06-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef OPENMANZI_SPRITE_H
#define OPENMANZI_SPRITE_H

#include "SDL.h"
#include "SDL_image.h"

struct OpenManzi_Sprite;
typedef struct OpenManzi_Sprite OpenManzi_Sprite;

/* Set C calling convention in C++, so C++ does not name mangle functions. */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 * @param renderer
 * @param imagePath
 * @return OpenManzi_Sprite*
 */
OpenManzi_Sprite* OpenManzi_CreateSprite(SDL_Renderer *renderer, const char *imagePath);

/**
 * @brief Frees sprite and it's texture once it has been used.
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
void OpenManzi_SetSpriteDimensions(OpenManzi_Sprite *sprite, int x, int y, int width, int height);

/**
 * @brief
 *
 * @param sprite
 * @param x
 * @param y
 * @param width
 * @param height
 */
void OpenManzi_SetSpriteDestination(OpenManzi_Sprite *sprite, int x, int y, int width, int height);

/**
 * @brief
 *
 * @param sprite
 * @param renderer The SDL renderer context to draw the sprite.
 */
void OpenManzi_RenderSprite(SDL_Renderer *renderer, OpenManzi_Sprite *sprite);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* OPENMANZI_SPRITE_H */
