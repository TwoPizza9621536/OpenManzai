#include <stdbool.h>
#include <SDL2/SDL.h>
#include <openmanzi.h>

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 800;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Couldn't initialize SDL2. Error: %s", SDL_GetError());
        return -1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("Couldn't initialize SDL2_Image. Error: %s", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Testing 1 2 3", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a window.");
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer.");
        SDL_DestroyWindow(window);
        return -1;
    }

    OpenManzi_Sprite *background = OpenManzi_CreateSprite(renderer, "assets/bg/school/bg_0020_1_001.png");
    if (background == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a sprite.");
        OpenManzi_DeleteSprite(background);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return -1;
    }

    OpenManzi_setSpriteDimensions(background, 0, 0, 2000, 1024);

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window)
                    {
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_SetWindowSize(window, event.window.data1, event.window.data2);
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);
        OpenManzi_RenderSprite(background, renderer, 0, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    OpenManzi_DeleteSprite(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
