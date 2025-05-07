#include "Render.h"

void Render()
	{
		switch(as->Context)
			{
				case MAIN_MENU:
					{
						//std::cout << "Main menu";
						MainMenuRender();
						
						break;
					}
				case IN_GAME:
					{
						IngameKeyboardHandler();
						IngameRender();

						break;
					}
				case PAUSED:
					{
						PauseMenuRender();
						break;
					}
				case GAME_OVER:
					{
						GameOverRender();
						break;
					}

				default:
					{
						break;
					}
			}
		
	}