#include <OpenManzi.h>

// static const int WINDOW_WIDTH = 2000;
// static const int WINDOW_HEIGHT = 1024;

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 820;

static const int BACKGROUND_WIDTH = 2000;
static const int BACKGROUND_HEIGHT = 1024;

static const int BACKGROUND_CUTIN_WIDTH = 814;
static const int BACKGROUND_CUTIN_HEIGHT = 136;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL2. Error: %s\n", SDL_GetError());
        return -1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL2_Image: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Testing 1 2 3", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a window: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }

    OpenManzi_Sprite *backgroundCutinOne = OpenManzi_CreateSprite(renderer, "assets/bg/school/school_0.png");
    OpenManzi_Sprite *background = OpenManzi_CreateSprite(renderer, "assets/bg/school/school_1.png");
    if (background == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create sprite: %s\n", SDL_GetError());
        OpenManzi_DeleteSprite(background);
        OpenManzi_DeleteSprite(backgroundCutinOne);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return -1;
    }

    OpenManzi_SetSpriteDimensions(background, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    OpenManzi_SetSpriteDimensions(backgroundCutinOne, 0, 888, BACKGROUND_CUTIN_WIDTH, BACKGROUND_CUTIN_HEIGHT);

    OpenManzi_SetSpriteDestination(background, 0, 110, WINDOW_WIDTH, WINDOW_HEIGHT);
    OpenManzi_SetSpriteDestination(backgroundCutinOne, 0, 0, 651, 110);

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
        OpenManzi_RenderSprite(renderer, background);
        OpenManzi_RenderSprite(renderer, backgroundCutinOne);
        SDL_RenderPresent(renderer);
    }

    OpenManzi_DeleteSprite(background);
    OpenManzi_DeleteSprite(backgroundCutinOne);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
