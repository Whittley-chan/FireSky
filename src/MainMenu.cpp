#include "MainMenu.h"


BGR* menuBackground = new BGR(MainMenuBackgroundRect, nullptr);
Button* PlayButton = new Button(PlayButtonRect, nullptr);
Button* QuitButton = new Button(QuitButtonRect, nullptr);

static void changeState()
	{
		SDL_DestroyTexture(menuBackground->BGRImg);
		SDL_DestroyTexture(PlayButton->ButtonTexture);
		SDL_DestroyTexture(QuitButton->ButtonTexture);

		delete menuBackground->BGRect;
		delete PlayButton->ButtonRect;
		delete QuitButton->ButtonRect;

		delete menuBackground;
		delete PlayButton;
		delete QuitButton;
	}

void MainMenuMouseHandler(SDL_Event* event)
	{
		if (event->button.x>=PlayButton->ButtonRect->x
			&&event->button.x<=PlayButton->ButtonRect->x+PlayButton->ButtonRect->w
			&&event->button.y>=PlayButton->ButtonRect->y
			&&event->button.y<=PlayButton->ButtonRect->y+PlayButton->ButtonRect->h)
			{
				changeState();

				as->Context = IN_GAME;


			}
		else if (event->button.x >= QuitButton->ButtonRect->x
			&&event->button.x <= QuitButton->ButtonRect->x+QuitButton->ButtonRect->w
			&&event->button.y >= QuitButton->ButtonRect->y
			&&event->button.y <= QuitButton->ButtonRect->y+QuitButton->ButtonRect->h)
			{
				as->Context = QUIT;
			}
	}

void MainMenuRender()
	{
		
		if (QuitButton->ButtonTexture == nullptr && PlayButton->ButtonTexture == nullptr && menuBackground->BGRImg == nullptr)
			{
				menuBackground->BGRImg = LoadIMG("./resources/Background/MainMenu.png");
				PlayButton->ButtonTexture = LoadFont("  PLAY  ", 96);
				QuitButton->ButtonTexture = LoadFont("  QUIT  ", 96);
			}
		
		
		SDL_RenderClear(as->renderer);
		SDL_RenderTexture(as->renderer, menuBackground->BGRImg, NULL, menuBackground->BGRect);
		SDL_RenderTexture(as->renderer, PlayButton->ButtonTexture, NULL, PlayButton->ButtonRect);
		SDL_RenderTexture(as->renderer, QuitButton->ButtonTexture, NULL, QuitButton->ButtonRect);

	}

