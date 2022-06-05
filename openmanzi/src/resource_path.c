#include "resource_path.h"

const char* getResourcePath(const char *path)
{
    static char baseResource[100];
    if (strlen(baseResource) == 0)
    {
        const char *basePath = SDL_GetBasePath();
        if (basePath == NULL)
        {
            SDL_Log("Error getting resource path.");
            return "";
        }

        strncpy(baseResource, basePath, sizeof(baseResource) - 1);
        strncat(baseResource, path, sizeof(baseResource) - strlen(baseResource) - 1);
    }
    return baseResource;
}
