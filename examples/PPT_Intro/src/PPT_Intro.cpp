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

// static const int WINDOW_WIDTH = 2000;
// static const int WINDOW_HEIGHT = 1024;

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 820;

static const int BACKGROUND_WIDTH = 2000;
static const int BACKGROUND_HEIGHT = 1024;

static const char* BACKGROUND_PATH = "assets/bg/bg_20/bg_20_001.png";
static const char* BACKGROUND_CUTIN_PATH = "assets/bg/bg_20/bg_20_000.png";

static const char* RINGO_PATH = "assets/manzai/rng/rng_0.png";
static const char* RINGO_FACE_PATH = "assets/manzai/rng/rng_3.png";

void Draw_Background(SDL_Renderer* renderer, OpenManzai_Sprite* bg, OpenManzai_Sprite* bgCutin)
{
    OpenManzai_TargetSprite(renderer, bgCutin);
    OpenManzai_SetSpriteDimensions(bgCutin, 0, 0, 1240, 440);
    OpenManzai_SetSpriteDestination(bgCutin, 644, 0, 956, 440);
    OpenManzai_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);

    OpenManzai_TargetSprite(renderer, bg);
    OpenManzai_SetSpriteDimensions(bg, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    OpenManzai_SetSpriteDestination(bg, 0, 110, WINDOW_WIDTH, 710);
    OpenManzai_RenderSprite(renderer, bg, 0, NULL, SDL_FLIP_NONE);

    OpenManzai_TargetSprite(renderer, bgCutin);
    OpenManzai_SetSpriteDimensions(bgCutin, 0, 888, 814, 136);
    OpenManzai_SetSpriteDestination(bgCutin, 0, 0, 651, 110);
    OpenManzai_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);

    OpenManzai_SetSpriteDimensions(bgCutin, 830, 475, 603, 513);
    OpenManzai_SetSpriteDestination(bgCutin, 0, 0, 464, 395);
    OpenManzai_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);

    // OpenManzai_SetSpriteDimensions(bgCutin, 1748, 0, 2048, 632);
    // OpenManzai_SetSpriteDestination(bgCutin, 0, 50, 326, 1024);
    // OpenManzai_RenderSprite(renderer, bgCutin, 0, NULL, SDL_FLIP_NONE);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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

    SDL_Window* window = SDL_CreateWindow(
        WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
            "Could not create a window: %s\n",
            SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }
    // SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    // SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    OpenManzai_Sprite* bg = OpenManzai_CreateSprite(renderer, BACKGROUND_PATH);
    OpenManzai_Sprite* bgCutin = OpenManzai_CreateSprite(renderer, BACKGROUND_CUTIN_PATH);
    OpenManzai_Sprite* rng = OpenManzai_CreateSprite(renderer, RINGO_PATH);
    OpenManzai_Sprite* rngFace = OpenManzai_CreateSprite(renderer, RINGO_FACE_PATH);
    if (bg == NULL || bgCutin == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
            "Could not create sprite: %s\n",
            SDL_GetError());
        OpenManzai_DeleteSprite(bg);
        OpenManzai_DeleteSprite(bgCutin);
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

        Draw_Background(renderer, bg, bgCutin);

        // OpenManzai_TargetSprite(renderer, rng);
        // OpenManzai_SetSpriteDimensions(rng, 0, 0, 512, 1024);
        // OpenManzai_SetSpriteDestination(rng, 50, 100, 0, 0);
        // OpenManzai_RenderSprite(renderer, rng, 0, NULL, SDL_FLIP_HORIZONTAL);

        // OpenManzai_TargetSprite(renderer, rngFace);
        // OpenManzai_SetSpriteDimensions(rngFace, 0, 0, 252, 252);
        // OpenManzai_SetSpriteDestination(rngFace, 241, 203, 0, 0);
        // OpenManzai_RenderSprite(renderer, rngFace, 0, NULL, SDL_FLIP_HORIZONTAL);

        SDL_RenderPresent(renderer);
    }

    OpenManzai_DeleteSprite(bg);
    OpenManzai_DeleteSprite(bgCutin);
    OpenManzai_DeleteSprite(rng);
    OpenManzai_DeleteSprite(rngFace);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
