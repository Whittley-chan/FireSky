#define SDL_MAIN_USE_CALLBACKS

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "main.h"

const bool* Keyboard = nullptr;

void SDL_AppQuit(void* appstate, SDL_AppResult result) 
    {	
		if (Highscores.size() > 0)
			{
				std::ofstream file("./resources/Highscores.txt");
				if (!file)
					{
						as->Context = QUIT;
					}
				auto i = Highscores.begin();
				while (i != Highscores.end() && *i > Score) 
					{
						i++;
					}
				Highscores.insert(i, Score);
				Highscores.pop_back();

				for (unsigned long int i : Highscores)
					{
						file << i << "\n";
					}

				file.close();
				
			}
        SDL_free(appstate);
    }

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) 
    {
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
											MainMenuMouseHandler(event);
											break;
										}
									case IN_GAME:
										{
											IngameMouseHandler(event);
											break;
										}
									case PAUSED:
										{
											PauseMenuMouseHandler(event);
											break;
										}
									case GAME_OVER:
										{
											GameOverMouseHandler(event);
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
		if (as->Context == QUIT)
			{	
				return SDL_APP_SUCCESS;
			}
		
		Keyboard = SDL_GetKeyboardState(NULL);
		
        Render();
		SDL_RenderPresent(as->renderer);
		SDL_Delay((Uint32)DELTA_TIME);
        return SDL_APP_CONTINUE;
    }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv)
    {
	    as = (Appstate*)SDL_calloc(1, sizeof(Appstate));
		
		if (!as)
			{
			    return SDL_APP_FAILURE;
			}
		else
			{
			    *appstate = as;
			}

        Init();

        

        return SDL_APP_CONTINUE;
    }

