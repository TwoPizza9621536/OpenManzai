#include "OpenManzi_sprite.h"

/**
 * ? Please suggest a better variable and function names.
 *
 * Abstraction layer to store information about rhe sprite so we do not have to
 * set each variable individually and keep repeating ourselves.
 */
struct OpenManzi_Sprite
{
    SDL_Rect dimensions, destination;
    SDL_Texture *image;
};

/**
 * Create and allocate memory for our sprite with an image we want to draw so we
 * do not have to do it manually.
 */
OpenManzi_Sprite* OpenManzi_CreateSprite(SDL_Renderer *renderer, const char *imagePath)
{
    OpenManzi_Sprite *sprite = (OpenManzi_Sprite*)SDL_malloc(sizeof(OpenManzi_Sprite));
    if (!sprite->image) SDL_free(sprite->image);

    SDL_Texture *image = IMG_LoadTexture(renderer, imagePath);
    if (image == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load sprite.");
        return NULL;
    }
    sprite->image = image;
    return sprite;
}

/**
 * Deallocate the sprite from memory so it does not cause a memory leak and
 * allocate that memory for other purposes.
 */
void OpenManzi_DeleteSprite(OpenManzi_Sprite *sprite)
{
    if (sprite == NULL) return;
    if (sprite->image == NULL) return;
    SDL_DestroyTexture(sprite->image);
    SDL_free(sprite);
}

/**
 * ? Better name for this function to differentiate between SetSpriteDestination
 * ? Or we combine those two functions
 *
 * Set the coordinates and size of the image we want to draw from.
 */
void OpenManzi_SetSpriteDimensions(OpenManzi_Sprite *sprite, int x, int y, int width, int height)
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
 * ? Or we combine those two functions
 *
 * ? Fallback if user did not call SetSpriteDimensions or provide x andy y
 *
 * Set the placement and the size of the image we want draw to.
 * SDL will automatically resize the image when given the width and height.
 */
void OpenManzi_SetSpriteDestination(OpenManzi_Sprite *sprite, int x, int y, int width, int height)
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
        rectangle.w = sprite->dimensions.w;
        rectangle.h = sprite->dimensions.h;
    }

    sprite->destination = rectangle;
}

/**
 * ? How to scale sprites and move them based on resolution
 *
 * An abstraction layer to render the sprite so we do not have pass additional
 * pointers.
 */
void OpenManzi_RenderSprite(SDL_Renderer *renderer, OpenManzi_Sprite *sprite)
{
    SDL_RenderCopy(renderer, sprite->image, &sprite->dimensions, &sprite->destination);
}
