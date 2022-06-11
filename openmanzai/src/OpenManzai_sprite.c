/**
 * \file OpenManzai_sprite.c
 * \author your name (you@domain.com)
 * \brief
 * \version 0.1
 * \date 2022-06-06
 *
 * \copyright Copyright (c) 2022
 *
 */

#include "OpenManzai_sprite.h"

 /**
  * ? Please suggest a better variable and function names. See issue #6.
  *
  * Abstraction layer to store information about rhe sprite so we do not have to
  * set each variable individually and keep repeating ourselves.
  */

struct OpenManzai_Sprite
{
    SDL_Rect dimensions, destination;
    SDL_Texture* image;
};

/**
 * Create and allocate memory for our sprite with an image we want to draw so we
 * do not have to do it manually.
 */
OpenManzai_Sprite* OpenManzai_CreateSprite(SDL_Renderer* renderer, const char* imagePath)
{
    OpenManzai_Sprite* sprite = (OpenManzai_Sprite*)SDL_malloc(sizeof(OpenManzai_Sprite));
    SDL_Texture* image = IMG_LoadTexture(renderer, imagePath);

    if (image == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load sprite: %s\n", imagePath);
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
    if (sprite == NULL) return;
    else if (sprite->image == NULL) SDL_free(sprite);
    SDL_DestroyTexture(sprite->image);
    SDL_free(sprite);
}

/**
 * ? Better name for this function to differentiate between SetSpriteDestination
 * ? Or we combine those two functions. See issue #6.
 *
 * Set the coordinates and size of the image we want to draw from.
 */
void OpenManzai_SetSpriteDimensions(OpenManzai_Sprite* sprite, const int x, const int y, const int width, const int height)
{
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    if (width > 0 && height > 0)
    {
        rectangle.w = width;
        rectangle.h = height;
    }
    else
    {
        SDL_QueryTexture(sprite->image, NULL, NULL, &rectangle.w, &rectangle.h);
    }

    sprite->dimensions = rectangle;
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
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;

    if (width > 0 && height > 0)
    {
        rectangle.w = width;
        rectangle.h = height;
    }
    else if (width > 0)
    {
        rectangle.w = width;
        rectangle.h = sprite->dimensions.h;
    }
    else if (height > 0)
    {
        rectangle.w = sprite->dimensions.w;
        rectangle.h = height;
    }
    else
    {
        rectangle.w = sprite->dimensions.w;
        rectangle.h = sprite->dimensions.h;
    }

    sprite->destination = rectangle;
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
    SDL_RenderCopyEx(renderer, sprite->image, &sprite->dimensions, &sprite->destination, angle, center, flip);
}
