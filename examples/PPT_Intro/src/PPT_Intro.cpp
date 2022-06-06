#include "OpenManzi.h"

// static const int WINDOW_WIDTH = 2000;
// static const int WINDOW_HEIGHT = 1024;

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 820;

static const int BACKGROUND_WIDTH = 2000;
static const int BACKGROUND_HEIGHT = 1024;

static const char *BACKGROUND_PATH = "assets/bg/school/school_1.png";
static const char *BACKGROUND_CUTIN_PATH = "assets/bg/school/school_0.png";

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Couldn't initialize SDL2. Error: %s\n",
                     SDL_GetError());
        return -1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Couldn't initialize SDL2_Image: %s\n",
                     SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Testing 1 2 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Could not create a window: %s\n",
                     SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Could not create a renderer: %s\n",
                     SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }

    OpenManzi_Sprite *bg = OpenManzi_CreateSprite(renderer, BACKGROUND_PATH);
    OpenManzi_Sprite *bgCutin =
        OpenManzi_CreateSprite(renderer, BACKGROUND_CUTIN_PATH);
    if (bg == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Could not create sprite: %s\n",
                     SDL_GetError());
        OpenManzi_DeleteSprite(bg);
        OpenManzi_DeleteSprite(bgCutin);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return -1;
    }

    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;
            }
        }
        SDL_RenderClear(renderer);

        OpenManzi_SetSpriteDimensions(bgCutin, 0, 0, 1240, 440);
        OpenManzi_SetSpriteDestination(bgCutin, 644, 0, 0, 0);
        OpenManzi_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);

        OpenManzi_SetSpriteDimensions(bg, 0, 0, BACKGROUND_WIDTH,
                                      BACKGROUND_HEIGHT);
        OpenManzi_SetSpriteDestination(bg, 0, 110, WINDOW_WIDTH, WINDOW_HEIGHT);
        OpenManzi_RenderSprite(renderer, bg, 0, NULL, SDL_FLIP_NONE);

        OpenManzi_SetSpriteDestination(bgCutin, 1748, 0, 2048, 632);

        OpenManzi_SetSpriteDimensions(bgCutin, 0, 888, 814, 136);
        OpenManzi_SetSpriteDestination(bgCutin, 0, 0, 651, 110);
        OpenManzi_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }

    OpenManzi_DeleteSprite(bg);
    OpenManzi_DeleteSprite(bgCutin);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
