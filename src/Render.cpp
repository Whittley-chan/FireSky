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
						//std::cout << "Ingame";
						IngameRender();
						break;
					}
				case PAUSED:
					{
						PauseMenuRender();
						break;
					}
				default:
					{
						break;
					}
			}
		
	}