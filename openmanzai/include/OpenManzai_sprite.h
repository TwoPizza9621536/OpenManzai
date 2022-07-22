/**
 * \file OpenManzai_sprite.h
 * \author OpenManzai Contributors
 * \brief
 * \version 0.0.0
 * \date 2022-06-05
 *
 * \copyright Copyright (c) 2022
 *
 */

#ifndef OpenManzai_sprite_h_
#define OpenManzai_sprite_h_

#include "SDL.h"
#include "SDL_image.h"

 /**
   * ? Please suggest a better variable and function names. See issue #6.
   *
   * Abstraction layer to store information about rhe sprite so we do not have to
   * set each variable individually and keep repeating ourselves.
   */
typedef struct
{
    SDL_Rect dimensions, destination;
    SDL_Texture* image;
} OpenManzai_Sprite;

#ifdef __cplusplus
/* Set C calling convention in C++, so C++ does not name mangle functions. */
extern "C"
{
#endif

    /**
     * \brief
     *
     * \param renderer
     * \param imagePath
     * \return OpenManzai_Sprite*
     */
    OpenManzai_Sprite* OpenManzai_CreateSprite(SDL_Renderer* renderer, const char* imagePath);

    /**
     * \brief Frees sprite and it's texture once it has been used.
     *
     * \param sprite
     */
    void OpenManzai_DeleteSprite(OpenManzai_Sprite* sprite);

    /**
     * \brief Set the location of the sprite and its size.
     *
     * \param sprite
     * \param x
     * \param y
     * \param width
     * \param height
     */
    void OpenManzai_SetSpriteDimensions(OpenManzai_Sprite* sprite, const int x, const int y, const int width, const int height);

    /**
     * \brief
     *
     * \param sprite
     * \param x
     * \param y
     * \param width
     * \param height
     */
    void OpenManzai_SetSpriteDestination(OpenManzai_Sprite* sprite, const int x, const int y, const int width, const int height);

    /**
     * \brief
     *
     * \param renderer
     * \param sprite
     */
    void OpenManzai_SetTargetSprite(SDL_Renderer* renderer, OpenManzai_Sprite* sprite);

    /**
     * \brief
     *
     * \param sprite
     * \param renderer The SDL renderer context to draw the sprite.
     */
    void OpenManzai_RenderSprite(SDL_Renderer* renderer, OpenManzai_Sprite* sprite, const double angle, SDL_Point* center, SDL_RendererFlip flip);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* OpenManzai_sprite_h_ */
