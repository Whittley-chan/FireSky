#include "MainMenu.h"


BGR* menuBackground = new BGR(new SDL_FRect{0,0,(float)wWidth, (float)wHeight}, nullptr);
Button* PlayButton = new Button(new SDL_FRect{ (float)wWidth/2-125, (float)wHeight/2+100, 200, 100 }, nullptr);
Button* ExitButton = new Button(new SDL_FRect{ (float)wWidth/2-125, (float)wHeight/2+205, 200, 100 }, nullptr);

void MainMenuMouseHandler(SDL_Event* event)
	{
		if (event->button.x>=PlayButton->ButtonRect->x
			&&event->button.x<=PlayButton->ButtonRect->x+PlayButton->ButtonRect->w
			&&event->button.y>=PlayButton->ButtonRect->y
			&&event->button.y<=PlayButton->ButtonRect->y+PlayButton->ButtonRect->h)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEBUG", "Play Button Clicked", as->window);
				changeState();

				as->Context = IN_GAME;


			}
		else if (event->button.x >= ExitButton->ButtonRect->x
			&&event->button.x <= ExitButton->ButtonRect->x+ExitButton->ButtonRect->w
			&&event->button.y >= ExitButton->ButtonRect->y
			&&event->button.y <= ExitButton->ButtonRect->y+ExitButton->ButtonRect->h)
			{
				as->Context = QUIT;
			}
	}

void MainMenuRender()
	{
		
		if (ExitButton->ButtonTexture == nullptr && PlayButton->ButtonTexture == nullptr && menuBackground->BGRImg == nullptr)
			{
				menuBackground->BGRImg = LoadIMG("./resources/MainMenu/Background_MainMenu.png");
				PlayButton->ButtonTexture = LoadIMG("./resources/MainMenu/PlayButton.png");
				ExitButton->ButtonTexture = LoadIMG("./resources/MainMenu/ExitButton.png");
			}
		
		
		SDL_RenderClear(as->renderer);
		SDL_RenderTexture(as->renderer, menuBackground->BGRImg, NULL, menuBackground->BGRect);
		SDL_RenderTexture(as->renderer, PlayButton->ButtonTexture, NULL, PlayButton->ButtonRect);
		SDL_RenderTexture(as->renderer, ExitButton->ButtonTexture, NULL, ExitButton->ButtonRect);
	}

void changeState()
	{
		SDL_DestroyTexture(menuBackground->BGRImg);
		SDL_DestroyTexture(PlayButton->ButtonTexture);
		SDL_DestroyTexture(ExitButton->ButtonTexture);

		delete menuBackground->BGRect;
		delete PlayButton->ButtonRect;
		delete ExitButton->ButtonRect;

		delete menuBackground;
		delete PlayButton;
		delete ExitButton;
	}