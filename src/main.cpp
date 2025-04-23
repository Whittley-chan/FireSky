#define SDL_MAIN_USE_CALLBACKS

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "graphics.h"


//      Initializations:


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) 
    {
        if (event->type == SDL_EVENT_QUIT) 
            {
                return SDL_APP_SUCCESS;
            }
        return SDL_APP_CONTINUE;
    }


SDL_AppResult SDL_AppIterate(void* appstate) // Main game loop - Everything runs in realtime
    {   
        Render();
		Update();
        return SDL_APP_CONTINUE;
    }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv) 
    {
        Init();

        return SDL_APP_CONTINUE;
    }

