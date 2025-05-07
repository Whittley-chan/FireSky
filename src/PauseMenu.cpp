#include "PauseMenu.h"

bool Pause_Loaded = false;

BGR* PauseMenu = new BGR(PauseMenuRect, nullptr);
Button* ResumeButton = new Button(ResumeButtonRect, nullptr);
Button* PauseQuitButton = new Button(PauseQuitButtonRect, nullptr);

void PauseMenuRender()
	{
		if (!Pause_Loaded)
			{
				PauseMenu->BGRImg = LoadIMG("./resources/Background/PauseMenu.png");
				ResumeButton->ButtonTexture = LoadFont(" RESUME ", 96);
				PauseQuitButton->ButtonTexture = LoadFont("  QUIT  ", 96);
			}
		IngameRender();
		SDL_RenderTexture(as->renderer, PauseMenu->BGRImg, NULL, PauseMenu->BGRect);
		SDL_RenderTexture(as->renderer, ResumeButton->ButtonTexture, NULL, ResumeButton->ButtonRect);
		SDL_RenderTexture(as->renderer, PauseQuitButton->ButtonTexture, NULL, PauseQuitButton->ButtonRect);
		
	}

void PauseMenuMouseHandler(SDL_Event* event)
	{
		if (event->button.x>=ResumeButton->ButtonRect->x
			&&event->button.x<=ResumeButton->ButtonRect->x+ResumeButton->ButtonRect->w
			&&event->button.y>=ResumeButton->ButtonRect->y
			&&event->button.y<=ResumeButton->ButtonRect->y+ResumeButton->ButtonRect->h)
			{
				PauseMenuChangeState(IN_GAME);

			}
		else if (event->button.x >= PauseQuitButton->ButtonRect->x
			&&event->button.x <= PauseQuitButton->ButtonRect->x+PauseQuitButton->ButtonRect->w
			&&event->button.y >= PauseQuitButton->ButtonRect->y
			&&event->button.y <= PauseQuitButton->ButtonRect->y+PauseQuitButton->ButtonRect->h)
			{
				PauseMenuChangeState(QUIT);
				
			}
	}
void PauseMenuChangeState(GameContext context)
	{
		switch (context)
			{
				case IN_GAME:
					{
						as->Context = IN_GAME;
						Paused = false;
						break;
					}
				case QUIT:
					{
						as->Context = QUIT;
						break;
					}
			}
	}

