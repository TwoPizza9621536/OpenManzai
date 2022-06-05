#include <openmanzi.h>
#include "resource_path.h"

OpenManzi_Sprite* OpenManzi_CreateSprite(SDL_Renderer *renderer, const char* imagePath)
{
    OpenManzi_Sprite *sprite = (OpenManzi_Sprite*)malloc(sizeof(OpenManzi_Sprite));
    const char *resourcePath = getResourcePath(imagePath);
    SDL_Texture* image = IMG_LoadTexture(renderer, resourcePath);
    if (image == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load sprite.");
        printf("%s\n", SDL_GetError());
        return NULL;
    }
    sprite->image = image;
    return sprite;
}

void OpenManzi_DeleteSprite(OpenManzi_Sprite* sprite)
{
    if (sprite == NULL) return;
    if (sprite->image == NULL) return;
    SDL_DestroyTexture(sprite->image);
    free(sprite);
}

void OpenManzi_setSpriteDimensions(OpenManzi_Sprite *sprite, int x, int y, int width, int height)
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

void OpenManzi_RenderSprite(OpenManzi_Sprite *sprite, SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = sprite->dimensions.w;
    destination.h = sprite->dimensions.h;
    SDL_RenderCopy(renderer, sprite->image, &sprite->dimensions, &destination);
}
