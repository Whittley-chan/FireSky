#define SDL_MAIN_USE_CALLBACKS

#include <vector>
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "main.h"






void SDL_AppQuit(void* appstate, SDL_AppResult result) 
    {
        SDL_free(appstate);
    }


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) 
    {
	    Appstate* as = (Appstate*)appstate;
        
        switch(event->type)
            {
                case SDL_EVENT_QUIT:
                    {
                        return SDL_APP_SUCCESS;
                        break;
                    }
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
					{
					    if (event->button.button == SDL_BUTTON_LEFT)
						    {
							switch (as->Context)
								{
									case MAIN_MENU:
										{
											MainMenuMouseHandler(as, event);
											break;
										}
									case IN_GAME:
										{
											IngameMouseHandler(as, event);
											break;
										}
									case PAUSED:
										{
											SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEBUG", "Pause Menu Clicked", as->window);
											break;
										}
									default:
										{
											break;
										}
								}
						    }
					    break;
					}
                default:
                    {
                        break;
                    }
            }
        return SDL_APP_CONTINUE;
    }


SDL_AppResult SDL_AppIterate(void* appstate)
	{
	    Appstate* as = (Appstate*)appstate;
		if (as->Context == QUIT)
			{
				return SDL_APP_SUCCESS;
			}
        Render(as);
		SDL_RenderPresent(as->renderer);
		SDL_Delay(16);
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

