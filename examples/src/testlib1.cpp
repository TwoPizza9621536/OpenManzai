#include <openmanzi.h>

// static const int WINDOW_WIDTH = 1600;
// static const int WINDOW_HEIGHT = 820;

static const int WINDOW_WIDTH = 2000;
static const int WINDOW_HEIGHT = 1024;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Couldn't initialize SDL2. Error: %s\n", SDL_GetError());
        return -1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("Couldn't initialize SDL2_Image: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Testing 1 2 3", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    OpenManzi_Sprite *background = OpenManzi_CreateSprite(renderer, "assets/bg/school/school_1.png");
    OpenManzi_Sprite *background2 = OpenManzi_CreateSprite(renderer, "assets/bg/school/school_0.png");
    if (background == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create sprite: %s\n", SDL_GetError());
        OpenManzi_DeleteSprite(background);
        OpenManzi_DeleteSprite(background2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return -1;
    }

    OpenManzi_setSpriteDimensions(background, 0, 0, 1999, 1024);
    // OpenManzi_setSpriteDimensions(background2, 0, 888, 812, 136);

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
        OpenManzi_RenderSprite(background2, renderer, 0, 0);
        OpenManzi_RenderSprite(background, renderer, 0, 0);
        SDL_RenderPresent(renderer);
    }

    OpenManzi_DeleteSprite(background);
    OpenManzi_DeleteSprite(background2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
