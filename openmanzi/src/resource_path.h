#ifndef OPENMANZI_RESOURCE_PATH_H
#define OPENMANZI_RESOURCE_PATH_H

#include <string.h>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif
const char* getResourcePath(const char *path);

#endif /* OPENMANZI_RESOURCE_PATH_H */
