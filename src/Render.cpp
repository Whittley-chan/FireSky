<<<<<<< HEAD
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
		
=======
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
		
>>>>>>> 8efbb6131e1c3c2e4adf6c29c57f71e25ce283d1
	}