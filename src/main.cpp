#define SDL_MAIN_USE_CALLBACKS

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "graphics.h"
#include "main.h"

#include <cstdlib>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const GameState gs)
	{
	    os<< gs;
	    return os;
	}


void SDL_AppQuit(void* appstate, SDL_AppResult result) 
    {
        SDL_free(appstate);
    }


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) 
    {
	    Appstate* as = (Appstate*)appstate;
        if (event->type == SDL_EVENT_QUIT) 
            {
                return SDL_APP_SUCCESS;
            }
        return SDL_APP_CONTINUE;
    }


SDL_AppResult SDL_AppIterate(void* appstate) // Main game loop - Everything runs in realtime
    {   
	    Appstate* as = (Appstate*)appstate;
        Render();
        return SDL_APP_CONTINUE;
    }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv) 
    {
	    Appstate* as = (Appstate*)SDL_calloc(1, sizeof(Appstate));
        


		if (!as)
			{
			    return SDL_APP_FAILURE;
			}
		else
			{
			    *appstate = as;
			}

        Init(as);
        


        return SDL_APP_CONTINUE;
    }

