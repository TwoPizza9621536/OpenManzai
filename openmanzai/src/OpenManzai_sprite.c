/**
 * \file OpenManzai_sprite.c
 * \author your name (you@domain.com)
 * \brief
 * \version 0.0.0
 * \date 2022-06-06
 *
 * \copyright Copyright (c) 2022
 *
 */

#include "OpenManzai_sprite.h"

 /**
  * Create and allocate memory for our sprite with an image we want to draw so we
  * do not have to do it manually.
  */
OpenManzai_Sprite* OpenManzai_CreateSprite(SDL_Renderer* renderer, const char* imagePath)
{
    OpenManzai_Sprite* sprite = (OpenManzai_Sprite*)SDL_malloc(sizeof(OpenManzai_Sprite));
    SDL_Texture* image = IMG_LoadTexture(renderer, imagePath);

    sprite->source = (SDL_Rect*)SDL_malloc(sizeof(SDL_Rect));
    sprite->destination = (SDL_Rect*)SDL_malloc(sizeof(SDL_Rect));

    if (image == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
        return NULL;
    }
    sprite->image = image;
    return sprite;
}

/**
 * Deallocate the sprite from memory so it does not cause a memory leak and
 * allocate that memory for other purposes.
 */
void OpenManzai_DeleteSprite(OpenManzai_Sprite* sprite)
{
    if (sprite->destination != NULL)
        SDL_free(sprite->destination);
    if (sprite->source != NULL)
        SDL_free(sprite->source);
    if (sprite->image != NULL)
        SDL_DestroyTexture(sprite->image);
    if (sprite != NULL)
        SDL_free(sprite);
}

/**
 * ? Better name for this function to differentiate between SetSpriteDestination
 * ? Or we combine those two functions. See issue #6.
 *
 * Set the coordinates and size of the image we want to draw from.
 */
void OpenManzai_SetSpriteSource(OpenManzai_Sprite* sprite, const int x, const int y, const int width, const int height)
{
    sprite->source->x = x;
    sprite->source->y = y;
    if (width > 0 && height > 0)
    {
        sprite->source->w = width;
        sprite->source->h = height;
    }
    else
    {
        SDL_QueryTexture(sprite->image, NULL, NULL, &sprite->source->w, &sprite->source->h);
    }
}

/**
 * ? Better name for this function to differentiate between SetSpriteDimensions
 * ? Or we combine those two functions. See issue #6.
 *
 * ? Fallback if user did not call SetSpriteDimensions or provide x and y
 *
 * Set the placement and the size of the image we want draw to.
 * SDL will automatically resize the image when given the width and height based
 * on window size.
 * There is no still good way to do relative positioning or resizing based on
 * resolution. See the issue #7.
 */
void OpenManzai_SetSpriteDestination(OpenManzai_Sprite* sprite, const int x, const int y, const int width, const int height)
{
    sprite->destination->x = x;
    sprite->destination->y = y;

    if (width > 0 && height > 0)
    {
        sprite->destination->w = width;
        sprite->destination->h = height;
    }
    else
    {
        sprite->destination->w = sprite->source->w;
        sprite->destination->h = sprite->source->h;
    }
}

void OpenManzai_SetTargetSprite(SDL_Renderer* renderer, OpenManzai_Sprite* sprite)
{
    SDL_SetRenderTarget(renderer, sprite->image);
}

/**
 * ? How to scale sprites and move them based on resolution. See issue #7.
 *
 * ? Should we simplify the SDL rotate angle, center and flipping modifiers.
 * ? See issue #5.
 *
 * An abstraction layer to render the sprite so we do not have pass additional
 * pointers.
 */
void OpenManzai_RenderSprite(SDL_Renderer* renderer, OpenManzai_Sprite* sprite, const double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, sprite->image, sprite->source, sprite->destination, angle, center, flip);
}
