/**
 * \file PPT_Intro.cpp
 * \author OpenManzai Contributors
 * \brief The opening to Puyo Puyo Tetris. A test program for the main library.
 *        Puyo Puyo and Tetris are either copyright or trademarks of SEGA
 *        Corporation and The Tetris Company respectively.
 * \version 0.0.0
 * \date 2022-06-06
 *
 * \copyright Copyright (c) 2022
 *
 */

#include "OpenManzai.h"

static const char* WINDOW_NAME = "Puyo Puyo Tetris Intro";

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

static const char* BACKGROUND_PATH = "assets/bg/bg_20/bg_20_1.png";
static const char* BACKGROUND_CUTIN_PATH = "assets/bg/bg_20/bg_20_0.png";
static const char* BACKGROUND_TREE_PATH = "assets/bg/bg_20/bg_20_2.png";

static const char* RINGO_PATH = "assets/manzai/rng/rng_0.png";
static const char* RINGO_FACE_PATH = "assets/manzai/rng/rng_3.png";

void Draw_Background(SDL_Renderer* renderer, OpenManzai_Sprite* bg, OpenManzai_Sprite** bgCutin)
{
    OpenManzai_SetTargetSprite(renderer, bgCutin[0]);
    OpenManzai_SetSpriteSource(bgCutin[0], 0, 0, 1240, 440);
    OpenManzai_SetSpriteDestination(bgCutin[0], (int)(761 * 0.64), 0, (int)(1240 * 0.64), (int)(440 * 0.7));
    OpenManzai_RenderSprite(renderer, bgCutin[0], 0, NULL, SDL_FLIP_NONE);

    OpenManzai_SetTargetSprite(renderer, bg);
    OpenManzai_SetSpriteSource(bg, 0, 0, 2000, 1024);
    OpenManzai_SetSpriteDestination(bg, 0, (int)(136 * 0.7), WINDOW_WIDTH, WINDOW_HEIGHT - (int)(136 * 0.7));
    OpenManzai_RenderSprite(renderer, bg, 0, NULL, SDL_FLIP_NONE);

    OpenManzai_SetTargetSprite(renderer, bgCutin[0]);
    OpenManzai_SetSpriteSource(bgCutin[0], 0, 888, 813, 136);
    OpenManzai_SetSpriteDestination(bgCutin[0], 0, 0, (int)(813 * 0.64), (int)(136 * 0.7));
    OpenManzai_RenderSprite(renderer, bgCutin[0], 0, NULL, SDL_FLIP_NONE);

    /*
    OpenManzai_SetSpriteSource(bgCutin[0], 830, 475, 604, 514);
    OpenManzai_SetSpriteDestination(bgCutin[0], 995, 85, 464, 395);
    OpenManzai_RenderSprite(renderer, bgCutin[0], 0, NULL, SDL_FLIP_NONE);

    OpenManzai_SetTargetSprite(renderer, bgCutin[1]);
    OpenManzai_SetSpriteSource(bgCutin[1], 0, 0, 0, 0);
    OpenManzai_SetSpriteDestination(bgCutin[1], 1200, 80, 413, 413);
    OpenManzai_RenderSprite(renderer, bgCutin[1], 0, NULL, SDL_FLIP_NONE);

    OpenManzai_SetSpriteSource(bgCutin, 1748, 0, 2048, 632);
    OpenManzai_SetSpriteDestination(bgCutin, 0, 50, 326, 1024);
    OpenManzai_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);
    */
}

int main()
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    OpenManzai_Sprite* bg;
    OpenManzai_Sprite** bgCutin;
    OpenManzai_Sprite* rng;
    OpenManzai_Sprite* rngFace;
    SDL_Event event;
    SDL_bool quit;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Couldn't initialize SDL2. Error: %s\n", SDL_GetError());
        return -1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Couldn't initialize SDL2_Image: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Could not create a window: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }
    /*
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    */

    bg = OpenManzai_CreateSprite(renderer, BACKGROUND_PATH);
    bgCutin = (OpenManzai_Sprite**)SDL_malloc(sizeof(OpenManzai_Sprite*) * 2);
    bgCutin[0] = OpenManzai_CreateSprite(renderer, BACKGROUND_CUTIN_PATH);
    bgCutin[1] = OpenManzai_CreateSprite(renderer, BACKGROUND_TREE_PATH);

    rng = OpenManzai_CreateSprite(renderer, RINGO_PATH);
    rngFace = OpenManzai_CreateSprite(renderer, RINGO_FACE_PATH);
    if (bg == NULL || bgCutin[0] == NULL || rng == NULL || rngFace == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create sprite: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return -1;
    }


    quit = SDL_FALSE;
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

        Draw_Background(renderer, bg, bgCutin);

        /*
        OpenManzai_SetTargetSprite(renderer, rng);
        OpenManzai_SetSpriteSource(rng, 0, 0, 512, 1024);
        OpenManzai_SetSpriteDestination(rng, 50, 100, 0, 0);
        OpenManzai_RenderSprite(renderer, rng, 0, NULL, SDL_FLIP_HORIZONTAL);

        OpenManzai_SetTargetSprite(renderer, rngFace);
        OpenManzai_SetSpriteSource(rngFace, 0, 0, 252, 252);
        OpenManzai_SetSpriteDestination(rngFace, 241, 203, 0, 0);
        OpenManzai_RenderSprite(renderer, rngFace, 0, NULL, SDL_FLIP_HORIZONTAL);
        */

        SDL_RenderPresent(renderer);
    }

    OpenManzai_DeleteSprite(bg);
    OpenManzai_DeleteSprite(bgCutin[0]);
    OpenManzai_DeleteSprite(bgCutin[1]);
    OpenManzai_DeleteSprite(rng);
    OpenManzai_DeleteSprite(rngFace);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
